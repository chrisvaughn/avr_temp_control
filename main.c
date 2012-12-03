/* Name: main.c
 * Author: Chris Vaughn
 * Copyright: (c) 2012
 * License: MIT
 */

#include <stdio.h>
#include <math.h>
#include <avr/io.h>
#include <util/delay.h>

#include "HD44780.h"


float update_world(uint8_t element_on, float current_temp)
{
    float positive_change_per_step = 0.2;
    float negative_change_per_step = 0.1;
    if (element_on == 1)
        current_temp += positive_change_per_step;
    else
        current_temp -= negative_change_per_step;

    if (current_temp < 0.001 && current_temp > -0.001)
        current_temp = 0.0;

    return current_temp;
}

int main(void)
{
    lcd_init();

    float current_temp = 100.0;
    uint16_t set_temp = 110.0;
    uint8_t element_on = 0;
    char display_str[255] = {0};

    while(1)
    {
        current_temp = update_world(element_on, current_temp);

        if (current_temp > set_temp)
            element_on = 0;
        else
            element_on = 1;

        uint16_t disp_temp = (int)round(current_temp);
        char *element_status = (element_on == 1) ? "ON": "OFF";
        sprintf(display_str,"Current: %d\nSet: %d  Element: %s", disp_temp, set_temp, element_status);
        lcd_clrscr();
        lcd_home();
        lcd_string(display_str);

        _delay_us(1000000);
    }
}