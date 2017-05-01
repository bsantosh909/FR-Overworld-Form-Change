.text
.thumb
.align 2

.include "defines/asm_defines.s"
.include "defines/xse_commands.s"

.global shaymin_script

shaymin_script:
lock
special 0x9F
waitstate
bufferpartypokemon 0x1 0x8004
callasm Shaymin_form_change+1
compare 0x800D 0x0
if 0x1 _goto not_affecting_dud
msgbox shaymin_changed_string MSG_KEEPOPEN
closeonkeypress
release
end

not_affecting_dud:
msgbox wont_have_effect_string MSG_KEEPOPEN
closeonkeypress
release
end

shaymin_changed_string:
.byte 0xFD, 0x3, Space, c_, h_, a_, n_, g_, e_, d_, Space, f_, o_, r_, m_, Exclam, Termin

wont_have_effect_string:
.byte I_, t_, Space, w_, o_, n_, t_, Space, h_, a_, v_, e_, Space, a_, n_, y_, Space, e_, f_, f_, e_, c_, t_, Exclam, Termin
