/*
 * This project is made for Bang & Olufsen IR eye (I2C based).
 * When a button is pressed an MQTT message is sent to the MQTT broker. 
 * The subscribers pickup the message and act according to the button pressed.
 * 
 * The code can distinguish between short and long pressed for every button.
 * When buttons PLAY and TIMER are pressed, the LED on the button is enabled.
 */

#include <Arduino.h>
#include "PCF8574.h"
#include "BeoButton.h"
#include "Beomote.h"


// B&O IR Eye I2C pin mapping
#define TIMER_BUTTON_PIN 0
#define UP_BUTTON_PIN    1
#define DOWN_BUTTON_PIN  2
#define PLAY_BUTTON_PIN  3
#define PLAY_LED_PIN     6
#define TIMER_LED_PIN    7
#define DEVICE_ADDRESS   0x20
#define MAX_MSG_LEN 128

// Set i2c address
PCF8574 pcf(DEVICE_ADDRESS);


BeoButton btnTimer(TIMER_LED_PIN, "TIMER");
BeoButton btnUp("UP");
BeoButton btnDown("DOWN");
BeoButton btnPlay(PLAY_LED_PIN, "PLAY");

int irPin = 5;
String data = "";
String led = "";
String state = "";
boolean led1 = HIGH;
boolean led2 = HIGH;
  

void setup()
{
  Serial.begin(9600);
  Beo.initialize(irPin);
  pcf.pinMode(TIMER_BUTTON_PIN, INPUT_PULLUP);
  pcf.pinMode(UP_BUTTON_PIN,    INPUT_PULLUP);
  pcf.pinMode(DOWN_BUTTON_PIN,  INPUT_PULLUP);
  pcf.pinMode(PLAY_BUTTON_PIN,  INPUT_PULLUP);

  pcf.pinMode(TIMER_LED_PIN, OUTPUT);
  pcf.pinMode(PLAY_LED_PIN, OUTPUT);

  pcf.begin();
  
 
  Serial.println("I'm alive");
}

void loop() {
  BeoCommand cmd;
  // read all button states
  uint8_t timerVal = pcf.digitalRead(TIMER_BUTTON_PIN);
  uint8_t upVal    = pcf.digitalRead(UP_BUTTON_PIN);
  uint8_t downVal  = pcf.digitalRead(DOWN_BUTTON_PIN);
  uint8_t playVal  = pcf.digitalRead(PLAY_BUTTON_PIN);
  btnTimer.update(timerVal); // change to (pcf, timerVal) if you want to turn the led on or off with long press
  btnUp.update(upVal);
  btnDown.update(downVal);
  btnPlay.update(playVal); // change to (pcf, playVal)
  
  //buttons in the ir eye
  if (timerVal != 1 && timerVal != 0) {
    delay(500);
    Serial.println(timerVal); 
  }
  if (upVal != 1 && upVal != 0) {
   delay(500);
   Serial.println(upVal);
  }
   if (downVal != 1 && downVal != 0) {
    delay(500);
    Serial.println(downVal);
  }
   if (playVal != 1 && playVal != 0) {
    delay(500);
    Serial.println(playVal);
  }
  if (Beo.receive(cmd)) {  
    //Serial.println(cmd.address, HEX);
    //Serial.println(cmd.command);
    Serial.println(cmd.command, HEX);
    //Serial.println(cmd.com); //if you want a more readable command
    
  }
  if (Serial.available() > 0) {
    data = Serial.readStringUntil('\n');
    if (data == "isled") { detectChange(led1, led2);  } else {
    ledUpdate(data); //write isled in serial to find state of the leds 
    }
  }
  
  delay(50);
}
void ledUpdate(String led) {
 
 if ( led == "timer") {
      led1 = !led1;
      BeoButton::updateLed(pcf, TIMER_LED_PIN, led1);
    } 
  
 if ( led == "play") {
      led2 = !led2;
      BeoButton::updateLed(pcf, PLAY_LED_PIN, led2);
    }  
    
}
void detectChange(boolean l1, boolean l2){
 if (l1==LOW) { Serial.println("timer 1");} else { Serial.println("timer 0"); } //for some reason the low and high are backwards
 if (l2==LOW) { Serial.println("play 1");} else { Serial.println("play 0"); }
}
