/*
 * File:   MPPT.c
 * Author: Silviu
 *
 * Created on March 12, 2019, 12:45 PM
 */


#include <xc.h>
#include <pic18f46k22.h>
#include "bit_config.h"
#include "config.h"
#include <stdio.h>
#define  buck  CCPR2L
#define  boost CCPR1L
int buck_pwm,boost_pwm;

char str_V[8],str_A[8],str_P[8];
int dty,c;
float rez_adc_A,tens_A,Iout,rez_adc_U,tens,Uout,Uin,Power_a;

void read_Iout(void)//citire curent de iesire
{
    ADCON0=0b00001011;//RA2
    __delay_ms(10);
    ADCON0bits.GO=1;
    __delay_ms(100);
    rez_adc_A=ADRESH;
    tens_A=rez_adc_A*0.0181372549019608;
    Iout=tens_A;
    if(Iout>2)
    {
        __delay_ms(10);
        CCPR1L=0;
        CCPR2L=0;
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Over Current");
        while(1)
        {
            __delay_ms(100);
        }
    
    }
    
}

void write_Iout(void)//scriere pe display valoarea curentului de iesire
{
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("I=");
    sprintf(str_A, "%.2f", Iout);
    Lcd_Set_Cursor(2,3);
    Lcd_Write_String(str_A);
    Lcd_Write_String(" A");
}


void read_Uout(void)//citire valoare tensinue de iesire
{
    ADCON0=0b00000111;//RA1
    __delay_ms(10);
    ADCON0bits.GO=1;
    __delay_ms(100);
    rez_adc_U=ADRESH;
    tens=rez_adc_U*0.01953125;
    Uout=tens/0.25;
    if(Uout>14.4)
    {
        __delay_ms(10);
        CCPR1L=0;
        CCPR2L=0;
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Over Voltage");
        while(1)
        {
            __delay_ms(100);
        }
    
    }

}

void write_Uout(void)//scriere pe display valoarea tensinuii de iesire
{
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("U=");
    sprintf(str_V, "%.2f", Uout);
    Lcd_Set_Cursor(1,3);
    Lcd_Write_String(str_V);
}

void read_Uin(void)//citire valoare tensinue de intrare
{
    ADCON0=0b00001111;//RA3
    __delay_ms(10);
    ADCON0bits.GO=1;
    __delay_ms(100);
    rez_adc_U=ADRESH;
    tens=rez_adc_U*0.01953125;
    Uin=tens/0.2;
   
}

void write_Uin(void)//scriere pe display valoarea tensinuii de intrare
{
    Lcd_Set_Cursor(1,9);
    Lcd_Write_String("Ui=");
    sprintf(str_V, "%.2f", Uin);
    Lcd_Set_Cursor(1,12);
    Lcd_Write_String(str_V);
    Lcd_Write_String(" V");
}
void write_Power(void)
{
    Power_a=Uout*Iout;
    Lcd_Set_Cursor(2,10);
    sprintf(str_P, "%.2f", Power_a);
    Lcd_Write_String(str_P);
    Lcd_Write_String(" W");
    
}

void pwm_init(float Uin)
{
    if(Uin>12)
    {
        boost_pwm=0;
        buck=boost_pwm;

    }
    else
    {

    }
}

void set_boost(int dty)
{
	if(dty>100)
    {
        dty=100;
    }
    if(dty<0)
    {
        dty=0;
    }
	c=dty*1.61; 
	CCPR1L=c;
    
	
}
void set_buck(int dty)
{
	if(dty>100)
    {
        dty=100;
    }
    if(dty<0)
    {
        dty=0;
    }
    
	c=dty*1.61; 
	CCPR2L=c;
}