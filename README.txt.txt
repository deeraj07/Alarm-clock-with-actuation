Real time alarm clock with actuation using lpc2148 microcontroller manafactured by NXP
LCD.h and Delays.h are header files that needs to be added into your
project destination or the path has to be added
if you are utilising these headers in a different project

In this project 4 push button switches are being connected
to lpc2148 one for controlling hours controlling here means
that on each press the value of hours gets incremented
and another button for minutes and another for seconds 
and a set button is provided to latch the time to RTC(Real time clock)respectively

lpc2148 is being interefaced with 16x2 LCD module 
for lcd.h to work lcd.c source file should also be added to the target
created in keil IDE  same goes for delays.h

Now a motor is being interfaced with lpc2148 with L293D driver for an active motor
to control this motor only some digital control signals are being given to the driver.
If you are interested try with PWM which is an efficient way to control a servo motor

Last comes the connections of lpc2148 since the operating voltage of lpc2148 is 3.3V
we use a dc generator to provide voltage of that decimal to lpc2148
Once all these are done comes the main purpose of this project
RTC is a built in real time clock in lpc2148 mirocontroller unlinke all other clocks which
requires batteries to operate this inbuilt clock has its own spare battery to work on.So even
if microcontroller is turned off it keeps on counting.
After latching time to rtc using set button rtc is being switch on so on match between 
RTC's time and settime the motor should run replicating a real time behaviour.