#include "BeoButton.h"
#include "PCF8574.h"


BeoButton::BeoButton(int pcfPin, String type) {
  buttonType = type;
  pin = pcfPin;
}

BeoButton::BeoButton(String type) {
  buttonType = type;  
}

void BeoButton::update(PCF8574& pcf, int state) {
  if (state != previousState) {

    if (state == LOW) {
      pressStart = millis();
    }
    else {
      boolean isShortPress = millis() - pressStart < 300;
      boolean isLongPress = !isShortPress && millis() - pressStart > 600;
      
      if (isShortPress) {
        pcf.digitalWrite(pin, LOW);
       
      }
      else if (isLongPress){
        pcf.digitalWrite(pin, HIGH);
        
      }
      Serial.println(buttonType);
    }
  }
  previousState = state;
}

void BeoButton::update( int state) {
  if (state != previousState) {

    if (state == LOW) {
      pressStart = millis();
    }
    else {
      boolean isShortPress = millis() - pressStart < 300;
      boolean isLongPress = !isShortPress && millis() - pressStart > 600;
      
      if (isShortPress) {
        
      }
      else if (isLongPress){
        
      }
      Serial.println(buttonType);
    }
  }
  previousState = state;
}


void BeoButton::updateLed(PCF8574& pcf, int pin, int state) {
  pcf.digitalWrite(pin, state);  
}
