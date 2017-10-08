/*H**********************************************************************
* FILENAME :        ADC_STL.h            
*
* DESCRIPTION :
*       ADC Library for PIC16 (8bit) microcontrollers 
*
* NOTES :
*       Designed for PIC16F1517 (RexPIC-8)
*       Copyright Swiss TI Lab 2017
*       https://www.swisstilab.com/en/
* 
* LICENSE:
*      CC-BY-SA
* 
* AUTHOR :    Kevin Ceresa        START DATE :    08 Oct 2017
*
* CHANGES :
*
* REF NO    VERSION   DATE      WHO     DETAIL
* 1         V1I1      08Oct17   KC      Released
*
*H*/

#ifndef ADC_STL_H
#define	ADC_STL_H

//ADSC Register Bits (conv_clk)
const unsigned short ADC_FOSC_2 = 0b000;
const unsigned short ADC_FOSC_8 = 0b001;
const unsigned short ADC_FOSC_32 = 0b010;
const unsigned short ADC_FRC = 0b011;
const unsigned short ADC_FOSC_4 = 0b100;
const unsigned short ADC_FOSC_16 = 0b101;
const unsigned short ADC_FOSC_64 = 0b110;

//ADPREF Register Bits (ad_ref)
const unsigned short ADC_VDD = 0; //Vref connected to VDD
const unsigned short ADC_VREF_P = 0b10; //Vref connected to external VREF+ pin
const unsigned short ADC_FVR = 0b11; //Vref connected to internal Fixed Voltage Reference

//ADC Init function
void ADC_Init(unsigned short conv_clk, unsigned short ad_ref);

//ADC Read function
int ADC_Read(unsigned short channel);

#endif	/* ADC_STL_H */

