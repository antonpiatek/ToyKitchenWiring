#include "LightController.h"
#include "config.h"
// edit above config.h, set DEBUG #define for debug output on serial

const int ledPins[3] = {12,10,11};
const int buttonPins[3] = {2,3,4};

LightController l0 = LightController(ledPins[0], buttonPins[0],"0");
LightController l1 = LightController(ledPins[1], buttonPins[1],"1");
LightController l2 = LightController(ledPins[2], buttonPins[2],"2");

void setup() {
  l0.setTimeout(15);
  l1.setTimeout(15);
  l2.setTimeout(120);
  #ifdef DEBUG
  Serial.begin(9600); 
  Serial.println("Run :)");
  #endif
}


void loop() {
  l0.checkButton();
  l1.checkButton();
  l2.checkButton();
}

