#include "defines.h"

u16 arceus_mapping[0x18]=
{
    0,
    POKE_ARCEUS_FIGHTING,
    POKE_ARCEUS_FLYING,
    POKE_ARCEUS_POISON,
    POKE_ARCEUS_GROUND,
    POKE_ARCEUS_ROCK,
    POKE_ARCEUS_BUG,
    POKE_ARCEUS_GHOST,
    POKE_ARCEUS_STEEL,
    0,
    POKE_ARCEUS_FIRE,
    POKE_ARCEUS_WATER,
    POKE_ARCEUS_GRASS,
    POKE_ARCEUS_ELECTRIC,
    POKE_ARCEUS_PSYCHIC,
    POKE_ARCEUS_ICE,
    POKE_ARCEUS_DRAGON,
    POKE_ARCEUS_DARK,
    0,
    0,
    0,
    0,
    0,
    POKE_ARCEUS_FAIRY
};

u16 silvally_mapping[0x18]=
{
    0,
    POKE_SILVALLY_FIGHTING,
    POKE_SILVALLY_FLYING,
    POKE_SILVALLY_POISON,
    POKE_SILVALLY_GROUND,
    POKE_SILVALLY_ROCK,
    POKE_SILVALLY_BUG,
    POKE_SILVALLY_GHOST,
    POKE_SILVALLY_STEEL,
    0,
    POKE_SILVALLY_FIRE,
    POKE_SILVALLY_WATER,
    POKE_SILVALLY_GRASS,
    POKE_SILVALLY_ELECTRIC,
    POKE_SILVALLY_PSYCHIC,
    POKE_SILVALLY_ICE,
    POKE_SILVALLY_DRAGON,
    POKE_SILVALLY_DARK,
    0,
    0,
    0,
    0,
    0,
    POKE_SILVALLY_FAIRY
};

void change_form_on_item_give(struct pokemon *poke, u16 item_id)
{
    u16 target_species=0;
    u16 species = get_attr(poke,ATTR_SPECIES,0);
    u8 ability = get_poke_ability(poke);
    switch(species)
    {
    case POKE_GIRATINA:
        if(get_item_x12_battle_function(item_id)==ITEM_EFFECT_GRISEOUSORB)
        {
            target_species = POKE_GIRATINA_O;
        }
        break;
    case POKE_GIRATINA_O:
        if(get_item_x12_battle_function(item_id)!=ITEM_EFFECT_GRISEOUSORB)
        {
            target_species = POKE_GIRATINA;
        }
        break;
    case POKE_GENESECT:
    case POKE_GENESECT_BURN:
    case POKE_GENESECT_CHILL:
    case POKE_GENESECT_DOUSE:
    case POKE_GENESECT_SHOCK:
        if(get_item_x12_battle_function(item_id)==ITEM_EFFECT_DRIVES)
        {
            switch(get_item_lastword(item_id))
            {
            case DOUSE_DRIVE_EFFECT:
                target_species=POKE_GENESECT_DOUSE;
                break;
            case BURN_DRIVE_EFFECT:
                target_species=POKE_GENESECT_BURN;
                break;
            case CHILL_DRIVE_EFFECT:
                target_species=POKE_GENESECT_CHILL;
                break;
            case SHOCK_DRIVE_EFFECT:
                target_species=POKE_GENESECT_SHOCK;
                break;
            }
        }
        if(target_species==0)
        {
            target_species=POKE_GENESECT;
        }
        if(target_species==species)
        {
            target_species=0;
        }
        break;
    }
    switch(ability)
    {
    case ABILITY_MULTITYPE:
        if(get_item_x12_battle_function(item_id)==ITEM_EFFECT_PLATES)
        {
            target_species=arceus_mapping[get_item_lastword(item_id)];
        }
        if(target_species==0)
        {
            target_species=POKE_ARCEUS;
        }
        break;
    case ABILITY_RKS_SYSTEM:
        if(get_item_x12_battle_function(item_id)==ITEM_EFFECT_MEMORIES)
        {
            target_species=silvally_mapping[get_item_lastword(item_id)];
        }
        if(target_species==0)
        {
            target_species=POKE_SILVALLY;
        }
        break;
    }
    if(target_species && target_species!=species)
    {
        set_attr(poke,ATTR_SPECIES,&target_species);
        calculate_stats_pokekmon(poke);
    }
}

void change_form_on_item_remove(struct pokemon* poke)
{
    u16 target_species=0;
    u16 species = get_attr(poke,ATTR_SPECIES,0);
    u8 ability = get_poke_ability(poke);

    switch(species)
    {
    case POKE_GIRATINA_O:
            target_species = POKE_GIRATINA;
        break;
    case POKE_GENESECT_BURN:
    case POKE_GENESECT_CHILL:
    case POKE_GENESECT_DOUSE:
    case POKE_GENESECT_SHOCK:
            target_species=POKE_GENESECT;
        break;
    }
    switch(ability)
    {
    case ABILITY_MULTITYPE:
            target_species=POKE_ARCEUS;
        break;
    case ABILITY_RKS_SYSTEM:
            target_species=POKE_SILVALLY;
        break;
    }
    if(target_species && target_species!=species)
    {
        set_attr(poke,ATTR_SPECIES,&target_species);
        calculate_stats_pokekmon(poke);
    }
}

void give_item_to_poke(struct pokemon *poke, u16 item_id)
{
    if(!item_is_mail(item_id) || prepare_party_mail_to_give(poke,item_id)!=0xFF)
    {
        set_attr(poke,ATTR_HELD_ITEM,&item_id);
        change_form_on_item_give(poke,item_id);
    }
}

enum take_status
{
    NO_ITEM_TO_TAKE,
    ITEM_TAKE_BAG_FULL,
    ITEM_TAKE_SUCCESS
};

enum take_status take_item_from_poke(struct pokemon *poke)
{
    enum take_status can_take = NO_ITEM_TO_TAKE;
    u16 item_id = get_attr(poke,ATTR_HELD_ITEM,0);

    if(item_id)
    {
        if(bag_add_item(item_id,1))
        {
            item_id=0;
            set_attr(poke,ATTR_HELD_ITEM,&item_id);
            change_form_on_item_remove(poke);
            can_take = ITEM_TAKE_SUCCESS;
        }
        else
        {
            can_take = ITEM_TAKE_BAG_FULL;
        }

    }
    return can_take;
}
