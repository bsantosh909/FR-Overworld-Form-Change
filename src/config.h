#ifndef CONFIG_H
#define CONFIG_H

#include "types.h"

// ------------------ shaymin form handling ------------------ //
#define SHAYMIN_FLY POKE_CHARIZARD
#define SHAYMIN_LAND POKE_SQUIRTLE
// ------------------ ------------------ ------------------ //


// ------------------ hoopa form handling ------------------ //
#define HOOPA_UNBOUND POKE_CHARIZARD
#define HOOPA_CONFINED POKE_SQUIRTLE
// ------------------ ------------------ ------------------ //


// ------------------ therain trio form handling ------------------ //
#define TORNADUS_INCARNATE POKE_CHARIZARD
#define TORNADUS_THERIAN POKE_SQUIRTLE
#define THUNDURUS_INCARNATE POKE_BLASTOISE
#define THUNDURUS_THERIAN POKE_RATTATA
#define LANDORUS_INCARNATE POKE_VENUSAUR
#define LANDORUS_THERIAN POKE_WEEDLE
// ------------------ ------------------ ------------------ //


// ------------------ Rotom form handling ------------------ //
#define NO_OF_ALTERNATE_ROTOM_FORMS 6
#define POKE_ROTOM POKE_TREECKO
enum rotom_forms
{
    POKE_ROTOM_HEAT=0x116,
    POKE_ROTOM_WASH,
    POKE_ROTOM_FROST,
    POKE_ROTOM_FAN,
    POKE_ROTOM_MOW
};
// ------------------ ------------------ ------------------ //


// ------------------ Deoxys form handling ------------------ //
enum deoxys_forms
{
    POKE_DEOXYS_ATTACK=1450,
    POKE_DEOXYS_DEFENSE,
    POKE_DEOXYS_SPEED,
};

// ------------------ ------------------ ------------------ //



#endif /* CONFIG_H */
