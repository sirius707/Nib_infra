#include "prog_input.h"
#include "my_sdl_util.h"
#include "structs/program_data.h"

#define  JOYSTICK_DEAD_ZONE 8000

static void PROG_key_up(SDL_KeyboardEvent *event);
static void PROG_key_down(SDL_KeyboardEvent *event);
static void PROG_joykey_down(SDL_JoyButtonEvent *event);
static void PROG_joykey_up(SDL_JoyButtonEvent *event);
static void PROG_joyaxis(SDL_JoyAxisEvent *event);



void PROG_input(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				PROG_key_down(&event.key);
				break;

			case SDL_KEYUP:
				PROG_key_up(&event.key);
				break;

            case SDL_JOYBUTTONDOWN:  /* Handle Joystick Button Presses */
                PROG_joykey_down(&event.jbutton);
                break;
            case SDL_JOYBUTTONUP:  /* Handle Joystick Button Presses */
                PROG_joykey_up(&event.jbutton);
                break;
            case SDL_JOYAXISMOTION:
                PROG_joyaxis(&event.jaxis);
                //printf("x = %d y = %d \n", prog.x_axis, prog.y_axis);
                break;
			default:
				break;
		}
	}
	//puts("");
}


inline void PROG_key_up(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		prog.keyboard[event->keysym.scancode] = 0;
	}
}

inline void PROG_key_down(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		prog.keyboard[event->keysym.scancode] = 1;
	}
}

inline void PROG_joykey_down(SDL_JoyButtonEvent *event)
{
		prog.joypad[event->button] = 1;
}

inline void PROG_joykey_up(SDL_JoyButtonEvent *event)
{
		prog.joypad[event->button] = 0;
}

inline void PROG_joyaxis(SDL_JoyAxisEvent *e)
{
     //prog.x_axis = prog.y_axis = 0;

     //X axis motion
     if( e->axis == 0 ){

            if(e->value < -JOYSTICK_DEAD_ZONE)
                prog.x_axis = -1;
            else if(e->value > JOYSTICK_DEAD_ZONE)
                prog.x_axis = 1;
            else{
                    prog.x_axis = 0;
            }

     } //Y axis motion
     else if( e->axis == 1 ){

        if(e->value < -JOYSTICK_DEAD_ZONE)
                prog.y_axis = -1;
            else if(e->value > JOYSTICK_DEAD_ZONE)
                prog.y_axis = 1;
            else{
                    prog.y_axis = 0;
            }

     }else{
     }

}

