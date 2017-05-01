#ifndef VANILLA_FUNCTIONS
#define VANILLA_FUNCTIONS

#include "defines.h"

u32 get_attr(struct pokemon* poke_address, u8 request, void* dst);
void set_attr(struct pokemon* poke_address, u8 request, void* new_value);
void calculate_stats_pokekmon(struct pokemon* poke);

// used for form change //
void run_after_graphics();
void script_env_2_enable(int taskID);
void script_run(void *scriptLoc);
void task_delete(u8 taskID);

#endif /* VANILLA_FUNCTIONS */
