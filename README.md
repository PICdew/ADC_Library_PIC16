# ADC_Library_PIC16
ADC library for PIC16 (Based on the PIC16F1517 MCU)

## Functions
### ADC_Init()
This function will initialize the ADC module.
```C
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
void ADC_Init(unsigned short conv_clk, unsigned short ad_ref);
```
The function need 2 parameters, the ADC clock source and the ADC voltage reference.
### ADC_Read()
This function will return the value readed by the selected channel.
```C
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

int ADC_Read(unsigned short channel);
```
This function need only the channel value as input parameter. See the datasheet of your MCU for more information about the port numeration.

## Example
This simple example will show you how to implement the library. 
This program will get the A/D value on the AN1 port and send it over the UART module.
```C
/*H**********************************************************************
* FILENAME :        main.c            
*
* DESCRIPTION :
*       ADC Library example 
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

#define _XTAL_FREQ 8000000 //8MHz crystal oscillator (necessary for the delay function)
#include <xc.h>

#include "ADC_STL.h"
#include <stdio.h>

void UART_Write(char txData)
{
    while(0 == PIR1bits.TXIF);
    TXREG = txData;    // Write the data byte to the USART.
}

void UART_Init()
{
    //RC6 output
    TRISCbits.TRISC6 = 0;
    ANSELC = 0;  
    // ABDOVF no_overflow; SCKP Non-Inverted; BRG16 16bit_generator; WUE disabled; ABDEN disabled; 
    BAUDCON = 0x08;
    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RCSTA = 0x90;
    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave; 
    TXSTA = 0x24;
    // Baud Rate = 9600; SPBRGL 207; 
    SPBRGL = 0xCF;
    // Baud Rate = 9600; SPBRGH 0; 
    SPBRGH = 0x00;
}

unsigned int adc_value;
char buffer[10];

void main()
{
    /*Port Configuration*/ //Change for your case
    TRISAbits.TRISA1 = 1; //Port RA1 Input
    ANSELAbits.ANSA1 = 1; //Port AN1 (RA1) analog
    
    //Initialize the uart module
    UART_Init();
    
    //Initialize the ADC module
    /*  
     *  CLOCK -> Fosc/2
     *  VREF -> VDD
     */
    ADC_Init(ADC_FOSC_2,ADC_VDD);
    
    while(1) //Infinite cycle
    {
       
        /*START THE CONVERSION*/
        adc_value = ADC_Read(1); //CH1
        
        //Convert the int value to char buffer
        sprintf(buffer,"%d",adc_value);
        
        //Send the value
        for(int i=0;buffer[i]!='\0';i++)
            UART_Write(buffer[i]);
        //Send the return caracter
        UART_Write('\n');
        
        __delay_ms(500);
    }
    
}
```
## Contact
If you have questions about this project, please contact me at: info@swisstilab.com
