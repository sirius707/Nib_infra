#ifndef PROGRAM_DATA_H_
#define PROGRAM_DATA_H_

#include "../common.h"

typedef struct {
	void (*logic)(void);
	void (*render)(void);
} DELEGATE;

//in this struct program data and settings will be stored
typedef struct PROGRAM{
	SDL_Renderer *renderer;
	SDL_Window *window;

    uint16_t resolution_w;
    uint16_t resolution_h;
    uint8_t sound_volume;
    uint8_t brightness;

    GAME_STATE enuGameState;

    uint8_t fps;
    float delta_time;

	int keyboard[MAX_KEYBOARD_KEYS];
    int joypad[MAX_JOYPAD_KEYS];
    int8_t x_axis;
    int8_t y_axis;

    DELEGATE functions;

}PROGRAM;

extern PROGRAM prog;

#endif
