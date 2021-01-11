/*
 * settings.h
 *
 *  Created on: Jan 9, 2021
 *      Author: yanyc
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#define F_CPU 16000000L

#include "pinmap.h"
#include "stdint.h"

typedef enum {
  BATTERY_POSITIVE,
  BATTERY_NEGATIVE,
  SHUNT_HIGH,
  NUM_ADC_CHANNELS
} adc_channel_t ;

typedef enum {
  CURRENT,
  VOLTAGE,
  POWER,
  ENERGY
} display_mode_t ;


#endif /* SETTINGS_H_ */
