#include "program.h"
#include "structs/program_data.h"
#include "prog_input.h"
#include "common.h"

static SDL_Texture *background;
SDL_Texture *heiroglyphs;

/*static function declarations*/
static void sdl_init(void);
static void sdl_deinit(void);
static void filler(void);//filler function in place of unused function pointers
static void ___secret_render(void);
static void ___secret_init(void);
static inline long cap_framerate(long *then, float *remainder, size_t fps);


void PROG_init()
{
    memset(&prog, 0, sizeof(prog));//clear program data

    prog.resolution_h = DEF_LOGIC_H;
    prog.resolution_w = DEF_LOGIC_W;

    sdl_init();
    prog.fps = DEFAULT_FPS;
    prog.enuGameState = RUNNING;

    prog.functions.render = filler;
    prog.functions.logic = filler;

    background = SDL_CreateTexture( prog.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, prog.resolution_w, prog.resolution_h);

    prog.functions.render = ___secret_render;
}

void PROG_run()
{
    ___secret_render();

    //frame rate capping
    long then;
    float remaining_time = 0;

    then = SDL_GetTicks();

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;

    /*main loop*/
    while(prog.enuGameState != OVER){
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        PROG_input();
        (*prog.functions.logic)();
        (*prog.functions.render)();

        prog.delta_time = (double)((NOW - LAST)/ (double)SDL_GetPerformanceFrequency() );//temporary until a fix is found
        if(prog.delta_time > 1.0/prog.fps)prog.delta_time = 1.0/prog.fps;
        cap_framerate(&then, &remaining_time, prog.fps);

    }
}

void PROG_deinit()
{
    sdl_deinit();
}

void PROG_setRenderCbk(void (*vidRenderFPTR)(void))
{
    prog.functions.render = vidRenderFPTR;

}

void PROG_setUpdateCbk(void (*vidLogicFPTR)(void))
{
    prog.functions.logic  = vidLogicFPTR;
}

void sdl_init()
{

	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	prog.window = SDL_CreateWindow("NiB", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEF_SCREEN_W, DEF_SCREEN_H, windowFlags);

     if( SDL_NumJoysticks() < 1 ){
            printf( "Warning: No joysticks connected!\n" );
    }else{
        printf("%d\n", SDL_NumJoysticks());
        SDL_JoystickOpen(0);
        SDL_JoystickOpen(1);
    }

	if (!prog.window)
	{
		printf("Failed to open %d x %d window: %s\n", DEF_SCREEN_W, DEF_SCREEN_H, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	prog.renderer = SDL_CreateRenderer(prog.window, -1, rendererFlags);

	if (!prog.renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

    //SDL_SetWindowDisplayMode(prog.window, NULL);
    SDL_RenderSetLogicalSize(prog.renderer, DEF_LOGIC_W, DEF_LOGIC_H);
    puts(SDL_GetError());

    if(!IMG_Init(IMG_INIT_PNG)){
        printf("Failed to load image extention: %s\n", SDL_GetError());
		exit(1);
    }
	___secret_init();
}


void sdl_deinit()
{
    SDL_DestroyRenderer(prog.renderer);
	SDL_DestroyWindow(prog.window);
	SDL_DestroyTexture(heiroglyphs);
	SDL_DestroyTexture(background);
	SDL_Quit();
}

void filler()
{
    //puts("you shouldnt see this.");

}

static void ___secret_render(void)
{
    static float col = 0;
    SDL_SetRenderDrawColor(prog.renderer, col, col , 242, 255);
    SDL_RenderClear(prog.renderer);

    SDL_Rect source;
    SDL_Rect rect;

    source.x = 0;
    source.y = 70;
    source.w = 70;
    source.h = 60;
    rect.x = DEF_SCREEN_W/2 - 140;
    rect.y = DEF_SCREEN_H/2;
    rect.w = 70;
    rect.h = 70;
    SDL_RenderCopy(prog.renderer, heiroglyphs, &source, &rect);

    source.x = 300;
    source.y = 0;
    source.w = 40;
    source.h = 64;
    rect.x = DEF_SCREEN_W/2 - 100;
    rect.y = DEF_SCREEN_H/2;
    rect.w = 70;
    rect.h = 70;
    SDL_RenderCopy(prog.renderer, heiroglyphs, &source, &rect);

    source.x = 240;
    source.y = 0;
    source.w = 40;
    source.h = 64;
    rect.x = DEF_SCREEN_W/2 - 60;
    rect.y = DEF_SCREEN_H/2;
    rect.w = 70;
    rect.h = 70;
    SDL_RenderCopy(prog.renderer, heiroglyphs, &source, &rect);

    source.x = 115;
    source.y = 60;
    source.w = 60;
    source.h = 64;
    rect.x = DEF_SCREEN_W/2 - 20;
    rect.y = DEF_SCREEN_H/2;
    rect.w = 70;
    rect.h = 70;
    SDL_RenderCopy(prog.renderer, heiroglyphs, &source, &rect);

	SDL_RenderPresent(prog.renderer);

    col += 100 * prog.delta_time;
    if(col > 255)col = 255;

}

static void ___secret_init(void)
{
    SDL_Surface *temp_surface = SDL_LoadBMP("data\\hiro.bmp");
    heiroglyphs = accelerate_surface(temp_surface, prog.renderer, SDL_MapRGB(temp_surface->format, 255, 255, 255));
}

static inline long cap_framerate(long *then, float *remainder, size_t fps)
{
	long wait, frameTime;

	wait = 1000/fps + *remainder;
	*remainder -= (int)*remainder;
	frameTime = SDL_GetTicks() - *then;
	wait -= frameTime;

	if (wait < 1){
		wait = 1;
	}


	SDL_Delay(wait);
	*remainder += 0.667;
	*then = SDL_GetTicks();

	return frameTime;
}

