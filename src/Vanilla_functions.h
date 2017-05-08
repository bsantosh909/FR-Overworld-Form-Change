#ifndef VANILLA_FUNCTIONS
#define VANILLA_FUNCTIONS

#include "defines.h"

u32 __attribute__((long_call)) get_attr(struct pokemon* poke_address, u8 request, void* dst);
void __attribute__((long_call)) set_attr(struct pokemon* poke_address, u8 request, void* new_value);
void __attribute__((long_call)) calculate_stats_pokekmon(struct pokemon* poke);
u16 __attribute__((long_call)) teach_move_in_available_slot(struct pokemon* , u16 move);
u16 __attribute__((long_call)) bag_remove_item(u16 itemID, u16 quantity);

/* doing for held item form change */
u8 __attribute__((long_call)) get_poke_ability(struct pokemon* poke);
u8 __attribute__((long_call)) get_item_x12_battle_function(u16 item_id);
u32 __attribute__((long_call)) get_item_lastword(u16 itemID);
u8 __attribute__((long_call)) item_is_mail(u16 itemID);
u8 __attribute__((long_call)) prepare_party_mail_to_give(struct pokemon* poke, u16 item);
bool __attribute__((long_call)) bag_add_item(u16 item_id, u8 a);
// ends here //


// used for form change //
void __attribute__((long_call)) run_after_graphics();
void __attribute__((long_call)) script_env_2_enable(int taskID);
void __attribute__((long_call)) script_run(void *scriptLoc);
void __attribute__((long_call)) task_delete(u8 taskID);
void* __attribute__((long_call)) memcpy_(void *dst, void *src, u8 size);
void* __attribute__((long_call)) memset_(void *dst, u8 pattern, u8 size);

void __attribute__((long_call)) pokemon_slot_purge(struct pokemon* poke);
void __attribute__((long_call)) Special_DD_delete_move();
u8 __attribute__((long_call)) party_move_up_no_free_slots_in_between();


#endif /* VANILLA_FUNCTIONS */
