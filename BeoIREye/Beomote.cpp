#include "Beomote.h"

Beomote Beo;

void Beomote::initialize(int pin) {
	irPin = pin;

	// Setting the pinmode of the IR pin and resetting the listener
	pinMode(irPin, INPUT);
	reset();

	// Clearing Control Register A
	TCCR1A = 0;

	// Setting the phase and frequency correct pwm, and stopping the timer
	TCCR1B = _BV(WGM13);

	long cycles = (F_CPU / 2000000) * TICK;
	ICR1 = cycles;

	TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));

	// Setting the timer overflow interrupt enable bit
	TIMSK1 = _BV(TOIE1);

	// Resetting clock select register, and starts the clock with no prescale
	TCCR1B |= _BV(CS10);
}

void Beomote::reset() {
	index = -1;
	irReceived = 0;

	link = 0x00;
	address = 0x00;
	command = 0x00;
}

int Beomote::receive(BeoCommand &cmd) {
	if (irReceived) {
		cmd.link = link;
		cmd.address = (beo_address)address;
		cmd.command = (beo_command)command;
    cmd.com = decodeC(cmd.command);
		reset();
		return 1;
	}

	return 0;
}

void Beomote::timerISR() {
	if (irReceived)
		return;

	timer++;

	int irData = digitalRead(irPin);

	if (irData == LOW && lastState == HIGH) {
		int beoCode = 0;
		int beoBit = 0;

		if (abs(timer - BEO_ZERO) < 2) {
			beoCode = BEO_ZERO;
			beoBit = lastBeoBit = 0;
		}
		else if (abs(timer - BEO_SAME) < 2) {
			beoCode = BEO_SAME;
			beoBit = lastBeoBit;
		}
		else if (abs(timer - BEO_ONE) < 2) {
			beoCode = BEO_ONE;
			beoBit = lastBeoBit = 1;
		}
		else if (abs(timer - BEO_STOP) < 2) {
			beoCode = BEO_STOP;
		}
		else if (abs(timer - BEO_START) < 2) {
			beoCode = BEO_START;
		}
		else
			index = -1;

		if (index == -1) {
			if (beoCode == BEO_START)
				index = 0;
		}
		else if (index == 0) {
			link = beoBit;
			index++;
		}
		else if (index < 9) {
			address = address << 1;
			address |= beoBit;

			index++;
		}
		else if (index < 17) {
			command = command << 1;
			command |= beoBit;

			index++;
		}
		else if (index == 17) {
			if (beoCode == BEO_STOP)
				irReceived = 1;
			else
				index = -1;
		}

		timer = 0;
		lastState = LOW;
	}
	else if (irData == HIGH && lastState == LOW) {
		lastState = HIGH;
	}
}

ISR(TIMER1_OVF_vect) {
	Beo.timerISR();
}

String Beomote::decodeC(int address) {
  const char * comm[] = { "NUMBER_0",
  "NUMBER_1",
  "NUMBER_2",
  "NUMBER_3",
  "NUMBER_4",
  "NUMBER_5",
  "NUMBER_6",
  "NUMBER_7",
  "NUMBER_8",
  "NUMBER_9",
  
  "CLEAR",
  "STORE",
  "STANDBY",
  "MUTE",
  "INDEX",
  
  "UP",
  "DOWN",
  "TUNE",
  
  "CLOCK",
  
  "FORMAT",
  
  "LEFT",
  "RETURN",
  "RIGHT",
  "GO",
  "STOP",
  "RECORD",
  
  "SELECT",
  
  "SPEAKER",
  "PICTURE",
  "TURN",
  
  "LOUDNESS",
  
  "BASS",
  "TREBLE",
  "BALANCE",
  
  "LIST",
  
  "MENU",
  
  "VOLUME_UP",
  "VOLUME_DOWN",
  
  "LEFT_REPEAT",
  "RIGHT_REPEAT",
  "UP_REPEAT",
  "DOWN_REPEAT",
  
  "GO_REPEAT",
  "GREEN_REPEAT",
  "YELLOW_REPEAT",
  "BLUE_REPEAT",
  "RED_REPEAT",
  
  "EXIT",
  "TV",
  "RADIO",
  "VIDEO_AUX",
  "AUDIO_AUX",
  
  "VIDEO_TAPE",
  "DVD",
  "CAMCORD",
  "TEXT",
  "SP_DEMO",
  "DIGITAL_TV",
  "PC",
  
  "DOOR_CAM",
  "AUDIO_TAPE",
  "CD",
  "PHONO",
  "AUDIO_TAPE_2",
  
  "CD2",
  
  "LIGHT",
  
  "AV",
  
  "YELLOW",
  "GREEN",
  "BLUE",
  "RED"};
if (address < 15) {
  return comm[address];
}
if (address > 29 && address < 33) {
  return comm[address - 15];
}
if (address > 29 && address < 33) {
  return comm[address - 15];
}
if (address == 40) {
  return comm[address - 22];
}
if (address == 42) {
  return comm[address - 23];
}
if (address > 49 && address < 56) {
  return comm[address - 30];
}
if (address == 63) {
  return comm[address - 37];
}
if (address > 67 && address < 71) {
  return comm[address - 41];
}
if (address == 72) {
  return comm[address - 42];
}
if (address > 76 && address < 80) {
  return comm[address - 46];
}
if (address == 88) {
  return comm[address - 54];
}
if (address == 92) {
  return comm[address - 57];
}
if (address == 96) {
  return comm[address - 60];
}
if (address == 100) {
  return comm[address - 63];
}
if (address > 112 && address < 122) {
  return comm[address - 75];
}
if (address > 126 && address < 140) {
  return comm[address - 80];
}
if (address == 141) {
  return comm[address - 81];
}
if (address > 144 && address < 149) {
  return comm[address - 84];
}
if (address == 151) {
  return comm[address - 86];
}
if (address == 155) {
  return comm[address - 89];
}
if (address == 191) {
  return comm[address - 124];
}
if (address > 211 && address < 216) {
  return comm[address - 144];
}
}
