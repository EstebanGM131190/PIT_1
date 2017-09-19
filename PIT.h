/*
 * PIT.h
 *
 *  Created on: 16/08/2017
 *      Author: jlpe
 */

#ifndef PIT_H_
#define PIT_H_

#include "DataTypeDefinitions.h"

/**/
#define PIT_CLOCK_GATING 0x00800000

/*! This enumerated constant are used to select the PIT to be used*/
typedef enum {PIT_0,PIT_1,PIT_2,PIT_3} PIT_Timer_t;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function configure the PIT to generate a delay base on the system clock.
 	 Internally it configures the clock gating and enables the PIT module.
 	 It is important to note that this strictly is not device driver since everything is
 	 contained in a single function, but in general you have to avoid this practices, this only
 	 for the propose of the homework

 	 \param[in] pitTimer timer to be configured
 	 \param[in] systemClock	the system clock frequency given in cycles
 	 \param[in] perior	the desired delay period
 	 \return void
 	 \todo	check if timer 0 overflow values in the comparison are correct
 */
void PIT_delay(PIT_Timer_t pitTimer,float systemClock ,float perior);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables the clock for the PIT module in order to make it work
 	 \param[in] void
 	 \return void
 */
void PIT_clockGating(void);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function is unimplemented because of instruction of the professor
 	 \param[in] void
 	 \return 0
 */
uint8 PIT_interruptFlagStatus(void);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function returns a PIT timer's interrupt flag current status
 	 \param[in] pitTimer selected timer to be analysed
 	 \return the desired PIT timer's interrupt flag status
 */
uint8 PIT_getIntrStutus(PIT_Timer_t pitTimer);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function clears the local variable "flag" in order to make clear the interrupt isn't active
 	 \param[in] void
 	 \return void
 */
void PIT_clear();


#endif /* PIT_H_ */
