/*H**********************************************************************
* FILENAME :        ADC_STL.c            
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

//Include the header file
#include "ADC_STL.h"

//Set the clock
#define _XTAL_FREQ 8000000
#include <xc.h>


/*------------------------------------------------- ADC_Init --------
|  Function ADC_Init
|
|  Purpose:  Set the parameters for the ADC internal block
|
|  Parameters:
|      conv_clk: -- IN -- Select the clock for the A/D conversion
|               1.  ADC_FOSC_2 
|               2.  ADC_FOSC_8 
|               3.  ADC_FOSC_32
|               4.  ADC_FRC 
|               5.  ADC_FOSC_4
|               6.  ADC_FOSC_16
|               7.  ADC_FOSC_64
|      ad_ref: -- IN -- Select the ADC voltage reference
|               1.  ADC_VDD
|               2.  ADC_VREF_P
|               3.  ADC_FVR
|      
|  Returns:  -
*-------------------------------------------------------------------*/
void ADC_Init(unsigned short conv_clk, unsigned short ad_ref)
{
    /*ADC Configuration*/
    ADCON1bits.ADPREF = ad_ref; //Set voltage reference
    ADCON1bits.ADCS = conv_clk; //Set the input clock
    ADCON1bits.ADFM = 1; //Format result 8 bits low 2 bits high
    ADCON0bits.ADON = 1; //Enable the ADC module
    __delay_us(10); //Wait the acquisition time
}

/*------------------------------------------------- ADC_Read --------
|  Function ADC_Read
|
|  Purpose:  Read the value (10 bit ADC) from the selected port
|
|  Parameters:
|      channel: -- IN -- Used for set the port before the reading
|               process.         
|
|  Returns:  returns an int with the value readed from the ADC block
*-------------------------------------------------------------------*/

int ADC_Read(unsigned short channel)
{
    
    ADCON0bits.CHS = channel; //Set ADC input
    
    /*START THE CONVERSION*/
    ADCON0bits.GO_nDONE = 1; //Start conversion
    while(ADCON0bits.GO_nDONE == 1); //Wait the hardware clear (conversion done)
    
    return((ADRESH<<8)|ADRESL);
}