#include "watch.h"

//global vars
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display
unsigned int count_ms = 0; 
unsigned int countSecond = 0;
unsigned int countMinute = 0;
unsigned int countHour = 0;
unsigned int count02s = 0, count1s = 0;
unsigned int swcount_ms = 0, swSecond = 0, swMinute = 0;
enum {state1, state2, state3, state4, state5} estate;
enum {hourstate1, hourstate2} hourstate;
enum {minutestate1, minutestate2} minutestate;
enum {secondstate1, secondstate2} secondstate;
boolean fbutton1 = false, fbutton2 = false, fbutton2pressed1s = false;
boolean fRead1 = true, sRead1 = true, fRead2 = true, sRead2 = true;
int swstate = 0;
boolean flag = false; // on/off stop watch
unsigned long previousMillis = 0;
boolean BlankOnOff = false; 
typedef enum {BUTTON_2_PRESSED, BUTTON_2_RELEASED} Button_2_State;
Button_2_State button2State = BUTTON_2_PRESSED;
//////////////////////////////


/// function definition
void blinktext(unsigned int text, int col, int row){
 unsigned long currentMillis = millis();
  lcd.setCursor(col, row);
  if(currentMillis - previousMillis > Blink_interval){
    previousMillis = currentMillis;
    if(BlankOnOff){
      for(int i = 1; i < 3; i++) {
        lcd.print(" ");
      } 
    }else {
      if(text < 10){
        lcd.print(0);
        lcd.print(text);
      }else{
        lcd.print(text);
      }
    }
    BlankOnOff = !BlankOnOff;
  }
}

void secondCount(){
  count_ms++;
  if(count_ms == 100){
    countSecond++;
    if(countSecond == 60){
      countSecond = 0;
      countMinute++;
      if(countMinute == 60){
        countMinute = 0;
        countHour++;
        if(countHour == 24){
          countHour == 0; 
        }
      }
    }
    count_ms = 0;
  }
}


void readButton1(){
  fRead1 = sRead1;
  sRead1 = digitalRead(BUTTON1);
  if(sRead1 == fRead1){
    if(!fRead1){
      fbutton1 = true;
    }else{
      fbutton1 = false;
    }
  }
}


void readButton2(){
  fRead2 = sRead2;
  sRead2 = digitalRead(BUTTON2);
  if(sRead2 == fRead2){
    if(!fRead2){
      fbutton2 = true;
      count1s++;
      if(count1s >= 100){
        fbutton2pressed1s = true;
        count02s++;
        if(count02s > 20){
          count02s = 0;
        }
      }
    }else{
      fbutton2 = false;
      fbutton2pressed1s = false;
      count1s = 0;
      count02s = 0;
    }
  }
}


void secondDisplay(unsigned int second){
  lcd.setCursor(6,0);
  if(second < 10){
    lcd.print(0);
    lcd.print(second);
  }
  else{
    lcd.print(second);    
  }
}

// display minute on lcd
void minuteDisplay(unsigned int minute){
  lcd.setCursor(3,0);
  if(minute < 10){
    lcd.print(0);
    lcd.print(minute);
  }
  else{
    lcd.print(minute);    
  }
}


void hourDisplay(unsigned int hour){
  lcd.setCursor(0,0);
  if(hour < 10){
    lcd.print(0);
    lcd.print(hour);
  }
  else{
    lcd.print(hour);    
  } 
}


void normalClock(unsigned int p1, unsigned int p2, unsigned int p3){
  hourDisplay(p3);
  lcd.setCursor(2,0);
  lcd.print(":");
  minuteDisplay(p2);
  lcd.setCursor(5,0);
  lcd.print(":");
  secondDisplay(p1);
}


void mode0(){
  normalClock(countSecond, countMinute, countHour);
}


void mode1(){
  blinktext(countHour, 0, 0);
  minuteDisplay(countMinute);
  secondDisplay(countSecond);
  switch(hourstate){
    case hourstate1:
      if(fbutton2){
        countHour++;
        if(countHour == 24){
          countHour = 0;
        }
        hourstate = hourstate2;
      } 
      break;
    case hourstate2:
      if(!fbutton2){
        hourstate = hourstate1;
      }else if(fbutton2pressed1s){
        if(count02s == 20){
          countHour++;
          if(countHour == 24){
            countHour = 0;      
          }
        }
      }
      break;
  }
}


void mode2(){
  blinktext(countMinute, 3, 0);
  hourDisplay(countHour);
  secondDisplay(countSecond);
  switch(minutestate){
    case minutestate1:
      if(fbutton2){
        countMinute++;
        if(countMinute == 60){
          countMinute = 0;
        }
        minutestate = minutestate2;
      } 
      break;
    case hourstate2:
      if(!fbutton2){
        minutestate = minutestate1;
      }else if(fbutton2pressed1s){
        if(count02s == 20){
          countMinute++;
          if(countMinute == 60){
            countMinute = 0;      
          }
        }
      }
      break;
  }
}


void mode3(){
  blinktext(countSecond, 6, 0);
  hourDisplay(countHour);
  minuteDisplay(countMinute);
  switch(secondstate){
    case secondstate1:
      if(fbutton2){
        countSecond++;
        if(countSecond == 60){
          countSecond = 0;
        }
        secondstate = secondstate2;
      } 
      break;
    case hourstate2:
      if(!fbutton2){
        secondstate = secondstate1;
      }else if(fbutton2pressed1s){
        if(count02s == 20){
          countSecond++;
          if(countSecond == 60){
            countSecond = 0;      
          }
        }
      }
      break;
  }
}


void sw(){
  if(flag){
    swcount_ms++;
    if(swcount_ms == 100){
      swSecond++;
      swcount_ms = 0;
    }else if(swSecond == 60){
      swMinute++;
      swSecond = 0;
    }else if(swMinute == 60){
      swMinute = 0;
    }
  }
}


void mode4(){

  switch(button2State){
    case BUTTON_2_PRESSED:
      if(fbutton2){
        button2State = BUTTON_2_RELEASED;
        if(flag == true) flag = false;
        else flag = true;  
      }
    break;
    case BUTTON_2_RELEASED:
      if(!fbutton2)
        button2State = BUTTON_2_PRESSED;
    break;
    default:
        button2State = BUTTON_2_PRESSED;
    break;
  }
  normalClock(swcount_ms, swSecond, swMinute);

}
////////////////////
