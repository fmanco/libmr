/* ==========================================================================
 * libmr - A lowlevel library for "Micro Rato"
 * ========================================================================== */

/**
 *  \file  lib/robot/robot.c
 *  \brief Implement basic operations on robot (like enabling/disabling sensors)
 *         and robot state database
 *
 *
 *  \version 0.1.0
 *  \date    Nov 2012
 *
 *  \author Filipe Manco <filipe.manco@gmail.com>
 */

#include <base.h>
#include <robot/robot.h>
#include <robot/conf.h>
#include <detpic32.h>


/* ========================================================================== */

/* ===================
 * Generic
 */
#define IN  1
#define OUT 0

/* ===================
 * Motors
 */
#define M1_IN1 LATBbits.LATB5
#define M1_IN2 LATCbits.LATC13
#define M2_IN1 LATBbits.LATB13
#define M2_IN2 LATFbits.LATF3
#define STDBY  LATCbits.LATC14
#define M1_FORWARD M1_IN1=1; M1_IN2=0
#define M1_REVERSE M1_IN1=0; M1_IN2=1
#define M2_FORWARD M2_IN1=0; M2_IN2=1
#define M2_REVERSE M2_IN1=1; M2_IN2=0

/* ===================
 * Leds
 */
#define LED1   LATEbits.LATE0
#define LED2   LATEbits.LATE1
#define LED3   LATEbits.LATE2
#define LED4   LATEbits.LATE3
#define LED5   LATBbits.LATB15

/* ===================
 * Servo
 */
#define T2_FREQ       625 // fin_t2 = 625 kHz
#define SERVO_LEVELS  (SERVO_POS_RIGHT - SERVO_POS_LEFT)
#define SERVO_K       ((((SERVO_WIDTH_MAX - SERVO_WIDTH_MIN) * T2_FREQ) / 1000) / SERVO_LEVELS)
#define SERVO_MIN_PWM_IS_RIGHT


/* ========================================================================== */

volatile mrSens  sensors;
volatile mrActs  actuators;
volatile mrClock ticker;

static int counter_m1 = 0;
static int counter_m2 = 0;


/* ========================================================================== */

uint getGroundSensors ( void );

int  avfilter_mleft   ( int vel );
int  avfilter_mright  ( int vel );

void stopMotors       ( void );

void delay ( uint tenth_ms);
void wait  ( uint tenth_seconds );



/* ==========================================================================
 * Management
 */

