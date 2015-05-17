#include "LightController.h"
#include "config.h"
// edit above config.h, set DEBUG #define for debug output on serial

const int ledPins[3] = {11,12,13};
const int buttonPins[3] = {2,3,4};

LightController l1 = LightController(ledPins[2], buttonPins[0],"1");
LightController l2 = LightController(ledPins[1], buttonPins[1],"2");
LightController l3 = LightController(ledPins[0], buttonPins[2],"3");

void setup() {
  l1.setTimeout(3);
  l2.setTimeout(3);
  l3.setTimeout(120);
  #ifdef DEBUG
  Serial.begin(9600); 
  Serial.println("Run :)");
  #endif
}


void loop() {
  l1.checkButton();
  l2.checkButton();
  l3.checkButton();
}

