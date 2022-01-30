

/****************LCD DIRECTIVES***************/
#define LCD_CLEAR		0x01
#define CURSOR_OFF 	0x0C
#define FIRST_ROW		0x80
#define SECOND_ROW	0xC0
#define Enable_Pulse()	IOSET0|=1<<EN;Delay_ms(1);IOCLR0=1<<EN;Delay_ms(1);
/*Pin Configuration for LCD*/
#define		RS				2
#define		RW				3
#define		EN				4
/*********************************************/

/**************Function Prototypes************/
extern void Lcd_Init(void);
extern void Lcd_Cmd(unsigned char value);
extern void Lcd_Write(unsigned char value);
extern void Lcd_Write_Text(unsigned char msg[]);
extern void Lcd_Data_Shift(unsigned char value);
/*********************************************/
