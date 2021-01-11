/*
 * data.h
 *
 *  Created on: Jan 9, 2021
 *      Author: yanyc
 */

#ifndef DATA_H_
#define DATA_H_

#include "settings.h"

typedef struct {
    int32_t raw_samples[NUM_ADC_CHANNELS];
} adc_data_t;

typedef struct {
    adc_data_t adc;
} energy_data_t;

#endif /* DATA_H_ */
