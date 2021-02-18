#ifndef _COMMANDS_H
#define _COMMANDS_H

typedef enum beo_address
{
  SOURCE_VIDEO = 0x00,
  SOURCE_AUDIO = 0x01,
  SOURCE_VIDEOTAPE = 0x05,
  SOURCE_ALL = 0x0F,
  SOURCE_SPDEMO = 0x1D,
  SOURCE_LIGHT = 0x1B
} beo_address;

typedef enum  beo_command
{
	NUMBER_0 = 0x00,
	NUMBER_1 = 0x01,
	NUMBER_2 = 0x02,
	NUMBER_3 = 0x03,
	NUMBER_4 = 0x04,
	NUMBER_5 = 0x05,
	NUMBER_6 = 0x06,
	NUMBER_7 = 0x07,
	NUMBER_8 = 0x08,
	NUMBER_9 = 0x09,
	
	CLEAR = 0x0A,
	STORE = 0x0B,
	STANDBY = 0x0C,
	MUTE = 0x0D,
	INDEX = 0x0E,
	
	UP = 0x1E,
	DOWN = 0x1F,
	TUNE = 0x20,
	
	CLOCK = 0x28,
	
	FORMAT = 0x2A,
	
	LEFT = 0x32,
	RETURN = 0x33,
	RIGHT = 0x34,
	GO = 0x35,
	STOP = 0x36,
	RECORD = 0x37,
	
	SELECT = 0x3F,
	
	SPEAKER = 0x44,
	PICTURE = 0x45,
	TURN = 0x46,
	
	LOUDNESS = 0x48,
	
	BASS = 0x4D,
	TREBLE = 0x4E,
	BALANCE = 0x4F,
	
	LIST = 0x58,
	
	MENU = 0x5C,
	
	VOLUME_UP = 0x60,
	VOLUME_DOWN = 0x64,
	
	LEFT_REPEAT = 0x70,
	RIGHT_REPEAT = 0x71,
	UP_REPEAT = 0x72,
	DOWN_REPEAT = 0x73,
	
	GO_REPEAT = 0x75,
	GREEN_REPEAT = 0x76,
	YELLOW_REPEAT = 0x77,
	BLUE_REPEAT = 0x78,
	RED_REPEAT = 0x79,
	
	EXIT = 0x7F,
	TV = 0x80,
	RADIO = 0x81,
	VIDEO_AUX = 0x82,
	AUDIO_AUX = 0x83,
	
	VIDEO_TAPE = 0x85,
	DVD = 0x86,
	CAMCORD = 0x87,
	TEXT = 0x88,
	SP_DEMO = 0x89,
	DIGITAL_TV = 0x8A,
	PC = 0x8B,
	
	DOOR_CAM = 0x8D,
	AUDIO_TAPE = 0x91,
	CD = 0x92,
	PHONO = 0x93,
	AUDIO_TAPE_2 = 0x94,
	
	CD2 = 0x97,
	
	LIGHT = 0x9B,
	
	AV = 0xBF,
	
	YELLOW = 0xD4,
	GREEN = 0xD5,
	BLUE = 0xD8,
	RED = 0xD9
} beo_command;


#endif
