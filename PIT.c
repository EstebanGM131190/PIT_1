#include "MK64F12.h"
#include "PIT.h"

uint8 flag = 0;

void PIT0_IRQHandler(){		/** PIT_0 ISR */
	volatile uint8 dummy;	/** dummy variable used to force PIT_0 TCTRL read, so the bug can be solved */
	PIT->CHANNEL[PIT_0].TCTRL &= ~(PIT_TCTRL_TEN_MASK);	/** stops the timer */
	PIT->CHANNEL[PIT_0].TFLG |= PIT_TFLG_TIF_MASK;	/** clears the timer 0 TimeOut flag */
	dummy = PIT->CHANNEL[PIT_0].TCTRL;	/** read control register for clear PIT flag, this is silicon bug */
	PIT->CHANNEL[PIT_0].TCTRL &= ~(PIT_TCTRL_TIE_MASK);	/** disables PIT_0 interrupts */
	flag = TRUE;	/**activates local variable flag in order to make clear an interrupt has ocurred*/
}

void timerInterrupt_Enable(PIT_Timer_t pitTimer){	/** This function enables the desired PIT interrupt */
	switch(pitTimer){
	case PIT_0:
		PIT->CHANNEL[PIT_0].TCTRL |= PIT_TCTRL_TIE_MASK;	/** PIT_0 interrupt enabled */
		break;
	case PIT_1:
		PIT->CHANNEL[PIT_1].TCTRL |= PIT_TCTRL_TIE_MASK;	/** PIT_1 interrupt enabled */
		break;
	case PIT_2:
		PIT->CHANNEL[PIT_2].TCTRL |= PIT_TCTRL_TIE_MASK;	/** PIT_2 interrupt enabled */
		break;
	case PIT_3:
		PIT->CHANNEL[PIT_3].TCTRL |= PIT_TCTRL_TIE_MASK;	/** PIT_3 interrupt enabled */
		break;
	}
}

void Timer_Enable(PIT_Timer_t pitTimer){	/** This function enables the desired PIT */
	switch(pitTimer){
	case PIT_0:
		PIT->CHANNEL[PIT_0].TCTRL |= PIT_TCTRL_TEN_MASK;	/** PIT_0 enabled */
		break;
	case PIT_1:
		PIT->CHANNEL[PIT_1].TCTRL |= PIT_TCTRL_TEN_MASK;	/** PIT_1 enabled */
		break;
	case PIT_2:
		PIT->CHANNEL[PIT_2].TCTRL |= PIT_TCTRL_TEN_MASK;	/** PIT_2 enabled */
		break;
	case PIT_3:
		PIT->CHANNEL[PIT_3].TCTRL |= PIT_TCTRL_TEN_MASK;	/** PIT_3 enabled */
		break;
	}
}

void PIT_delay(PIT_Timer_t pitTimer,float systemClock ,float perior){
	//PIT_clockGating();	/** TODO: ELIMINATE THIS LINE FROM HERE; calls the PIT_clockGating function, in order to enable the internal clock so that the PIT can work */
	PIT->MCR &= ~(PIT_MCR_MDIS_MASK);	/** clears the MDIS field of the PTR_MCR register, enabling PIT timers */
	float period_cycles = ((perior)*(systemClock/2))-1;	/** Calculates the number of cycles for the desired delay period */
	uint32 period_cycles2 = (uint32)period_cycles;
	//if(period_cycles>18446744065119617025){	/**if it exceeds timer 1 and 2 together capacity */
		/** pending to be implemented, timer 1, 2 and 3 */
	//}
	if(period_cycles>4294967295){	/** if it exceeds timer 0 capacity */
		/** pending to be implemented, timer 1 and 2 */
	}else{	/** if timer 0 capacity is enough */
		PIT->CHANNEL[pitTimer].LDVAL = period_cycles2;	/** setup timer 0 for the calculated period cycles */
		timerInterrupt_Enable(pitTimer);	/** enable PIT 0 timer interrupts */
		Timer_Enable(pitTimer);	/** starts PIT 0 timer */
	}
}

void PIT_clockGating(void){		/**This function enables the clock gate for the PIT module*/
	SIM->SCGC6 |= PIT_CLOCK_GATING;		/** Bit 23 of SIM_SCGC6 is  set */
}

uint8 PIT_interruptFlagStatus(void){	/**omitida por instrucciones del profesor*/
	return 0;
}

uint8 PIT_getIntrStutus(PIT_Timer_t pitTimer){	/** This function returns the current status of the Interrupt flag(local variable) */
	return flag;	/** returns current status: interrupt active/not active */
}

void PIT_clear(){	/** This function clears the local variable flag, as the interrupt is not active */
	flag = FALSE;	/** the interrupt flag (local variable) is not active */
}


