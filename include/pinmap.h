/*
 * pinmap.h
 *
 *  Created on: Jan 10, 2021
 *      Author: yanyc
 */

#ifndef INCLUDE_PINMAP_H_
#define INCLUDE_PINMAP_H_

#include  "msp430g2553.h"


// Note: the actual PIN mapping is actually 1 indexed
#define PIN1    0
#define PIN2    1
#define PIN3    2
#define PIN4    3
#define PIN5    4
#define PIN6    5
#define PIN7    6
#define PIN8    7
#define PIN9    8
#define PIN10   9
#define PIN11   10
#define PIN12   11
#define PIN13   12
#define PIN14   13
#define PIN15   14
#define PIN16   15
#define PIN17   16
#define PIN18   17
#define PIN19   18
#define PIN20   19

#define A0  PIN2
#define A1  PIN3
#define A2  PIN4
#define A3  PIN5
#define A4  PIN6
#define A5  PIN7
#define A6  PIN14
#define A7  PIN15

#define RED_LED     PIN2
#define GREEN_LED   PIN14

#define BTN2        PIN5

#define A0_ADC_CHANNEL  INCH_0
#define A1_ADC_CHANNEL  INCH_1
#define A2_ADC_CHANNEL  INCH_2
#define A3_ADC_CHANNEL  INCH_3
#define A4_ADC_CHANNEL  INCH_4
#define A5_ADC_CHANNEL  INCH_5
#define A6_ADC_CHANNEL  INCH_6
#define A7_ADC_CHANNEL  INCH_7

#endif /* INCLUDE_PINMAP_H_ */
