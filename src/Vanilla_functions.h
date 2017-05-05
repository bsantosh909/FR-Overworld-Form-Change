#ifndef VANILLA_FUNCTIONS
#define VANILLA_FUNCTIONS

#include "defines.h"

u32 get_attr(struct pokemon* poke_address, u8 request, void* dst);
void set_attr(struct pokemon* poke_address, u8 request, void* new_value);
void calculate_stats_pokekmon(struct pokemon* poke);
u16 teach_move_in_available_slot(struct pokemon* , u16 move);

// used for form change //
void run_after_graphics();
void script_env_2_enable(int taskID);
void script_run(void *scriptLoc);
void task_delete(u8 taskID);
void* _memcpy(void *dst, void *src, u8 size);
void* _memset(void *dst, u8 pattern, u8 size);

#endif /* VANILLA_FUNCTIONS */
