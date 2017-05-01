#include "defines.h"

// ---------- importing the script file ----------- //
void *shaymin_script();
void *Hoopa_script();
//---------- end of import ----------- //


// rest lines till I write shaymin form change end are the functions for handling shaymin form //
// these are the function that is directly got from KDS EM repo so full credits to him for these and also darthathron and EGG for original asm routines ! //
void run_script_from_item_shaymin(int taskID)
{
    script_env_2_enable(taskID);
    script_run(shaymin_script);
    task_delete(taskID);
}

void item_forme_change_handler_shaymin()
{
    routine_to_run_after_graphics = (void *) &run_script_from_item_shaymin;
    run_after_graphics();
}
//end of the function copy //

void Shaymin_form_change()
{
	//special 9F for single poke //
    struct pokemon *poke = &party_player[var_8004];
    u16 species = get_attr(poke,ATTR_SPECIES,0);
    var_800D_lastresult =0;
    if (species == SHAYMIN_LAND)
    {
        var_800D_lastresult =1;
        u16 final_species = SHAYMIN_FLY;
        set_attr(poke, ATTR_SPECIES,&final_species);
        calculate_stats_pokekmon(poke);
    }
}
//shaymin form change end here//


// rest lines till I write shaymin form change end are the functions for handling hoopa form //
// these are the function that is directly got from KDS EM repo so full credits to him for these and also darthathron and EGG for original asm routines ! //
void run_script_from_item_hoopa(int taskID)
{
    script_env_2_enable(taskID);
    script_run((void *)0x8BBBBBB);
    task_delete(taskID);
}

void item_forme_change_handler_hoopa()
{
    routine_to_run_after_graphics = (void *) &run_script_from_item_hoopa;
    run_after_graphics();
}
//end of the function copy //

void Hoopa_form_change()
{
		struct pokemon *poke = &party_player[var_8004];
		u16 species = get_attr(poke,ATTR_SPECIES,0);
		var_800D_lastresult=0;
		if(species == HOOPA_CONFINED)
		{
			var_800D_lastresult = 1;
			u16 final_species = HOOPA_UNBOUND;
			set_attr(poke,ATTR_SPECIES,&final_species);
			calculate_stats_pokekmon(poke);
		}
				
}
//shaymin form change end here//