/*
 * File:   config.c
 * Author: Silviu
 *
 * Created on March 14, 2019, 3:04 PM
 */

#include <xc.h>
#include "config.h"
#include <pic18f46k22.h>
#include "bit_config.h"
#include "lcd_i2c.h"

void config(void)//configuari initale ale proturilor
{
    TRISA=0Xff;
    TRISB=0X00;
    TRISC=0X00;
    TRISD=0X00;
    TRISE=0Xff;
    
    PORTA=0X00;
    PORTB=0X00;
    PORTC=0X00;
    PORTD=0X00;
    PORTE=0X00;
     
    LATA=0X00;
    LATB=0X00;
    LATC=0X00;
    LATD=0X00;
    LATE=0X00;
    
    ANSELA=0Xff;
    ANSELB=0X00;
    ANSELC=0X00;
    ANSELD=0X00;
    ANSELE=0X00;
    
    OSCCON=0b01110100;
    OSCTUNEbits.PLLEN=1;
}

void pwm_config(void)//activare si configurare al semnalului cu modulatie
{
    CCPTMRS0=0b00000000;
    CCP2CON=0b00001100; //RC2
    CCP1CON=0b00001100; //RC1
    T2CON=0b01111101;
    PR2=160;

}

void adc_config(void)//setari initiale ale ADC-ului
{
    ADCON1=0b10000000;
    ADCON2=0b00111110;
    ADCON2bits.ADFM=0;

}

void init_io_display()//initializari display I2C
{
    TRISCbits.TRISC3=1;//i2c
    TRISCbits.TRISC4=1;//i2c
    I2C_Master_Init(100000);
    __delay_ms(100);
    Lcd_Init();
    Lcd_Clear();
    Cursor_Off();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Test");
    __delay_ms(100);
}

void eusart_config(void)
{
    TRISCbits.RC6=1;
    USARTInit(19200);//19200
    TRISCbits.RC7=1;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    PIE1bits.RC1IE=1;
    
}