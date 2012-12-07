# libmr - A not so low level library for Micro Rato

libmr is a C library to program a [Micro Rato], providing from the low level
interaction with the robot, to more high level movements, like precise
rotations and obstacle avoidance.

This library abstracts the complexity of handling the hardware (mcu, sensors and
actuators), and gives the user a simple interface allowing the user to focus
on the development of high level algorithms to make the mouse find it's cheese.

## Features
 - Hardware configuration and operation
 - PI control for the motors
 - High level movements using standard units (degrees, m, m/s)
  - Spin (degrees)
  - Move forward/backward (cm)
 - Bump detection and control
 - Obstacle avoidance

Beyond the high level interface, libmr also exposes low level functions, which
together with it's high configurability, allows more advance users to implement
their own low level algorithms.


  [micro rato]: (http://microrato.ua.pt)
