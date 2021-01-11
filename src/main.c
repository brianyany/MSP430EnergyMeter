//#include <msp430.h>
#include  "msp430g2553.h"
#include "settings.h"
#include "data.h"
#include "adc.h"
#include <string.h>

#define     LED1                  BIT0
#define     LED2                  BIT6
#define     LED_DIR               P1DIR
#define     LED_OUT               P1OUT

#define     BUTTON                BIT3
#define     BUTTON_OUT            P1OUT
#define     BUTTON_DIR            P1DIR
#define     BUTTON_IN             P1IN
#define     BUTTON_IE             P1IE
#define     BUTTON_IES            P1IES
#define     BUTTON_IFG            P1IFG
#define     BUTTON_REN            P1REN

#define ADC_BITS  10
#define ADC_COUNTS  (1<<ADC_BITS)

void InitializeClocks(void);
void InitializeLeds(void);
void InitializeButton(void);

void InitializeDataStructures(void);

void ConfigADCs(void);
void ConfigGPIOs(void);

energy_data_t energy_meter;

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    InitializeClocks();
    InitializeButton();
    InitializeLeds();

//    ConfigADCs();
    ConfigGPIOs();

    __enable_interrupt();                     // Enable interrupts.

    while (1)
    {
//        ADC10CTL0 &= ~ENC;
//        while (ADC10CTL1 & ADC10BUSY)
//            ;               // Wait if ADC10 core is active
//        ADC10SA =
//                (unsigned int) &(energy_meter.adc.raw_samples[BATTERY_POSITIVE]);
//        ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
//        __bis_SR_register(CPUOFF + GIE);      // LPM0, ADC10_ISR will force exit

        energy_meter.adc.raw_samples[BATTERY_POSITIVE] = (int32_t) analogValuetoVoltage(readAnalogValue(A0));
    }

    return 0;
}

void InitializeClocks(void)
{

    BCSCTL1 = CALBC1_1MHZ;                    // Set range
    DCOCTL = CALDCO_1MHZ;
    BCSCTL2 &= ~(DIVS_3);                     // SMCLK = DCO = 1MHz
}

void InitializeButton(void)                 // Configure Push Button
{
    BUTTON_DIR &= ~BUTTON;
    BUTTON_OUT |= BUTTON;
    BUTTON_REN |= BUTTON;
    BUTTON_IES |= BUTTON;
    BUTTON_IFG &= ~BUTTON;
    BUTTON_IE |= BUTTON;
}

void InitializeLeds(void)
{
    LED_DIR |= LED1 + LED2;
    LED_OUT &= ~(LED1 + LED2);
}

void InitializeDataStructures(void)
{
//    memset()
}

void ConfigADCs(void)
{
    ADC10CTL1 = INCH_2 + CONSEQ_3 + ADC10SSEL_3;
    ADC10CTL0 = ADC10SHT_0 + MSC + ADC10ON + ADC10IE;
    ADC10DTC1 = 0x03;
    ADC10AE0 |= BIT0 + BIT1 + BIT2;
    ADC10SA = (unsigned int) &(energy_meter.adc.raw_samples[BATTERY_POSITIVE]);
}

void ConfigGPIOs(void)
{
//    P1DIR |= BIT1 + BIT2;
    P1DIR &= ~(BIT0 + BIT1 + BIT2);
//    P1OUT |= BIT1 + BIT2;
}
