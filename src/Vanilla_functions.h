#ifndef VANILLA_FUNCTIONS
#define VANILLA_FUNCTIONS

#include "defines.h"

u32 get_attr(struct pokemon* poke_address, u8 request, void* dst);
void set_attr(struct pokemon* poke_address, u8 request, void* new_value);
void calculate_stats_pokekmon(struct pokemon* poke);
u16 teach_move_in_available_slot(struct pokemon* , u16 move);
u16 bag_remove_item(u16 itemID, u16 quantity);

/* doing for held item form change */
u8 get_poke_ability(struct pokemon* poke);
u8 get_item_x12_battle_function(u16 item_id);
u32 get_item_lastword(u16 itemID);
u8 item_is_mail(u16 itemID);
u8 prepare_party_mail_to_give(struct pokemon* poke, u16 item);
bool bag_add_item(u16 item_id, u8 a);
// ends here //


// used for form change //
void run_after_graphics();
void script_env_2_enable(int taskID);
void script_run(void *scriptLoc);
void task_delete(u8 taskID);
void* memcpy_(void *dst, void *src, u8 size);
void* memset_(void *dst, u8 pattern, u8 size);

void pokemon_slot_purge(struct pokemon* poke);
void Special_DD_delete_move();
u8 party_move_up_no_free_slots_in_between();


#endif /* VANILLA_FUNCTIONS */
