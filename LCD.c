
#include <LPC213X.H>
#include "LCD.h"
#include "Delays.h"

/*****************LCD Functions***************/
void Lcd_Init(void)
{
	PINSEL0 = 0x00;
	IODIR0 |= (1<<RS);					//RS Pin as Output Pin
	IODIR0 |= (1<<RW);					//RW Pin as Output Pin
	IODIR0 |= (1<<EN);					//EN Pin as Output Pin
	
	IODIR0 |= 0x0000FF00;				//P0.8 to P0.15 as Data Line of LCD
	
	Lcd_Cmd(0x38);							//Send 8-bit initialization command to lcd
	Delay_ms(10);
	Lcd_Cmd(CURSOR_OFF);				//Cursor OFF
	Delay_ms(10);
	Lcd_Cmd(LCD_CLEAR);
	Delay_ms(1);
	Lcd_Cmd(FIRST_ROW);
}

void Lcd_Data_Shift(unsigned char value)
{
	/*
	This Function will shift the eight bit data stored in variable value,
	to the Port Pin P0.8 to P0.15 Successfully.
	*/
	unsigned char i;
	
	for(i=0;i<8;i++)
	{
		if(value & 0x01)
		{
			IOSET0 |= (1<<(i+8));
		}
		else
		{
			IOCLR0 |= (1<<(i+8));
		}
		value = value >> 1;
	}
}

void Lcd_Cmd(unsigned char value)
{
	/*Configure LCD for receiving Command Data*/
	IOCLR0 |= (1<<RS);
	IOCLR0 |= (1<<RW);
	IOSET0 |= (1<<EN);
	Lcd_Data_Shift(value);
	Enable_Pulse();
}

void Lcd_Write(unsigned char value)
{
	/*Configure LCD for receiving Display Data*/
	IOSET0 |= (1<<RS);
	IOCLR0 |= (1<<RW);
	IOSET0 |= (1<<EN);
	Lcd_Data_Shift(value);
	Enable_Pulse();
}

void Lcd_Write_Text(unsigned char msg[])
{
	while(*msg)
	{
		Lcd_Write(*msg);
		msg++;
	}
}
/*********************************************/
