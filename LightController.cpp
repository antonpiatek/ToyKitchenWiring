#include "Arduino.h"
#include "LightController.h"
#include "config.h"

LightController::LightController(int lightPin, int buttonPin, String id){
  this->lightPin = lightPin;
  this->buttonPin = buttonPin;
  this->id = id;
  this->lightState = LOW;
  this->readCount = 0;
  this->pressed = false;
  this->offDelay = 30000;
  pinMode(this->lightPin, OUTPUT);
  pinMode(this->buttonPin, INPUT);
};

void LightController::setLed() {
  digitalWrite(this->lightPin, this->lightState);
};

void LightController::turnOn(){
  this->lightState = HIGH;
  this->setLed();
};

void LightController::turnOff(){
  this->lightState = LOW;
  this->setLed();
};

void LightController::toggleLight(){
  this->lightState = ! this->lightState;
  this->setLed();
};

void LightController::checkButton(){
  // auto Off
  if(this->lightState == HIGH && this->readCount == 0 && !this->pressed ){
    unsigned long offTime = this->onTime + this->offDelay;
    unsigned long now = millis();
    if( offTime < now ){
      this->debug("AUTOOFF", "state: "+String(this->lightState)+" OnTime: "
            +String(this->onTime)+" OffTime: "+String(offTime)+" now:"+String(now));
      this->lightState = LOW;
      digitalWrite(this->lightPin, this->lightState );
    }
  }

  //check for button presses
  int reading = digitalRead(this->buttonPin);
  //debounce
  if ( reading == HIGH ){
    if(this->readCount < 100){
      this->readCount++;
    }
  }else if(this->readCount > 0){
    this->readCount--;
  }else if (this->readCount == 0){
    this->pressed = false;
  }
  //turn on if sufficiently debounced
  if(!this->pressed && this->readCount >= 50 ){
    unsigned long now = millis();
    this->debug("PRESS","state:"+String(this->lightState)+" pressed:"+String(this->pressed)+" count:"+String(this->readCount)+" now:"+String(now)+" offIn: "+String(this->offDelay)+"ms");
    this->pressed=true;
    toggleLight();
    if(this->lightState == HIGH) {
      this->onTime = now;
    }
  }
};

void LightController::setTimeout(int seconds){
  this->offDelay=(unsigned long)seconds *1000;
}

void LightController::debug(String action, String s){
#ifdef DEBUG
//TODO: debug ifdef?
//TODO: This is probably horrendously inefficient, use a fixed size char[] instead? Or as its debug, perhaps rely on ifdefing it out for production?
  while(action.length() < 10){
    action += " ";
  }
  Serial.println(action+"("+id+"): "+s);
#endif
};
