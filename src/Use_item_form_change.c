#include "defines.h"

// ---------- importing the script file ----------- //
void *shaymin_script();
void *Hoopa_script();
void *Therain_trio_script();
//---------- end of import ----------- //


// rest lines are the functions for handling shaymin form //
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


// rest lines are the functions for handling hoopa form //
// these are the function that is directly got from KDS EM repo so full credits to him for these and also darthathron and EGG for original asm routines ! //
void run_script_from_item_hoopa(int taskID)
{
    script_env_2_enable(taskID);
    script_run(Hoopa_script);
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


// rest lines are the functions for handling therain trio form //
// these are the function that is directly got from KDS EM repo so full credits to him for these and also darthathron and EGG for original asm routines ! //
void run_script_from_item_Therain_trio(int taskID)
{
    script_env_2_enable(taskID);
    script_run(Therain_trio_script);
    task_delete(taskID);
}

void item_forme_change_handler_Therain_trio()
{
    routine_to_run_after_graphics = (void *) &run_script_from_item_Therain_trio;
    run_after_graphics();
}
//end of the function copy //

void Therain_trio_form_change()
{
		struct pokemon *poke = &party_player[var_8004];
		u16 species = get_attr(poke,ATTR_SPECIES,0);
		var_800D_lastresult=0;
		u16 target_species=0;
		u8 formtype=0;

		switch (species)
        {
        case TORNADUS_INCARNATE:
            target_species = TORNADUS_THERIAN;
            formtype = 1;
            break;

        case TORNADUS_THERIAN:
            target_species = TORNADUS_INCARNATE;
            formtype = 2;
            break;

        case THUNDURUS_INCARNATE:
            target_species = THUNDURUS_THERIAN;
            formtype = 1;
            break;

        case THUNDURUS_THERIAN:
            target_species = THUNDURUS_INCARNATE;
            formtype = 2;
            break;

        case LANDORUS_INCARNATE:
            target_species = LANDORUS_THERIAN;
            formtype = 1;
            break;

        case LANDORUS_THERIAN:
            target_species = LANDORUS_INCARNATE;
            formtype = 2;
            break;
	}
	if(formtype)
    {
        set_attr(poke,ATTR_SPECIES,&target_species);
        calculate_stats_pokekmon(poke);
        var_800D_lastresult=formtype;
    }
}
//threain trio form change end here//
