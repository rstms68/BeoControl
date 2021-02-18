#define RADIO 2
#define TAPE 3
#define AUX 4
#define OFF 5

void setup() {
  // put your setup code here, to run once:
pinMode(RADIO, OUTPUT);
pinMode(TAPE, OUTPUT);
pinMode(AUX, OUTPUT);
pinMode(OFF, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    if ( data == "radio") {
        digitalWrite(RADIO, HIGH);
        delay(200);
        digitalWrite(RADIO, LOW);
    } 
    if (data == "tape") {
      digitalWrite(TAPE, HIGH);
      delay(200);
      digitalWrite(TAPE, LOW);
    }
    if (data == "aux") {
      digitalWrite(AUX, HIGH);
      delay(500);
      digitalWrite(AUX, LOW);
    }
    if (data == "off") {
      digitalWrite(OFF, HIGH);
      delay(500);
      digitalWrite(OFF, LOW);
    }
  }
  delay(50);
}
