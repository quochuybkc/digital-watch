#include <Wire.h> 
#include <Ticker.h>
#include "watch.h"


Ticker ticker_clock, ticker_button1, ticker_button2, ticker_sw;
enum {state1, state2, state3, state4, state5} estate;

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
  ticker_button1.attach_ms(100, readButton1);
  // 10ms
  ticker_button2.attach_ms(10, readButton2);
  // 10ms
  ticker_sw.attach_ms(10, sw);
  // initialize first state
  estate = state1;
}

// super loop
void loop(){
  switch(estate){
    case state1:
    {
      mode0();
      if(fbutton1){
        fbutton1 = false;
        estate = state2;
      }
      break;
    }
    case state2:
    {
      mode1();
      if(fbutton1){
        fbutton1 = false;
        estate = state3;
      }
      break;
    }
    case state3:
    {
      mode2();
      if(fbutton1){
        fbutton1 = false;
        estate = state4;
      }
      break;
    }
    case state4:
    {
      mode3();
      if(fbutton1){
        fbutton1 = false;
        estate = state5;
      }
      break;
    }
    case state5:
    {
      mode4();
      if(fbutton1){
        fbutton1 = false;
        swcount_ms = swSecond = swMinute = 0;
        estate = state1;
      }      
      break;
    }
  }
}
