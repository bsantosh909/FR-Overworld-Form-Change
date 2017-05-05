.text
.align 2
.thumb

revert_hook:

add r1, r1, r2
bl hoopa_revert_logic
ldr r3, =0x8093020|1
bx r3
