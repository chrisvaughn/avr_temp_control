/* Name: main.c
 * Author: Chris Vaughn
 * Copyright: (c) 2012
 * License: MIT
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "HD44780.h"

int main(void)
{
	lcd_init();								// init the LCD screen

	int current_temp = 240;
	int set_temp = 225;

	char szDisp[255] = {0};
    while(1)
    {
		lcd_home();
		sprintf(szDisp,"Current: %d\nSet: %d  Element: %s", current_temp, set_temp, "ON");
		lcd_string(szDisp);
		_delay_us(1000000);
    }
}