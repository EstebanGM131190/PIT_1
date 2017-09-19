/*
 /*
 * Copyright (c) 2016, NXP Semiconductor, Inc.
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
 * @file    PIT_Delay.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "PIT.h"
#include "NVIC.h"
#include "GPIO.h"
#define SYSTEM_CLOCK 21000000		/** 21MHz */
#define DELAY 0.25f					/** 25ms delay */


int main(void) {
	GPIO_pinControlRegisterType pinControlRegisterPORTD = GPIO_MUX1;	/** PORT D as GPIO (configured by the MUX field in PCR register) */
	GPIO_clockGating(GPIO_D);	/** activating the port D clock */
	GPIO_pinControlRegister(GPIO_D,BIT0,&pinControlRegisterPORTD);	/** Configures the PORT D pin 0 as GPIO */
	GPIO_dataDirectionPIN(GPIO_D,GPIO_OUTPUT,BIT0);	/** configures PORT D pin 0 as output */
	GPIO_setPIN(GPIO_D,BIT0);	/** establish a secure value of 1 in the pin */
	PIT_clockGating();	/** activates the PIT clock */
	NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_10);	/** enables the PIT_0 interrupt, and gives it a priority level of 10 */
	EnableInterrupts;	/** enables global interrupts */

    while(1) {
    	GPIO_tooglePIN(GPIO_D,BIT0);	/** switches the current value of the PORT D pin 0 (to 0 in this case) */
    	PIT_clear();	/** clears the local variable "flag" */
		PIT_delay(PIT_0,SYSTEM_CLOCK,DELAY);	/** sets the PIT_0 LDVAL register with a number of cycles in order to generate a determined delay in seconds, also it enables the timer */
		while(FALSE == PIT_getIntrStutus(PIT_0));	/** while there hasn't been an interrupt */
		GPIO_tooglePIN(GPIO_D,BIT0);	/** switches the current value of the PORT D pin 0 (to 0 in this case) */
		PIT_clear();	/** clears the local variable "flag" */
		PIT_delay(PIT_0,SYSTEM_CLOCK,DELAY);	/** sets the PIT_0 LDVAL register with a number of cycles in order to generate a determined delay in seconds, also it enables the timer */
		while(FALSE == PIT_getIntrStutus(PIT_0));	/** while there hasn't been an interrupt */
    }
    return 0;
}
