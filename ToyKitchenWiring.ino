const int ledPins[3] = {11,12,13};
int ledStates[3]     = {LOW,LOW,LOW};
const int buttonPins[3] = {2,3,4};

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

int pressed[3]={0};

int readCount[] = {0,0,0};
void loop() {
  for (int i = 0; i < 3; i++){
    int reading = digitalRead(buttonPins[i]);
    if ( reading == HIGH ){
      if(readCount[i] < 100){
        readCount[i]++;
      }
    }else if(readCount[i] > 0){
      readCount[i]--;
    }else if (readCount[i] == 0){
      pressed[i]=0;
    }
    if(pressed[i] == 0 && readCount[i] >= 50 ){
      Serial.println(String(i)+" "+String(ledStates[i])+" "+String(pressed[i])+","+String(readCount[i]));
      pressed[i]=1;
      ledStates[i] = !ledStates[i];
      digitalWrite(ledPins[i], ledStates[i] );
      Serial.println(readCount[i]);
    }
  }
}
