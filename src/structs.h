#ifndef POKESTRUCT
#define POKESTRUCT

#include "types.h"

struct pokemon{
    u32 PID;
    u32 OTID;
    char name[10];
    u16 language;
    u8 OT_name[7];
    u8 markings;
    u16 checksum;
    u16 padding_maybe;
    u8 data[48];
    u32 ailment;
    u8 level;
    u8 pokerus;
    u16 current_hp;
    u16 total_hp;
    u16 attack;
    u16 defense;
    u16 speed;
    u16 sp_attack;
    u16 sp_defense;
};


extern struct pokemon party_opponent[6];
extern struct pokemon party_player[6];



//Pokemon Basestats table

struct poke_basestats{
    u8 base_hp;
    u8 base_atk;
    u8 base_def;
    u8 base_spd;
    u8 base_spatk;
    u8 base_spdef;
    u8 type1;
    u8 type2;
    u8 catch_rate;
    u8 exp_yield;
    u16 evs_hp : 2;
    u16 evs_atk : 2;
    u16 evs_def : 2;
    u16 evs_spd : 2;
    u16 evs_spatk : 2;
    u16 evs_spdef : 2;
    u16 unused : 4;
    u16 item1;
    u16 item2;
    u8 gender_ratio;
    u8 hatching;
    u8 friendship;
    u8 exp_curve;
    u8 egg_group1;
    u8 egg_group2;
    u8 ability1;
    u8 ability2;
    u8 safari_flee_rate;
    u8 dex_colour;
    u8 padding1;
    u8 padding2;
};


#endif // POKESTRUCT
