//Fill in the values below with the pins that you chose to use
const int POT_PIN = A0;
const int BUTTON_PIN = 3;
const int HOT_PIN = 9;
const int COLD_PIN = 6;
const int DRY_PIN = 11;
const int LOCK_PIN = 13;

enum State {
  rest,
  econWash,
  deluxeWash,
  supDelWashHot,
  supDelWashMed,
  econDry,
  deluxeSupDelDry,
}; 

State place = rest;

void setup() {
  Serial.begin(9600);
  pinMode(HOT_PIN, OUTPUT);
  pinMode(COLD_PIN, OUTPUT);
  pinMode(DRY_PIN, OUTPUT);
  pinMode(LOCK_PIN, OUTPUT);
  pinMode(POT_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
}

void loop() {
  place = nextState(place);
}

State nextState(State state){
   Serial.print(analogRead(POT_PIN));
  switch (state) {   
    case rest:
    digitalWrite(HOT_PIN, LOW);
    digitalWrite(COLD_PIN, LOW);
    digitalWrite(DRY_PIN, LOW);
    digitalWrite(LOCK_PIN, LOW);
    
   if(digitalRead(BUTTON_PIN)==LOW){
      if(analogRead(POT_PIN)>=5){
        state = econWash;
    
      }
      else if(analogRead(POT_PIN) < 5 && analogRead(POT_PIN) > 2){
        state = deluxeWash;
    
      }
      else if(analogRead(POT_PIN)<=1){
        state = supDelWashHot;
  
      }
      break;
   }
   else{
   state = rest;
   break;
   }
    
    case econWash:
    digitalWrite(COLD_PIN, HIGH);
    digitalWrite(LOCK_PIN, HIGH);
    delay(5000);
    
    if(analogRead(POT_PIN)<=2){
      state = deluxeSupDelDry;
    
    }
    else{
      state = econDry;
    
    }
    break;
    
    case deluxeWash:
    digitalWrite(HOT_PIN, HIGH);
    digitalWrite(LOCK_PIN, HIGH);
    delay(7000);

    if(analogRead(POT_PIN)>2){
      state = econDry;
      
    }
    else{
      state = deluxeSupDelDry;
     
    }
    break;
    
    case supDelWashHot:
    digitalWrite(HOT_PIN, HIGH);
    digitalWrite(LOCK_PIN, HIGH);
    delay(7000);

    if(analogRead(POT_PIN)>=5){
      state = econDry;
  
    }
    else{
      state = supDelWashMed;
 
    }
    break;
   
    
    case supDelWashMed:
    digitalWrite(COLD_PIN, HIGH);
    delay(7000);
    state = deluxeSupDelDry;
    break;
    
    case econDry:
    digitalWrite(HOT_PIN, LOW);
    digitalWrite(COLD_PIN, LOW);
    digitalWrite(DRY_PIN, HIGH);
    delay(2000);
    state = rest; 
    break;
    
    case deluxeSupDelDry:
    digitalWrite(HOT_PIN, LOW);
    digitalWrite(COLD_PIN, LOW);
    digitalWrite(DRY_PIN, HIGH);
    delay(7000);
    state = rest; 
    break;
    
  }
  return state;
}
