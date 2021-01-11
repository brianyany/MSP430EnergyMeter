/*
 * adc.h
 *
 *  Created on: Jan 10, 2021
 *      Author: yanyc
 */

#ifndef INCLUDE_ADC_H_
#define INCLUDE_ADC_H_

#include "msp430g2553.h"
#include "settings.h"

extern const uint32_t digital_pin_to_analog_in[];

#define NOT_ON_ADC 0xFF

#define digitalPinToADCIn(P)      ( digital_pin_to_analog_in[P] )

__interrupt void ADC10_ISR(void);

uint16_t readAnalogValue(uint8_t pin);

uint16_t analogValuetoVoltage(uint16_t value);

#endif /* INCLUDE_ADC_H_ */
