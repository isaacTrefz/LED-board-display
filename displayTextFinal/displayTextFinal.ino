#include "numbersBinaryWLabels.h"
#include <FastLED.h>
#define WIDTH 36
#define HEIGHT 32
#define LED_PIN 2
int location;
int level;
int letter;

const int NUM_LEDS = WIDTH * HEIGHT;
CRGB leds[NUM_LEDS];

#include <ThreeWire.h>  
#include <RtcDS1302.h>

ThreeWire myWire(13,14,16); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);



// Adafruit_DHT library is inserted
#include "DHT.h"
 
// Here the respective input pin can be declared
#define DHTPIN 23    
 
// The sensor is initialized
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);
 








void ledSet(int j, int level){
  leds[j].r = level * digitalRead(18);
  leds[j].g = level * digitalRead(18);
  leds[j].b = level * digitalRead(18);
}



void displayText(String message){


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
    if(scroll == 0)
      delay(2000);
    }
    delay(1250);
    }
  



}



void displayTextLow(String message){



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
        ledSet((((y+2)*WIDTH)+x) + 576, 255 * toDisplay[x][y]);   
     }}
     for(int b = 0; b<16; b++){//This line is a bad solution, change this
      ledSet(575 + (b*36),0);
     }
     showTime();
     FastLED.show();
  }

  else{                                               //If scrolling is nessesary, displays text
    for(int scroll = 0; scroll < (arraySize-WIDTH); scroll++){
    for(int y = 0; y < 12; y++){
      for(int x = 0; x < WIDTH; x++){
        ledSet((((y+2)*WIDTH)+x) + 576, 255 * toDisplay[x + scroll][y]);
     }}
     if(digitalRead(19)==HIGH || digitalRead(21)==HIGH)
      return;
     showTime();
     FastLED.show();
     delay(1
     
     50);
    if(scroll == 0)
      delay(2000);
    }
    delay(1250);
    }
  



}




void showChar(int input){ //This function is for testing, put in the ascii value of a char and it will display the letter.

   for(int k = 0; k<12; k++){
    for(int i = 0; i<7;i++){
      location = ((k+2)*WIDTH)+i;
      level = 255 * num[input-32][(k*7)+i];
      ledSet(location,level);
   }
  }
    FastLED.show();
    
  
}

void displayTemp(){
   // temperature is measured
  float t = dht.readTemperature();
  String temp = String(t);
displayTextLow(temp.substring(0, 4) + "C");

  
}


void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];


     snprintf_P(datestring, 
            countof(datestring),
            //PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            PSTR("%02u:%02u"),
            //dt.Month(),
            //dt.Day(),
            //dt.Year(),
            dt.Hour(),
            //dt.Minute(),
            //dt.Second() );
            dt.Minute() );
    displayText(datestring);
}



void showTime(){

   RtcDateTime now = Rtc.GetDateTime();
   printDateTime(now);

    if (!now.IsValid())
    {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }
  
}


void setup() {
    pinMode(18, INPUT);
    Serial.begin(115200);
    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();

    if (!Rtc.IsDateTimeValid()) 
    {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }

    if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled) 
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled) 
    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }



  pinMode(19, INPUT);
  pinMode(18, INPUT);
  pinMode(21, INPUT);
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds,NUM_LEDS);

  // Measurement is started
  dht.begin();

}
  int menu = 0;
void loop() {

if(digitalRead(19)==HIGH || digitalRead(21)==HIGH){
  menu = (menu == 0) ? 1 : 0;
  delay(500);}


if(menu == 1)
  displayTemp();
else
  displayTextLow("Give us an A+");


}
