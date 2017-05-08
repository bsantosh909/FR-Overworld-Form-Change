	.text
	.align 1
	
	.force_thumb
	.syntax unified
	.global __gnu_thumb1_case_uqi
	.thumb_func
	.type __gnu_thumb1_case_uqi,function
__gnu_thumb1_case_uqi:
	push	{r1}
	mov	r1, lr
	lsrs	r1, r1, #1
	lsls	r1, r1, #1
	ldrb	r1, [r1, r0]
	lsls	r1, r1, #1
	add	lr, lr, r1
	pop	{r1}
	bx	lr
	.size __gnu_thumb1_case_uqi, . - __gnu_thumb1_case_uqi
	
	.force_thumb
	.syntax unified
	.global __gnu_thumb1_case_uhi
	.thumb_func
	.type __gnu_thumb1_case_uhi,function
__gnu_thumb1_case_uhi:
	push	{r0, r1}
	mov	r1, lr
	lsrs	r1, r1, #1
	lsls	r0, r0, #1
	lsls	r1, r1, #1
	ldrh	r1, [r1, r0]
	lsls	r1, r1, #1
	add	lr, lr, r1
	pop	{r0, r1}
	bx	lr
	.size __gnu_thumb1_case_uhi, . - __gnu_thumb1_case_uhi

    .force_thumb
    .syntax unified
    .global __gnu_thumb1_case_sqi
    .thumb_func
    .type __gnu_thumb1_case_sqi,function
__gnu_thumb1_case_sqi:
     push    {r1}
     mov r1, lr
     lsrs    r1, r1, #1
     lsls    r1, r1, #1
     ldrsb   r1, [r1, r0]
     lsls    r1, r1, #1
     add lr, r1
     pop {r1}
     bx  lr
    .size __gnu_thumb1_case_sqi, . - __gnu_thumb1_case_sqi
	
    .force_thumb
    .syntax unified
    .global __aeabi_uidiv
    .thumb_func
    .type __aeabi_uidiv,function
__aeabi_uidiv:
	ldr r3, =(__udivsi3)
	bx r3
	.size __aeabi_uidiv, . - __aeabi_uidiv
	
    .force_thumb
    .syntax unified
    .global __aeabi_idiv
    .thumb_func
    .type __aeabi_idiv,function
__aeabi_idiv:
	ldr r3, =(__divsi3)
	bx r3
	.size __aeabi_idiv, . - __aeabi_idiv
	
    .force_thumb
    .syntax unified
    .global memcpy
    .thumb_func
    .type memcpy,function
memcpy:
	ldr r3, =(memcpy_)
	bx r3
	.size memcpy, . - memcpy
	
    .force_thumb
    .syntax unified
    .global memset
    .thumb_func
    .type memset,function
memset:
	ldr r3, =(memset_)
	bx r3
	.size memset, . - memset
	
    .force_thumb
    .syntax unified
    .global malloc
    .thumb_func
    .type malloc,function
malloc:
	ldr r3, =(malloc_)
	bx r3
	.size malloc, . - malloc
	
    .force_thumb
    .syntax unified
    .global free
    .thumb_func
    .type free,function
free:
	ldr r1, =(free_)
	bx r1
	.size free, . - free
