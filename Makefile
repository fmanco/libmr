# ===========================================================================
# mrlib - A lowlevel library for "Micro Rato"
# ===========================================================================

##
 #  \file Makefile
 #
 #  \brief Basic Makefile for a mrlib based application
 #
 #  This Makefile builds an application name app.c placed on app folder.
 #  It also allows to upload the application to the MCU.
 #
 #  \author Filipe Manco <filipe.manco@gmail.com>
 ##


APP = app/app.c
INC = inc/
LIB = $(shell find lib/ -name *.c -printf "%p ")


all:
	CPATH=$(INC) pcompile $(APP) $(LIB)

doc:
	doxygen doc/Doxyfile

upload:
	ldpic32 -w $(patsubst %.c, %.hex, $(APP))

clean:
	find . -regex ".*\(\.\(hex\|o\|elf\|map\)\|\(~\)\)" -delete -printf "deleted: %p\n"
	rm -rf doc/latex doc/html


.PHONY: all doc upload clean
