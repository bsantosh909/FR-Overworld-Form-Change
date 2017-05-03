#include "defines.h"

////////////////////////////
// The below lines are for handling the deoxys form change, if you dont want to add it then simply remove all these lines //
////////////////////////////

bool check_deoxys(u16 species)
{
    bool it_is = false;
    switch(species)
    {
    case POKE_DEOXYS:
    case POKE_DEOXYS_ATTACK:
    case POKE_DEOXYS_DEFENSE:
    case POKE_DEOXYS_SPEED:
        it_is = true;
    }
    return it_is;
}

void find_deoxys_in_party()
{
    struct *pokemon poke;
    u8 total_deoxys=0;
    u8 first_slot=0;
    for (u8 i=0;i<6;i++)
    {
        poke = &party_player[i];
        u16 species = get_attr(poke,ATTR_SPECIES,0);
        if (check_deoxys(species))
        {
            count++;
            if (count == 1)
                first_slot=1;
            else
                break;
        }
    }
    switch(count)
    {
    case 0:
        var_800D_lastresult=0;
        break;
    case 1:
        var_800D_lastresult=1;
        var_8004=first_slot;
        break;
    case default:
        var_800D_lastresult=2;
        break;
    }
}

void deoxys_formes_change()
{
    u8 i = var_8004;
    u16 target_species;
    struct *pokemon poke = &party_player[i];
    u16 species = get_attr(poke, ATTR_SPECIES, 0);

    switch(species)
    {
    case POKE_DEOXYS:
        target_species=POKE_DEOXYS_ATTACK;
        var_800D_lastresult=1;
        break;
    case POKE_DEOXYS_ATTACK:
        target_species=POKE_DEOXYS_DEFENSE;
        var_800D_lastresult=2;
        break;
    case POKE_DEOXYS_DEFENSE:
        target_species=POKE_DEOXYS_SPEED;
        var_800D_lastresult=3;
        break;
    case POKE_DEOXYS_SPEED:
        target_species=POKE_DEOXYS;
        var_800D_lastresult=4;
        break;
    }
    set_attr(poke, ATTR_SPECIES,&target_species);
    calculate_stats_pokekmon(poke);
}

void validate_choosen_pokemon()
{
    struct *pokemon poke = &party_player[var_8004];
    u16 species = get_attr(poke, ATTR_SPECIES,0);
    if (check_deoxys(species))
        var_800D_lastresult=1;
    else
        var_800D_lastresult=0;
}

////////////////////////////
// The  deoxys form change handling ends here.. if you dont want the deoxys form change these remove lines upto here from previous mark //
////////////////////////////
