#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

Adafruit_SSD1306 display = Adafruit_SSD1306(128,64,&Wire);

void clear_disp(){
  display.clearDisplay();
}

void init_Display() {

  display.begin(SSD1306_SWITCHCAPVCC,0x3c);

}

void display_Data(int val){

  display.clearDisplay();
  display.setTextColor(WHITE);

 

  display.setTextSize(1);
  display.setCursor(0,16);
  display.print(val);

  display.display();

}

void display_step(int val){

  // display.clearDisplay();
  display.setTextColor(WHITE);

 

  display.setTextSize(1);
  display.setCursor(0,40);
  display.print(val);

  display.display();

}

void display_Data_txt(const char* val){

  display.clearDisplay();
  display.setTextColor(WHITE);

 

  display.setTextSize(1);
  display.setCursor(0,16);
  display.print(val);

  display.display();

}


