/*
   MIT License

  Copyright (c) 2021 Felix Biego

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include <ESP32Time.h>
#include "numbersBinaryWLabels.h"
#include <FastLED.h>
#define WIDTH 36
#define HEIGHT 16
#define LED_PIN 2
int location;
int level;
int letter;

const int NUM_LEDS = WIDTH * HEIGHT;
CRGB leds[NUM_LEDS];





void ledSet(int j, int level){
  leds[j].r = level;
  leds[j].g = level;
  leds[j].b = level;
}



void displayText(String message){
  if(message.length() < 5)
  for(int i = 0; i < (message.length() - 5); i++){
    message = message + " ";
  }

  int arraySize = message.length() * 7;
  int toDisplay[arraySize][12];
  
  for(int y = 0; y < 12; y++){                        //creates array to be displayed
    for(int x = 0; x < arraySize; x++){
      toDisplay[x][y] = num[int(message[(x/7)])-32][(x%7)+(y*7)];
    } 
  }

  

  if(message.length() <= 5){                          //If no scrolling is nessesary, displays text
    for(int y = 0; y < 12; y++){
      for(int x = 0; x < (arraySize); x++){
        ledSet(((y+2)*WIDTH)+x, 255 * toDisplay[x][y]);   
     }}
     FastLED.show();
  }

  else{                                               //If scrolling is nessesary, displays text
    for(int scroll = 0; scroll < (arraySize-WIDTH); scroll++){
    for(int y = 0; y < 12; y++){
      for(int x = 0; x < WIDTH; x++){
        ledSet(((y+2)*WIDTH)+x, 255 * toDisplay[x + scroll][y]);
     }}
     FastLED.show();
     delay(250);
    }
    delay(1250);
    }

}

















//ESP32Time rtc;

ESP32Time rtc(3600);  // offset in seconds GMT+1

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds,NUM_LEDS);
  Serial.begin(115200);
  pinMode(25, INPUT);
  pinMode(33, INPUT);
  pinMode(32, INPUT);
  String test;
  int hour = 0;
  int minutes = 0;

  while(digitalRead(32)==LOW){
    if(digitalRead(33)==HIGH){
      hour++;
      delay(250);
    }
    if(digitalRead(25)==HIGH){
      minutes++;
      delay(250);
    }
   test = String((hour%12)+1) + ":" + String(minutes % 60);
   displayText(test);

    
  }
  

  rtc.setTime(0, (minutes%60), (hour%12), 17, 1, 2021);  // 17th Jan 2021 15:24:30
  //rtc.setTime(1609459200);  // 1st Jan 2021 00:00:00
  //rtc.offset = 7200; // change offset value


}

void loop() {
  char test[6];
  sprintf(test, "%02d:%02d",rtc.getHour(), rtc.getMinute());


  
  //test = String(rtc.getHour()) + ":" + String(rtc.getMinute());
  displayText(String(test));
  //Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));   // (String) returns time with specified format 
  // formating options  http://www.cplusplus.com/reference/ctime/strftime/


  struct tm timeinfo = rtc.getTimeStruct();
  //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");   //  (tm struct) Sunday, January 17 2021 07:24:38
  
  delay(1000);
}
