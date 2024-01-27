#ifndef GAME_DATA_H_
#define GAME_DATA_H_

#include "../common.h"


typedef struct{
    //hitbox
    float x, y;
    float width, height;

    float target_dx;//displace victim
    float target_dy;//displace victim

    uint8_t damage;

    ENU_ATTACK_TYPE enuType;
}ATK_INFO;//todo:create attack queue


typedef struct{
    float dx;
    float x;
    float y;
    float width, height;
    uint8_t layer;//unused, use later to define which layer

    bool bIsLooping;

    SDL_Texture *img;
}SCROLLING_BG;//scrolling background


typedef struct FRAME{
    bool active;
    uint32_t x;
    uint32_t y;
    uint8_t data;
}ANIMATION_FRAME;

//tyoe for general animation data
typedef struct ANIMATION{
    char name[20];
    ANIMATION_FRAME frames[MAX_SEQUENCES][MAX_FRAMES];
    int8_t transition_table[MAX_CHARACTER_STATES][MAX_SEQUENCES];//for when a sequence is interrupted by a state
    uint8_t default_seqs[MAX_CHARACTER_STATES];//index is player state, value is sequence, default to this if there is nothing in transition table

    uint8_t sprite_w;//visual width, used in rednering, must be bigger than logical width
    uint8_t sprite_h;//visual height, used in rednering, must be bigger than logical height
    int8_t sprite_x_displacement;
    int8_t sprite_y_displacement;
    uint32_t sprite_scale;//visual scale of the sprite

    ATK_INFO attacks[NUMBER_OF_ATTACKS_PER_ANIMATION];

    SDL_Texture *sprite_sheet;
}ANIMATION;

//tyoe for animation processing
typedef struct ANIMATOR{
    /*animation*/
    ANIMATION *ptr_animation;

    uint8_t current_squence;
    uint8_t current_frame;
    bool animation_end;//only true when current frame goes beyond the last frame, i.e when current frame.active = false
    uint8_t frame_counter;//temporary frame counter that will be used to simulate animation, until we implement animation
    float animation_elapsed_time;//play animation if this is greater than 1/ANIMATION_PLAY_RATE, increment with delta time each logical frame.
    bool render_foreground;
    bool bLoop_animation;
    bool bImgFlip;
}ANIMATOR;

typedef struct{
    bool ACTIVE;

    uint8_t current_frame;
    ANIMATION_FRAME attack_frames[ATTACK_FRAMES_MAX];

    uint8_t active_frame; //frame where attack applies

    uint32_t x;
    uint32_t y;

    uint32_t w;
    uint32_t h;

    float animation_elapsed_time;

    SDL_Texture *sprite_sheet;
}ATK_INSTANCE;

typedef struct SLAVE_GEN_INFO{
    float speed;
    float hp;
    float scale;
    uint8_t max_health_factor; //multiply by it to increase max health
}SLAVE_GEN_INFO;

typedef struct CHARACTER{
    float x;uint16_t width;//logical width, used in physics
    float y;uint16_t height;//logical height, used in physics
    float dx;//movement step, change these to change x and Y, change by setting to WALK speed or gravity mutliplied by delta time
    float dy;

    float fProcessing_delay;//if this is not 0 certain processes will not happen to the player, physics, fsm and attacks

    /*animation*/
    ANIMATOR;//animation_clip

   /*gameplay*/
    ENU_AISTATE enu_AIState;// maybe this shouldn't be here
    ENU_PLAYER_STATE enu_playerState;
    ENU_PLAYER_STATE enu_cachedState;
    float fParry_timer;
    int32_t hp;
    float fBullet_cooldown;
    float fGothit_timer;
    bool bCan_attack;
    bool bIsHit;
    uint8_t u8MaxHealthFactor;

    /*control*/
    bool bIs_firing;//if true let out a bullet in bullets.c, disgusting i know but make do for now
    bool bAction_atk;/*true if you want to attack*/
    bool bAction_parry;/*true if you want to parry*/
    int8_t iMove_horizontal;/*1 or -1 */
    int8_t iMove_vertical;/*1 or -1*/
    bool bHuman;//ai or human? if human control using joypad or whatever. this is disgusting we should do it using a function pointer, or just have a different module for boss

}CHARACTER;

typedef struct BULLET{
    float x;
    float y;
    float dx;
    float dy;
    float fProcessing_delay;
    uint8_t anim_frame;
    ENU_DIRECTION dir;//1 or -1
}BULLET;

//map element to define relationship between action and button/buttons
typedef struct INPUT_MAP_ELEMENT{
    uint8_t keyboard_value;
    uint8_t joypad_value;
}INPUT_MAP_ELEMENT;


/*level related structs*/
typedef struct{
    uint16_t u16PosX;//if this is a certain magic number then it means there are no more spots, trick to save memory
    uint16_t u16PosY;
    uint8_t u8AnimationIndex;//what kind of character would be spaned at that level spot
}LEVEL_SPOT;

/*each level is divided into sections, each sections has spawn spots we move to the next section when all enemies are dead? or whatever criteria*/
typedef struct{
    uint8_t u8current_section;
    uint8_t u8max_sections;
    LEVEL_SPOT spots[MAX_SECTIONS][MAX_SPOTS];
}LEVEL;

extern CHARACTER gData_player;
extern CHARACTER gData_boss;
extern CHARACTER gData_slaves[];
extern BULLET gData_bullets[];
extern LEVEL levels[];

extern INPUT_MAP_ELEMENT input_map[];
extern SCROLLING_BG scrolling_backgrounds[];
extern ANIMATION animations[];

extern ATK_INSTANCE gData_attack_instance_player;
extern SLAVE_GEN_INFO gData_slave_gen_info;//info for generating slaves

void GAMEDATA_init();

#endif // GAME_DATA_H_
