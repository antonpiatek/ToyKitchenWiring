const int ledPins[3] = {11,12,13};
int ledStates[3]     = {LOW,LOW,LOW};
const int buttonPins[3] = {2,3,4};

int pressed[3]={0};
int readCount[3] = {0,0,0};
unsigned long onTime[3] = {0};

void setup() {
  // Setup the buttons with an internal pull-up and debouncer
  for (int i = 0; i < sizeof(buttonPins); i++){
    pinMode(buttonPins[i],INPUT);
  }

  // Set leds
  for (int i = 0; i < sizeof(ledPins); i++){
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], ledStates[i]);
  }
  Serial.begin(9600); 
}

#define AUTO_OFF_TIME 30

void loop() {
  for (int i = 0; i < 3; i++){
    //auto turn off
    if(ledStates[i] == HIGH && readCount[i] ==0 && pressed[i] == 0){
      unsigned long offTime = onTime[i] + ((unsigned long)AUTO_OFF_TIME * 1000);
      unsigned long now = millis();
      if( offTime < now ){
        Serial.println("AUTOOFF: "+String(i)+" "+String(ledStates[i])+" OnTime: "+String(onTime[i])+" OffTime: "+String(offTime)+" now:"+String(now));
        ledStates[i] = LOW;
        digitalWrite(ledPins[i], ledStates[i] );
      }
    } 

    //check for button presses
    int reading = digitalRead(buttonPins[i]);
    //debounce
    if ( reading == HIGH ){
      if(readCount[i] < 100){
        readCount[i]++;
      }
    }else if(readCount[i] > 0){
      readCount[i]--;
    }else if (readCount[i] == 0){
      pressed[i]=0;
    }
    //turn on if sufficiently debounced
    if(pressed[i] == 0 && readCount[i] >= 50 ){
      unsigned long now = millis();
      Serial.println("ON: butt:"+String(i)+" state:"+String(ledStates[i])+" pressed:"+String(pressed[i])+" count:"+String(readCount[i])+" now:"+String(now));
      pressed[i]=1;
      ledStates[i] = !ledStates[i];
      digitalWrite(ledPins[i], ledStates[i] );
      if(ledStates[i] == HIGH) {
        onTime[i] = now;
      }
      //Serial.println(readCount[i]);
    }
  }
}