void robot_init(void)
{
	/* ===================
	 * Disable JTAG
	 */
	DDPCON = 3;

	/* ===================
	 * Config Timer2, Timer3, OC1, OC2 and OC5
	 */
	T2CONbits.TCKPS = 5;    // 1:16 prescaler (i.e. fin = 625 KHz)
	PR2 = 6249;             // Fout = 20M / (32 * (6249 + 1)) = 100 Hz
	TMR2 = 0;               // Reset timer T2 count register
	T2CONbits.TON = 1;      // Enable timer T2 (must be the last command of
	                        //  the timer configuration sequence)
	                        //
	T3CONbits.TCKPS = 4;    // 1:32 prescaler (i.e. fin = 1.25 MHz)
	PR3 = 63;               // Fout = 20M / (16 * (63 + 1)) = 20000 Hz
	TMR3 = 0;               // Reset timer T2 count register
	T3CONbits.TON = 1;      // Enable timer T2 (must be the last command of
	                        // the timer configuration sequence)

	/* ===================
	 * Motor1 PWM
	 */
	OC1CONbits.OCM = 6;     // PWM mode on OCx; fault pin disabled
	OC1CONbits.OCTSEL = 1;  // Use timer T3 as the time base for PWM generation
	OC1RS = 0;              //
	OC1CONbits.ON = 1;      // Enable OC1 module

	/* ===================
	 * Motor2 PWM
	 */
	OC2CONbits.OCM = 6;     // PWM mode on OCx; fault pin disabled
	OC2CONbits.OCTSEL = 1;  // Use timer T3 as the time base for PWM generation
	OC2RS = 0;              //
	OC2CONbits.ON = 1;      // Enable OC2 module

	/* ===================
	 * Servo PWM
	 */
	OC5CONbits.OCM = 6;     // PWM mode on OCx; fault pin disabled
	OC5CONbits.OCTSEL = 0;  // Use timer T2 as the time base for PWM generation
	OC5RS = 0;              //
	OC5CONbits.ON = 1;      // Enable OC5 module

	IFS0bits.T2IF = 0;
	IPC2bits.T2IP = 1;
	IEC0bits.T2IE = 1;      // Enable Timer 2 interrupts

	robot_setServo(0); /// \todo Don't call function

	EnableInterrupts(); /// \todo Move to the end of the function?

	/* ===================
	 * IO Config
	 */
	/* 1-Bridge control */
	STDBY = 1;                  // Half-Bridge ON

	M1_IN1 = M1_IN2 = 0;        // STOP
	M2_IN1 = M2_IN2 = 0;        // STOP

	TRISCbits.TRISC14 = OUT;    // STDBY
	TRISBbits.TRISB5 = OUT;     // M1_IN1
	TRISCbits.TRISC13 = OUT;    // M1_IN2

	TRISBbits.TRISB13 = OUT;    // M2_IN1
	TRISFbits.TRISF3 = OUT;     // M2_IN2

	/* 2-Leds */
	LATECLR = 0x000F;           // Leds 4-1 OFF
	LATBCLR = 0x8000;           // Led 5 OFF
	TRISECLR = 0x000F;          // RE3-0 as output
	TRISBCLR = 0x8000;          // RB15 as output

	/* 3-Sensors */
	LATBbits.LATB10 = 0;        // Disable Obstacle sensors output
	TRISBbits.TRISB10 = OUT;    // EN_OBST_SENS as output
	TRISBbits.TRISB9 = IN;      // IV BEACON as output

    LATECLR = 0x0020;           // Disable line sensor
	TRISEbits.TRISE5 = OUT;     // EN_GND_SENS as output

	LATD = LATD | 0x00EC;       // Line sensor: output latches must be set
	TRISD = TRISD & ~(0x00EC);  // Line sensor: 5 bits as output

	/* 4- start/stop buttons */
	CNPUE = CNPUE | 0x60;       // Activate weak pull-ups in input ports RB3 and RB4

	/* ADC Config */
	AD1PCFGbits.PCFG0 = 0;      // RB0 configured as analog input (AN0)
	AD1PCFGbits.PCFG1 = 0;      // RB1 configured as analog input (AN1)
	AD1PCFGbits.PCFG2 = 0;      // RB2 configured as analog input (AN2)
	AD1PCFGbits.PCFG11 = 0;     // RB11 configured as analog input (AN11)

	AD1CON1bits.SSRC = 7;       // Conversion trigger: internal counter ends
	                            //  sampling and starts conversion
	AD1CON1bits.CLRASAM = 1;    // Stop conversions when the 1st A/D converter
	                            //  interrupt is generated. At the same time,
	                            //  hardware clears the ASAM bit
	AD1CON3bits.SAMC = 16;      // Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI = 2 - 1;   // Interrupt is generated after 2 samples
	AD1CON1bits.ON = 1;         // Enable A/D converter

	/* Encoders */
	INTCONbits.INT1EP = 1;      // interrupt generated on rising edge
	INTCONbits.INT4EP = 1;      // interrupt generated on rising edge

	IPC1bits.INT1IP = 4;
	IPC4bits.INT4IP = 4;

	IFS0bits.INT1IF = 0;
	IFS0bits.INT4IF = 0;

	IEC0bits.INT1IE = 1;        // Enable INT1 interrupts
	IEC0bits.INT4IE = 1;        // Enable INT4 interrupts

	/* Reset variables */
	counter_m1 = 0;             // Reset counters
	counter_m2 = 0;             //

	ticker.ticks = 0;           // Reset 10ms ticker
}

