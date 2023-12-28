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
  leds[j].b = 0;
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






void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds,NUM_LEDS);
}

void loop() {
    
displayText("Down with emacs");
displayText("vim rules!");

}
