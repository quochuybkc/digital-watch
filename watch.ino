#include <Wire.h> 
#include <Ticker.h>
#include "watch.h"


Ticker ticker_clock, ticker_button1, ticker_button2, ticker_sw;
enum {state1, state2, state3, state4, state5} estate;
unsigned char mode = 0;

// setup
void setup(){
  // set uart baud rate
  Serial.begin(115200);
  
  // set button is input
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  
  // initialize the LCD
  lcd.begin(); 

  // Turn on the backlight 
  lcd.backlight();
  
  // timer call interrupt every 1/100s = 10ms
  ticker_clock.attach_ms(10, secondCount);
  // 100ms = 0.1s
  ticker_button1.attach_ms(10, readButton1);
  // 10ms
  ticker_button2.attach_ms(10, readButton2);
  // 10ms
  ticker_sw.attach_ms(10, sw);
  // initialize first state
  estate = state1;
}

// super loop
void loop(){
  if(mode == 0) mode0();
  else if (mode == 1) mode1();
  else if (mode == 2) mode2();
  else if (mode == 3) mode3();
  else if (mode == 4) mode4();
  switch (estate){
    case state1:
      if(fbutton1){
        mode = (mode + 1)%5;
        estate = state2;
      }
    case state2:
      if(!fbutton1){
        estate = state1;
      }
    break;
  }

}
