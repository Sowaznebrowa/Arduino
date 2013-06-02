/*
 Copyright (c) 2010 by arms22 (arms22 at gmail.com)
 Microchip 23x256 SPI SRAM library for Arduino

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#include <Arduino.h>
#include <SPI.h>

#include "SPISRAM.h"

SPISRAM::SPISRAM(const byte csPin, const byte addr_width) :
		_csPin(csPin), _addrbus(addr_width) {
	//addr = 0;
}

void SPISRAM::init() {
	pinMode(_csPin, OUTPUT);
	csHigh();
}

byte SPISRAM::read(const long & address) {
	byte data;
	select();
	set_access(READ, address);
	data = SPI.transfer(0);
	deselect();
	return data;
}

void SPISRAM::read(const long & address, byte *buffer, const long & size) {
	writeMode(SEQ_MODE);
	select();
	set_access(READ, address);
	for (unsigned int i = 0; i < size; i++)
		*buffer++ = SPI.transfer(0);
	deselect();
}

void SPISRAM::write(const long & address, byte data) {
//	writeMode(BYTE_MODE);
	select();
	set_access(WRITE, address);
	SPI.transfer(data);
	deselect();
}

void SPISRAM::write(const long & address, byte *buffer, const long & size) {
	writeMode(SEQ_MODE);

	select();
	set_access(WRITE, address);
	for (unsigned int i = 0; i < size; i++)
		SPI.transfer(*buffer++);
	deselect();
}

void SPISRAM::setSPIMode(void) {
	SPI.setBitOrder(MSBFIRST);
	SPI.setClockDivider(SPI_CLOCK_DIV2);
	SPI.setDataMode(SPI_MODE0);
}

void SPISRAM::csLow() {
	digitalWrite(_csPin, LOW);
}

void SPISRAM::csHigh() {
	digitalWrite(_csPin, HIGH);
}

void SPISRAM::select(void) {
	setSPIMode();
	csLow();
}

void SPISRAM::deselect(void) {
	csHigh();
}
