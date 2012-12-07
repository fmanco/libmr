# ===========================================================================
# libmr - A lowlevel library for "Micro Rato"
# ===========================================================================

##
 #  \file tests/Makefile
 #
 #  \brief Basic Makefile for test applications
 #
 #  \author Filipe Manco <filipe.manco@gmail.com>
 ##


INC = ../inc/
LIB = $(shell find ../lib/ -name "*.c" -printf "%p ")


all:
	@echo "USAGE: make <test_name>"
	@echo "       make upload"
	@echo "       make clean"

%: %.c
	CPATH=$(INC) pcompile $^ $(LIB)

upload:
	ldpic32 -w $(patsubst %.c, %.hex, $(shell find *.hex))

clean:
	find .. -regex ".*\(\.\(hex\|o\|elf\|map\)\|\(~\)\)" -delete -printf "deleted: %p\n"

.PHONY: all upload clean
