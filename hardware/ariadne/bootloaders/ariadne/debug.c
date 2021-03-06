/* Name: debug.c
 * Author: .
 * Copyright: Arduino
 * License: GPL http://www.gnu.org/licenses/gpl-2.0.html
 * Project: eboot
 * Function: Utility routines for bootloader debugging
 * Version: 0.2 tftp / flashing functional, serial flashing
 */

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"
#include "debug.h"


#ifdef _VERBOSE
void trace(char* msg)
{
	uint8_t c;
	if(*msg != '\0') {
		while((c = *msg++)) putch(c);
	}
}

void traceln(char* msg)
{
	trace("\r\n");
	trace(msg);
}

void tracehex(uint16_t num, uint8_t len)
{
	trace("0x");
	while(len > 0) {
		puthex(num >> (4 * (len - 1)));
		len--;
	}
}


#ifdef _DEBUG_STEP
void stepInit()
{
	PORTB |= _BV(PB0);
	traceln(" Dbg: Button stepping enabled");
}


/* FIXME: the button is reverse, shortcircuiting when it
 * is released. Code was modified accordingly */
uint8_t checkbutton()
{
	/* the button is pressed when BUTTON_BIT is clear */
	if(bit_is_clear(PINB, PB0)) {
		_delay_ms(25);
		if(bit_is_clear(PINB, PB0)) return 0;
	}
	return 1;
}


void step()
{
	while(1) if(checkbutton()) break;
	_delay_ms(250); // Lock input
}
#endif
#endif
