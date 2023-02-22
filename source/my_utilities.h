/*
 * my_utilities.h
 *
 *  Created on: Feb 13, 2023
 *      Author: collinlove
 */

#ifndef _MY_UTILITIES_H_
#define _MY_UTILITIES_H_

/*
Delay Function, input is in msec
 */
void delay(volatile unsigned int time_msec);

/*
Set up leds, this prepares them to be turned on
| */
void led_init();

/*
Initial touch sensor, this prepares TSI to scan
 */
void touch_init();

/*
Scan for touch channel 10 (if touch left red/ if touch right green)
 */
int touch_scan_10();

/*
Takes in color input (RGBW) and turns on led
 */
void color_on(int color);

/*
Turns all leds off
 */
void led_off();

/*
Initial light up sequence followed by 3s start delay:

Start up sequence: white (0.5s), delay, blue (0.5s), delay, 
white (0.5s), delay, blue (0.5s), delay

*/
void init_sequence();


/* Main sequence: Exit if TSI

Enter an infinite loop: red (0.5s), delay, green (1s), delay, 
red (2s), delay, green (3s), delay , back to top 

*/
void main_led_pattern();


/* Red sequence: Exit if TSI Right | Green sequence: Exit if TSI Left

Enter an infinite loop: color (0.5s), delay, color (1s), delay, 
color (2s), delay, color (3s), delay , back to top 

*/
void solid_led_pattern(int color);


#endif // _MY_UTILITIES_H_
