#include<lpc214x.h>
#define bit(x) (1<<x)
#define delay for(i=0;i<=60000;i++)
#define delay2 for(j=0;j<=12000;j++)
#include "LCD.h"
#include "Delays.h"
//motor
#define SWITCH1 16
#define SWITCH2 17
#define SWITCH3 18
#define SWITCH4 19
unsigned int i;
unsigned int j;
unsigned char flag = 1;
void motor(void){
IO0DIR=0xf;                     //Declaring as a output
    IO0PIN=0;                           //Clear all IO Pins in P0
    VPBDIV=0x01;                    //PCLK = 60MHz
    while(1) {
        /*Forward*/
        IO0SET=bit(0);          //IN1 = 1
        IO0CLR=bit(1);          //IN2 = 0
        delay;delay;
        /*Off*/
        IO0CLR=bit(0)|bit(1); //IN1 = IN2 = 0
        delay;delay;
        /*Reverse*/
        IO0SET=bit(1);          //IN2 = 1
        IO0CLR=bit(0);          //IN0 = 1
        delay;delay;
        /*Off*/
        IO0CLR=bit(0)|bit(1); //IN1 = IN2 = 0
        delay;delay;
    }
}
//rtc
void RTC_Init(void)
{

	PREINT = 0x726;			//To Generate clock of 32.768KHz for RTC Module
	PREFRAC = 0x700;		//when PCLK = 30MHz
	CIIR = 0x01;				//Enables Second Counter Interrupt
	CCR = 0x01;					//Start RTC
}
//rtc
__irq void RTC_ISR(void)
{
	int flag = 1;
	ILR = 0x01;					//Clear the RTC Interrupt Flag
	VICVectAddr = 0x00;
}

int main()
{  unsigned char TIME[] = "TIME:";
	unsigned char DATE[] = "SETTIME:";
	int HOUR1 = 0;
	int MIN1 = 0;
	int SEC1 = 0;
    unsigned int  switchStatus;
	unsigned int  switchStatus1;
	unsigned int  switchStatus2;
	unsigned int  switchStatus3 = 1;
	HOUR = 0;					//Hour
	MIN = 0;						//Min
	SEC = 0;						//Sec
    PINSEL2 = 0x000000; //Configure the PORT1 Pins as GPIO;
    PINSEL1 = 0x000000;
	PINSEL0 = 0x000000;
    IO1DIR = 0x000000;
	 
	Lcd_Init();	
	Lcd_Cmd(LCD_CLEAR);
	Lcd_Write_Text(TIME);
	Lcd_Cmd(SECOND_ROW);
	Lcd_Write_Text(DATE);
	Lcd_Cmd(FIRST_ROW+8);
	Lcd_Write(HOUR/10 + 0x30);
	Lcd_Write(HOUR%10 + 0x30);
	Lcd_Write(':');
	Lcd_Write(MIN/10 + 0x30);
	Lcd_Write(MIN%10 + 0x30);
	Lcd_Write(':');
	Lcd_Write(SEC/10 + 0x30);
	Lcd_Write(SEC%10 + 0x30);
	Lcd_Cmd(SECOND_ROW+8);
	Lcd_Write(HOUR1/10 + 0x30);
    Lcd_Write(HOUR1%10 + 0x30);
	Lcd_Write(':');
	Lcd_Write(MIN1/10 + 0x30);
    Lcd_Write(MIN1%10 + 0x30);
	Lcd_Write(':');
	Lcd_Write(SEC1/10 + 0x30);
    Lcd_Write(SEC1%10 + 0x30); 
	  while(switchStatus3)
    {

     /* Turn On all the leds and wait for one second */ 
       switchStatus = (IO1PIN>>SWITCH1) & 0x01 ;  // Read the switch status
       delay2;
       if(switchStatus == 0)                 //Turn ON/OFF LEDs depending on switch status
       {  
         HOUR1 = (HOUR1 + 1 )%24;
        
       }
	   /* Turn On all the leds and wait for one second */ 
       switchStatus1 = (IO1PIN>>SWITCH2) & 0x01 ;  // Read the switch status
       delay2;
       if(switchStatus1 == 0)                 //Turn ON/OFF LEDs depending on switch status
       {  
         MIN1 = (MIN1 + 1 )%60;

       }
	   /* Turn On all the leds and wait for one second */ 
       switchStatus2 = (IO1PIN>>SWITCH3) & 0x01 ;  // Read the switch status
       delay2;
       if(switchStatus2 == 0)                 //Turn ON/OFF LEDs depending on switch status
       {  
           SEC1 = (SEC1 + 1 )%60;
           
       }

       Lcd_Cmd(SECOND_ROW+8);
	   Lcd_Write(HOUR1/10 + 0x30);
       Lcd_Write(HOUR1%10 + 0x30);
	   Lcd_Write(':');
	   Lcd_Write(MIN1/10 + 0x30);
       Lcd_Write(MIN1%10 + 0x30);
	   Lcd_Write(':');
	   Lcd_Write(SEC1/10 + 0x30);
       Lcd_Write(SEC1%10 + 0x30);  
	   switchStatus3 =  (IO1PIN>>SWITCH4) & 0x01 ; 
	   delay2;   
    }
	  	RTC_Init();
	VICVectAddr13 = (unsigned)RTC_ISR;	//Vector Address of RTC Interrupt
	VICVectCntl13 = 0x20 | 0x0D;				//Enable the Vector IRQ Slot for RTC Interrupt
	VICIntEnable = (1UL<<13);						//Enable the RTC Interrupt      
	//LCD 
	while(!((HOUR1<=HOUR)&&(MIN1<=MIN)&&(SEC1 <= SEC)))
	{
			Lcd_Cmd(FIRST_ROW+8);
			Lcd_Write(HOUR/10 + 0x30);
			Lcd_Write(HOUR%10 + 0x30);
			Lcd_Write(':');
			Lcd_Write(MIN/10 + 0x30);
			Lcd_Write(MIN%10 + 0x30);
			Lcd_Write(':');
			Lcd_Write(SEC/10 + 0x30);
			Lcd_Write(SEC%10 + 0x30);
	
		//motor match checking
     
	}
	 motor();
 
}