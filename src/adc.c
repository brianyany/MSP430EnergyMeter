/*
 * adc.c
 *
 *  Created on: Jan 10, 2021
 *      Author: yanyc
 */

#include "adc.h"

#ifndef DEFAULT_READ_RESOLUTION
#define DEFAULT_READ_RESOLUTION 10
#endif
static int _readResolution = DEFAULT_READ_RESOLUTION;

#define ADC10ENC ENC

const uint32_t digital_pin_to_analog_in[20] = { NOT_ON_ADC,
                                                0b0000, 0b0001,
                                                0b0010, 0b0011,
                                                0b0100, 0b0101,
                                                NOT_ON_ADC, NOT_ON_ADC,
                                                NOT_ON_ADC, NOT_ON_ADC,
                                                NOT_ON_ADC, NOT_ON_ADC,
                                                0b0110, 0b0111,
                                                NOT_ON_ADC, NOT_ON_ADC,
                                                NOT_ON_ADC, NOT_ON_ADC,
                                                NOT_ON_ADC };

uint16_t analog_reference = SREF_0;
uint16_t analog_period = F_CPU / 490;
uint16_t analog_div = ID_0;
uint16_t analog_res = 0xFF;

static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to)
{
    if (from == to)
        return value;
    if (from > to)
        return value >> (from - to);
    else
        return value << (to - from);
}

/*
 * read the analog value of a single adc channel
 * */
uint16_t readAnalogValue(uint8_t pin)
{
// make sure we have an ADC
    uint8_t channel;

    // Check if pin is a special analog pin (A10 = temp sensor, A11 = Vcc/2, etc.)
    if (pin >= 128)
        channel = pin - 128;
    else
        channel = digitalPinToADCIn(pin);

    // Check if pin is valid
    if (channel == NOT_ON_ADC)
        return 0;
    //  0000 A0
    //  0001 A1
    //  0010 A2
    //  0011 A3
    //  0100 A4
    //  0101 A5
    //  0110 A6
    //  0111 A7
    //  1010 Internal temperature sensor

    //TODO: Only int. temp. sensor requires Tsample > 30us.
    // The below ADC configuration applies this rule to all channels right now.
    // ADC10CLK = 5MHz / 5 = 1Mhz
    // Tsample = S&H / ADC10CLK = 64 / 1 MHz = 64 us
    // Tconvert = 13 / ADC10CLK = 13 / 1 MHz = 13 us
    // Total time per sample = Tconvert + Tsample = 64 + 13 = 67 us = ~15k samples / sec

    ADC10CTL0 &= ~ADC10ENC;                 // disable ADC
    ADC10CTL1 = ADC10SSEL_0 | ADC10DIV_4;   // ADC10OSC as ADC10CLK (~5MHz) / 5
    ADC10CTL0 = analog_reference | // set analog reference
            ADC10ON | ADC10SHT_3 | ADC10IE; // turn ADC ON; sample + hold @ 64 × ADC10CLKs; Enable interrupts
    ADC10CTL1 |= (channel << 12);               // select channel
    ADC10CTL1 |= ADC10DF;
    ADC10AE0 = (1 << channel);             // Disable input/output buffer on pin
    __delay_cycles(128);                    // Delay to allow Ref to settle
    ADC10CTL0 |= ADC10ENC | ADC10SC;        // enable ADC and start conversion
    while (ADC10CTL1 & ADC10BUSY)
    {         // sleep and wait for completion
        __bis_SR_register(CPUOFF + GIE);    // LPM0 with interrupts enabled
    }
    /* POWER: Turn ADC and reference voltage off to conserve power */
    ADC10CTL0 &= ~(ADC10ENC);
    ADC10CTL0 &= ~(ADC10ON | REFON);

    return mapResolution(ADC10MEM, DEFAULT_READ_RESOLUTION, _readResolution);

}

uint16_t analogValuetoVoltage(uint16_t value)
{
    return value * (3570 / 1023.0);    // 3000mV
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
