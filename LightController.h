#ifndef LightController_h
#define LightController_h

#include "Arduino.h"

class LightController {
  private:
    int lightState,lightPin, buttonPin, readCount;
    void setLed();
    boolean pressed;
    unsigned long offDelay, onTime;
    String id;
    void debug(String action, String s);
  public:
    LightController(int lightPin, int buttonPin, String id);
    void turnOn();
    void turnOff();
    void toggleLight();
    void checkButton();
    void setTimeout(int seconds);
};
#endif
