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
    struct pokemon* poke;
    u8 total_deoxys=0;
    u8 first_slot=0;
    for (u8 i=0;i<6;i++)
    {
        poke = &party_player[i];
        u16 species = get_attr(poke,ATTR_SPECIES,0);
        if (check_deoxys(species))
        {
            total_deoxys++;
            if (total_deoxys == 1)
            {
                first_slot=1;
            }
            else
            {
                break;
            }
        }
    }
    switch(total_deoxys)
    {
    case 0:
        var_800D_lastresult=0;
        break;
    case 1:
        var_800D_lastresult=1;
        var_8004=first_slot;
        break;
    default:
        var_800D_lastresult=2;
        break;
    }
}

void deoxys_formes_change()
{
    u8 i = var_8004;
    u16 target_species;
    struct pokemon* poke = &party_player[i];
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
    struct pokemon* poke = &party_player[var_8004];
    u16 species = get_attr(poke, ATTR_SPECIES,0);
    if (check_deoxys(species))
        var_800D_lastresult=1;
    else
        var_800D_lastresult=0;
}

////////////////////////////
// The  deoxys form change handling ends here.. if you dont want the deoxys form change these remove lines upto here from previous mark //
////////////////////////////



////////////////////////////
// The below lines are for handling the rotom form change, if you dont want to add it then simply remove all these lines //
////////////////////////////

struct rotom_set
{
    enum rotom_forms form_index;
    u16 special_move;
};

#define NO_OF_ALTERNATE_ROTOM_FORMS 6
struct rotom_set rotom_move_mapping[NO_OF_ALTERNATE_ROTOM_FORMS] = {{POKE_ROTOM_HEAT,MOVE_OVERHEAT},{POKE_ROTOM_WASH,MOVE_HYDRO_PUMP},
            {POKE_ROTOM_FROST,MOVE_BLIZZARD},{POKE_ROTOM_FAN,MOVE_AIR_SLASH},{POKE_ROTOM_MOW,MOVE_LEAF_STORM}};

u16 get_rotom_form_special_move(u16 species)
{
    u16 special_move=0;
    for(u8 j=0;j<NO_OF_ALTERNATE_ROTOM_FORMS;j++)
    {
        if(species==rotom_move_mapping[j].form_index)
        {
            special_move=rotom_move_mapping[j].special_move;
            break;
        }
    }
    return special_move;
}

bool is_valid_rotom(u16 species)
{
    bool valid_rotom=false;
    if(species==POKE_ROTOM || get_rotom_form_special_move(species))
    {
        valid_rotom=true;
    }
    return valid_rotom;
}

void find_rotom()
{
    struct pokemon* poke;
    u8 count=0;
    u16 first_index=0x0;
    u8 first_slot=0;
    for(u8 i=0;i<6;i++)
    {
        poke = &party_player[i];
        u16 species = get_attr(poke,ATTR_SPECIES,0);
        if(is_valid_rotom(species))
        {
            count++;
            if(count==1)
            {
                first_slot=i;
                first_index=species;
            }
            else if(count==2)
            {
                break;
            }
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
        var_8003=get_rotom_form_special_move(first_index);
        break;
    default:
        var_800D_lastresult=2;
        break;

    }
}

void check_chosen_rotom()
{
    struct pokemon* poke = &party_player[var_8004];
    u16 species = get_attr(poke,ATTR_SPECIES,0);
    if(is_valid_rotom(species))
    {
        var_8003=get_rotom_form_special_move(species);
        var_800D_lastresult=1;
    }
    else
    {
        var_800D_lastresult=0;
    }
}


void rotom_change()
{
    if(var_800D_lastresult==0x5)
    {
        var_8005=POKE_ROTOM;
    }
    else
    {
        var_8005=rotom_move_mapping[var_800D_lastresult].form_index;
    }
    u16 target_species=var_8005;
    u8 move_slot_to_purge=4;
    u16 special_move_to_remove=var_8003;
    u8 i=var_8004;

    struct pokemon* poke = &party_player[i];
    u16 species = get_attr(poke,ATTR_SPECIES,0);
    if(species!=target_species)
    {
        if(species!=POKE_ROTOM)
        {
            for(u8 j=0;j<4;j++)
            {
                u16 moveset_move=get_attr(poke,ATTR_ATTACK_1+j,0);
                if(moveset_move==0)
                {
                    break;
                }
                if(special_move_to_remove==moveset_move) //0x0 in rotom's case
                {
                    move_slot_to_purge=j;
                    break;
                }
            }
            if(move_slot_to_purge==4)
            {
                var_800D_lastresult=2;
            }
            else
            {
                var_8005=move_slot_to_purge;
                if(target_species==POKE_ROTOM)
                {
                    var_800D_lastresult=3;
                }
                else
                {
                    var_800D_lastresult=1;
                }
            }
        }
        else
        {
            var_800D_lastresult=2;
        }
        set_attr(poke,ATTR_SPECIES,&target_species);
        calculate_stats_pokekmon(poke);
        var_8004=i;
    }
    else
    {
        if(species!=POKE_ROTOM)
        {
            var_800D_lastresult=0;
        }
        else
        {
            var_800D_lastresult=4;
        }

    }
}


void rotom_determine_special_move()
{
    var_800D_lastresult=0;
    u16 special_move_to_learn=0;
    u8 i=var_8004;
    struct pokemon* poke = &party_player[i];
    u16 species = get_attr(poke,ATTR_SPECIES,0);
    if(species!=POKE_ROTOM)
    {
        special_move_to_learn=get_rotom_form_special_move(species);
    }
    else
    {
        if(!get_attr(poke,ATTR_ATTACK_1,0))
        {
            special_move_to_learn=MOVE_THUNDER_SHOCK;
        }
    }
    if(special_move_to_learn)
    {
        var_8006=special_move_to_learn;
    }
}

void rotom_learn_special_move_func()
{
    struct pokemon* poke=&party_player[var_8004];
    teach_move_in_available_slot(poke,var_8006);
}

void store_move_to_var8003_from_var8005_in_slot_var8004()
{
    struct pokemon* poke=&party_player[var_8004];
    var_8003 = get_attr(poke,ATTR_ATTACK_1+var_8005,0);
}




////////////////////////////
// The  deoxys form change handling ends here.. if you dont want the deoxys form change these remove lines upto here from previous mark //
////////////////////////////