void inline robot_enableObstSens ( void )
{
	LATBbits.LATB10 = 1;
}

void inline robot_disableObstSens ( void )
{
	LATBbits.LATB10 = 0;
}

void inline robot_enableGroundSens ( void )
{
	LATEbits.LATE5 = 1;
}

void inline robot_disableGroundSens ( void )
{
	LATEbits.LATE5 = 0;
}


/* ==========================================================================
 * Sensors
 */

void robot_readSensors ( void )
{
	static int channels[] = {0, 1, 2, 11}; /// \todo Use defines for channels

	int i;

	for(i = 0; i < 4; i++) {
		AD1CHSbits.CH0SA = channels[i];           // Select analog channel
		AD1CON1bits.ASAM = 1;                     // Start conversion
		while (IFS1bits.AD1IF == 0);              // Wait until AD1IF = 1

		sensors.array[i] = (ADC1BUF0 + ADC1BUF1) / 2;

		IFS1bits.AD1IF = 0;                       // Clean IF
	}

	sensors.array[4] = getGroundSensors();
}

void robot_readEncoders ( void )
{
	DisableInterrupts();
	sensors.enc_left  = counter_m1;
	sensors.enc_right = counter_m2;
	counter_m1 = 0;
	counter_m2 = 0;
	EnableInterrupts();
}

uint inline robot_readBeaconSens ( void )
{
	return PORTBbits.RB9;
}

uint inline robot_startBtn ( void )
{
	return (!PORTBbits.RB3);
}

uint inline robot_stopBtn ( void )
{
	return (!PORTBbits.RB4);
}


/* ==========================================================================
 * Actuators
 */

void robot_setVel2 ( int velL, int velR )
{
	DisableInterrupts();

	actuators.vel_left  = velL > 100 ? 100 : (velL < -100 ? -100 : velL);
	actuators.vel_right = velR > 100 ? 100 : (velR < -100 ? -100 : velR);

	EnableInterrupts();
}

void robot_setServo ( int pos )
{
#ifdef SERVO_MIN_PWM_IS_LEFT
	pos = pos < SERVO_POS_LEFT ? SERVO_POS_LEFT : pos;
	pos = pos > SERVO_POS_RIGHT ? SERVO_POS_RIGHT : pos;
	pos += -SERVO_POS_LEFT; // PWM is minimum @ left position
#else
	pos = pos < SERVO_POS_LEFT ? SERVO_POS_LEFT : pos;
	pos = pos > SERVO_POS_RIGHT ? SERVO_POS_RIGHT : pos;
	pos = -pos;
	pos += SERVO_POS_RIGHT; // PWM is minimum @ right position
#endif

	actuators.servo_pos = pos;
	OC5RS = ((SERVO_WIDTH_MIN * T2_FREQ) / 1000  + pos * SERVO_K) + 1;
}

void robot_setLed ( int ledNr )
{
	if (ledNr < 0 || ledNr > 3)
		return;

	LATE = LATE | (1 << ledNr);
	actuators.leds = LATE & 0x0f;
}

void robot_resetLed ( int ledNr )
{
	if (ledNr < 0 || ledNr > 3)
		return;

	LATE = LATE & ~(1 << ledNr);
	actuators.leds = LATE & 0x0f;
}


/* ==========================================================================
 * Helper functions
 */

