#include "defines.h"

void hoopa_revert_logic(void *dst, void *src)
{
    memcpy_(dst, src, 0x64);
    struct pokemon* poke = (struct pokemon *)dst;
    u16 species = get_attr(poke, ATTR_SPECIES,0);
    u16 target_species = 0;
    switch (species)
    {
    case HOOPA_UNBOUND:
        target_species=HOOPA_CONFINED;
        break;
    case SHAYMIN_FLY:
        target_species=SHAYMIN_LAND;
        break;
    }
    if (target_species)
    {
        set_attr(poke,ATTR_SPECIES,&target_species);
        calculate_stats_pokekmon(poke);
    }

}
