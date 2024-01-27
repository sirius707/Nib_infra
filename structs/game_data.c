#include "game_data.h"
#include <stdlib.h>
#include "../common.h"
#include <stdlib.h>
#include <time.h>

ATK_INSTANCE gData_attack_instance_player;
CHARACTER gData_player;
CHARACTER gData_boss;
CHARACTER gData_slaves[SLAVE_ARRAY_SIZE];
BULLET gData_bullets[BULLET_ARRAY_SIZE];
ANIMATION animations[NUMBER_OF_ANIMATIONS];
LEVEL levels[MAX_LEVELS];

INPUT_MAP_ELEMENT input_map[NUM_OF_ACTIONS];
SCROLLING_BG scrolling_backgrounds[NUM_BACKGROUDNS];
SLAVE_GEN_INFO gData_slave_gen_info;

void GAMEDATA_init()
{
    srand(time(0));
    memset(&gData_player, 0, sizeof (gData_player));
    memset(&gData_attack_instance_player, 0, sizeof (gData_attack_instance_player));
    memset(&gData_boss, 0, sizeof (gData_boss));
    memset(gData_slaves, 0, SLAVE_ARRAY_SIZE*sizeof (gData_player));
    memset(gData_bullets, 0, BULLET_ARRAY_SIZE*sizeof (gData_player));
    memset(levels, 0, MAX_LEVELS*sizeof (LEVEL));
    memset(animations, 0, NUMBER_OF_ANIMATIONS*sizeof (ANIMATION));
    memset(&gData_slave_gen_info, 0, sizeof (gData_slave_gen_info));

    //gData_player.x = DEF_LOGIC_W/2.0 - (gData_player.width);
    //gData_player.y = DEF_LOGIC_H/2.0 - (gData_player.height);
    //gData_player.bCan_attack = true;
    //gData_player.hp = 20;

    gData_player.enu_playerState = PL_IDLE;

    gData_slave_gen_info.max_health_factor = 1;
    gData_slave_gen_info.hp = 100;
    gData_slave_gen_info.speed = 100;
    gData_slave_gen_info.scale = 1;

    input_map[FIRE].joypad_value    = 0;
    input_map[MELEE].joypad_value   = 3;
    input_map[SPECIAL].joypad_value = 1;
    input_map[PARRY].joypad_value   = 7;
}