uint getGroundSensors ( void )
{
	uint sensValue;

// The reading of the line sensor can be done here. However, if long loops are being used
//  the integration process allows the capacitors to charge completely; in that case the
//  read value will be always 0.

//	sensValue = PORTD >> 2;
//	sensValue = (sensValue & 0x0003) | ((sensValue & 0x38) >> 1);

// discharge capacitors (3 us should be enough)
    LATECLR = 0x0020;			// Disable line sensor
	LATD = LATD | 0x00EC;		// All 5 outputs set (just in case, set in initPIC32() )
	TRISD = TRISD & ~(0x00EC);	// 5 bits as output
	delay(2);					// Wait, discharging capacitors (200 us)

// charge capacitors
	TRISD = TRISD | 0x00EC;		// 5 bits as input
    LATESET = 0x0020;			// Enable line sensor
	delay(60);					// wait 6 ms
								// this time is critical... capacitors take time to charge
								// too little time: output capacitors don't charge enough

// Read the value
	sensValue = PORTD >> 2;
	sensValue = (sensValue & 0x0003) | ((sensValue & 0x38) >> 1);

	return sensValue;
}

int avfilter_mleft ( int vel )
{
	static int i   = 0;
	static int sum = 0;
	static int buf[4] = {0, 0, 0, 0};

	sum = sum - buf[i] + vel;
	buf[i++] = vel;

#ifndef SOFT_SLOPE
	i &= 0x01;
	return sum / 2;
#else
	i &= 0x03;
	return sum / 4;
#endif
}

int avfilter_mright(int vel)
{
	static int i   = 0;
	static int sum = 0;
	static int buf[4] = {0, 0, 0, 0};

	sum = sum - buf[i] + vel;
	buf[i++] = vel;

#ifndef SOFT_SLOPE
	i &= 0x01;
	return sum / 2;
#else
	i &= 0x03;
	return sum / 4;
#endif
}

/* ===================
 * delay() - input: value in 1/10 ms
 */
void delay ( uint tenth_ms )
{
	tenth_ms = tenth_ms > 500000 ? 500000 : tenth_ms;

	resetCoreTimer();
	while(readCoreTimer() <= (2000 * tenth_ms));
}

/* ===================
 * wait() - input: value in 1/10 s
 */
void wait ( uint tenth_seconds )
{
	resetCoreTimer();
	while(readCoreTimer() <= (2000000 * tenth_seconds ));
}


/* ==========================================================================
 * Interrupt Service Routines
 */

/* ===================
 * Interrupt Service routine - Timer2
 */
void _int_(_TIMER_2_VECTOR) isr_t2(void)
{
	static int cntT2Ticks = 0;

	int velL, velR;

	cntT2Ticks++;
	ticker.ticks = cntT2Ticks;

#ifdef SOFT_SLOPE
	if((cntT2Ticks % 2) == 0)
#endif
	{
		velL = actuators.vel_left;
//		velL = avfilter_mleft(actuators.vel_left);

		velR = actuators.vel_right;
//		velR = avfilter_mright(actuators.vel_right);

		if(velL < 0) {
			velL = -velL;
			M1_REVERSE;
		} else {
			M1_FORWARD;
		}

		if(velR < 0) {
			velR = -velR;
			M2_REVERSE;
		} else {
			M2_FORWARD;
		}

		OC1RS = ((PR3+1)*velL) / 100;
		OC2RS = ((PR3+1)*velR) / 100;
	}

	IFS0bits.T2IF = 0;
}

/* ===================
 * Interrupt Service routine - External Interrupt 1 (encoder M1)
 */
void _int_(_EXTERNAL_1_VECTOR) isr_enc_m1(void)
{
	if(PORTEbits.RE6 == 1)
		counter_m1++;
	else
		counter_m1--;

	IFS0bits.INT1IF = 0;

}

/* ===================
 * Interrupt Service routine - External Interrupt 4 (encoder M2)
 */
void _int_(_EXTERNAL_4_VECTOR) isr_enc_m2(void)
{
	if(PORTEbits.RE7 == 1)
		counter_m2++;
	else
		counter_m2--;

	IFS0bits.INT4IF = 0;
}


/* = EOF ==================================================================== */
