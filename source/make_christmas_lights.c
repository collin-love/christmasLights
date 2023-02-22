/*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    make_christmas_lights.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "my_utilities.h"
#include "MACROS.h"

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    // init touch
    touch_init();
    // init leds
    led_init(); 

    while(1) {

        /* Start up sequence: white (0.5s), delay, blue (0.5s), delay, 
        white (0.5s), delay, blue (0.5s), delay */

        init_sequence();

        /* Enter an infinite loop: red (0.5s), delay, green (1s), delay, 
        red (2s), delay, green (3s), delay , back to top */

        main_led_pattern();

        while(1) {

            if ((touch_scan_10() > TSI_THRESHOLD) && (touch_scan_10() <= TSI_CENTER)){
            
                // print TSI value
                LOG("Change color to Red, TSI Value: %i\n", touch_scan_10());
                // make sure leds off during a switch
                led_off();
                // flash same pattern red led
                solid_led_pattern(RED);

            }

            if(touch_scan_10() > TSI_CENTER){
            
                // print TSI value
                LOG("Change color to Green, TSI Value: %i\n", touch_scan_10());
                // make sure leds off during a switch
                led_off();
                // flash same pattern green led
                solid_led_pattern(GREEN);
            
            }

        }

    }
    return 0 ;
  }
