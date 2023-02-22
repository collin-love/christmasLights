/*
 * my_utilities.c
 *
 *  Created on: Feb 13, 2023
 *      Author: collinlove
 * 
 * 	Credits to: Lalit Pandit and TA's
 *  Credits to: Alexander Dean - https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_2/Source/main.c
 *  Credits to: Ben Roloff - https://forum.digikey.com/t/using-the-capacitive-touch-sensor-on-the-frdm-kl46z/13246 
 */

#include <MKL25Z4.h>
#include "MACROS.h"
#include <stdio.h>

void delay(volatile unsigned int time_msec){
	
	// convert from user input msec to counters
	int time_delay = time_msec * DELAY_CONVERSION_FACTOR;
 	
	// decrement time_delay counter
	while(time_delay > 0){
		time_delay--;
	}
}

void led_init(){
	
	// allow clock access to port b / d (RGB leds)
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
	// pin control register clear
	PORTB->PCR[RED_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;
	// pin control register mux
	PORTB->PCR[RED_LED_SHIFT] |= PORT_PCR_MUX(1);
	PORTB->PCR[GREEN_LED_SHIFT] |= PORT_PCR_MUX(1);
	PORTD->PCR[BLUE_LED_SHIFT] |= PORT_PCR_MUX(1);
	// set direction (output)
	GPIOB->PDDR |= (1 << RED_LED_SHIFT);	
	GPIOB->PDDR |= (1 << GREEN_LED_SHIFT);
	GPIOD->PDDR |= (1 << BLUE_LED_SHIFT);

}

void touch_init(){
	// set clock
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;
	// not in range
	TSI0->GENCS |= TSI_GENCS_OUTRGF_MASK;
	// for capacitive reading
	TSI0->GENCS |= TSI_GENCS_MODE(0);
	// reference charge
	TSI0->GENCS |= TSI_GENCS_REFCHRG(0);
	// volatage range
	TSI0->GENCS |= TSI_GENCS_DVOLT(0);
	// external charge
	TSI0->GENCS |= TSI_GENCS_EXTCHRG(0);
	// prescalar
	TSI0->GENCS |= TSI_GENCS_PS(0);
	// scans per electrode
	TSI0->GENCS |= TSI_GENCS_NSCN(31);
	// enable touch sensitive input (tsi)
	TSI0->GENCS |= TSI_GENCS_TSIEN_MASK;
	// enable tsi low power input
	TSI0->GENCS |= TSI_GENCS_STPE_MASK;
	// end of scan clear bit
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK;

}

// Turn on RGBW Led

void color_on(int color){
	
	if (color == RED){
		// turn on red
		GPIOB->PCOR |= (1 << RED_LED_SHIFT);
	}
	if (color == GREEN){
		// turn on green
		GPIOB->PCOR |= (1 << GREEN_LED_SHIFT);	
	}
	if (color == BLUE){
		// turn on blue
		GPIOD->PCOR |= (1 << BLUE_LED_SHIFT);
	}		
	if (color == WHITE){
		// turn on RGB aka white
		GPIOB->PCOR |= (1 << RED_LED_SHIFT);
		GPIOB->PCOR |= (1 << GREEN_LED_SHIFT);		
		GPIOD->PCOR |= (1 << BLUE_LED_SHIFT);
	}


}

void led_off(){
	
	// turn off RGB
	GPIOB->PSOR |= (1 << RED_LED_SHIFT);
	GPIOB->PSOR |= (1 << GREEN_LED_SHIFT);		
	GPIOD->PSOR |= (1 << BLUE_LED_SHIFT);

}


int touch_scan_10(){
	
	int value;
	// channel 10
	TSI0->DATA &= 0;
	TSI0->DATA |= TSI_DATA_TSICH(10);
	// printf("TSI0->DATA 10: %p\n", TSI0->DATA);
	TSI0->DATA |= TSI_DATA_SWTS_MASK;
	value = SCAN_DATA;
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK;
	// return scanned value from TSI
	return value - SCAN_OFFSET;

}

// initial startup sequence
void init_sequence(){
	
	// loop through twice
	int count = TWICE;

	// do operation twice
	while(count--){

		// block 1/3: flash white, delay
		LOG("Change LED to White\n");
		color_on(WHITE);
		delay(HALF_SECOND);
		led_off();
		delay(TENTH_SECOND);

		// block 2/4: flash blue, delay
		LOG("Change LED to Blue\n");
		color_on(BLUE);
		delay(HALF_SECOND);
		led_off();
		delay(TENTH_SECOND);
	}

	// start timer
	LOG("START TIMER 3s\n");
	delay(THREE_SECOND);
}

// WOULD LIKE TO TURN THE THREE LED PATTERNS INTO ONE FUNCTION TAKING IN COLOR INPUT
// BUT color_on() FUNCTION AS IS BLURS LEDS ON MY MCU
void main_led_pattern(){

	// iterate through 8.5s in "counters"
	for(int counter = 0; counter <= EIGHT_HALF_SECOND_CONVERTED; counter++){

		// TSI Input: Left or Right (exit)
		if (touch_scan_10() > TSI_THRESHOLD){
			break;
		}

		// BLOCK 1 RED (0.5s)
		if ((counter > 0) && (counter <= HALF_SECOND_CONVERTED)){
			// block 1: flash red for time in "counters"
			if(counter == 1){
				LOG("Change LED to Red\n");
			}
			delay(TENTH_SECOND);
			color_on(RED);
		}

		// BLOCK 2 GREEN (1s)
		if ((counter > ONE_SECOND_CONVERTED) && (counter <= TWO_SECOND_CONVERTED)){
			// block 2: flash green for time in "counters"
			if(counter == 25){
				LOG("Change LED to Green\n");
			}
			delay(TENTH_SECOND);
			color_on(GREEN);

		}

		// BLOCK 3: RED (2s)
		if ((counter > TWO_HALF_SECOND_CONVERTED) && (counter <= FOUR_HALF_SECOND_CONVERTED)){
			// block 3: flash red for time in "counters"
			if(counter == 61){
				LOG("Change LED to Red\n");
			}
			delay(TENTH_SECOND);
			color_on(RED);

		}

		// BLOCK 4: GREEN (3s)
		if ((counter > FIVE_SECOND_CONVERTED) && (counter <= EIGHT_SECOND_CONVERTED)){
			// block 2: flash green for time in "counters"
			if(counter == 121){
				LOG("Change LED to Green\n");
			}
			delay(TENTH_SECOND);
			color_on(GREEN);

		}

		if (counter == EIGHT_HALF_SECOND_CONVERTED){
			// countinue forever until tsi input
			counter = 0;
		}

		// leds off for time in "counters"
		if (((counter > HALF_SECOND_CONVERTED) && (counter <= ONE_SECOND_CONVERTED)) ||
			((counter > TWO_SECOND_CONVERTED) && (counter <= TWO_HALF_SECOND_CONVERTED)) ||
			((counter > FOUR_HALF_SECOND_CONVERTED) && (counter <= FIVE_SECOND_CONVERTED)) ||
			((counter > EIGHT_SECOND_CONVERTED) && (counter <= EIGHT_HALF_SECOND_CONVERTED)))
			{
			// half second delay
			led_off();

		}

	}
}

void solid_led_pattern(int color){
	
	// iterate through 8.5s in "counters"
	for(int counter = 0; counter <= EIGHT_HALF_SECOND_CONVERTED; counter++){

		if(color == RED){
			// TSI Input: Left (exit)
			if (touch_scan_10() > TSI_CENTER){
				color = GREEN;
				break;
			}
		}

		if(color == GREEN){
			// TSI Input: Left (exit)
			if ((touch_scan_10() > TSI_THRESHOLD) && (touch_scan_10() <= TSI_CENTER)){
				color = RED;
				break;
			}
		}

		// BLOCK 1 RED (0.5s)
		if ((counter > 0) && (counter <= HALF_SECOND_CONVERTED)){
			// block 1: flash red for time in "counters"
			delay(TENTH_SECOND);
			color_on(color);
		}

		// BLOCK 2 GREEN (1s)
		if ((counter > ONE_SECOND_CONVERTED) && (counter <= TWO_SECOND_CONVERTED)){
			// block 2: flash red for time in "counters"
			delay(TENTH_SECOND);
			color_on(color);

		}

		// BLOCK 3: RED (2s)
		if ((counter > TWO_HALF_SECOND_CONVERTED) && (counter <= FOUR_HALF_SECOND_CONVERTED)){
			// block 3: flash red for time in "counters"
			delay(TENTH_SECOND);
			color_on(color);

		}

		// BLOCK 4: GREEN (3s)
		if ((counter > FIVE_SECOND_CONVERTED) && (counter <= EIGHT_SECOND_CONVERTED)){
			// block 2: flash red for time in "counters"
			delay(TENTH_SECOND);
			color_on(color);

		}

		if (counter == EIGHT_HALF_SECOND_CONVERTED){
			// countinue forever until TSI input RHS
			counter = 0;
		}

		// countinue forever until TSI input RHS
		if (((counter > HALF_SECOND_CONVERTED) && (counter <= ONE_SECOND_CONVERTED)) ||
			((counter > TWO_SECOND_CONVERTED) && (counter <= TWO_HALF_SECOND_CONVERTED)) ||
			((counter > FOUR_HALF_SECOND_CONVERTED) && (counter <= FIVE_SECOND_CONVERTED)) ||
			((counter > EIGHT_SECOND_CONVERTED) && (counter <= EIGHT_HALF_SECOND_CONVERTED)))
			{
			// half second delay
			led_off();

		}

	}
}
