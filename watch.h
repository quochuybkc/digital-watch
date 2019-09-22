#ifndef _WATCH_H
#define _WATCH_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// define IO pin
#define BUTTON1 12
#define BUTTON2 14

// blink every 500ms
#define Blink_interval  500 

extern boolean fbutton1;
extern  LiquidCrystal_I2C lcd;
extern unsigned int swcount_ms, swSecond, swMinute;
// func prototype

// count second & minute & hour
void secondCount();

// display second
void secondDisplay(unsigned int);

// display minute
void minuteDisplay(unsigned int);

// display hour
void hourDisplay(unsigned int);

// normal clock
void normalClock(unsigned int, unsigned int, unsigned int);

// blink text on lcd
void blinktext(unsigned int, int, int);

// stop watch
void sw();

// read button 1
void readButton1();

// read button 2
void readButton2();

// mode 0: run normal clock
void mode0();

// mode 1: modify hour
void mode1();

// mode 2: modify minute
void mode2();

// mode 3: modify second
void mode3();

// mode 4: run stopwatch
void mode4();


#endif
