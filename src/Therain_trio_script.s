.text
.thumb
.align 2

.include "defines/asm_defines.s"
.include "defines/xse_commands.s"

.global Therain_trio_script

Therain_trio_script:
lock
special 0x9F
waitstate
bufferpartypokemon 0x1 0x8004
callasm Therain_trio_form_change+1
compare 0x800D 0x1
if 0x1 _goto changed_to_therain
compare 0x800D 0x2
if 0x1 _goto changed_to_incarnate
msgbox wont_have_effect_string MSG_KEEPOPEN
closeonkeypress
release
end

changed_to_therain:
msgbox Hoopa_changed_to_therain_string MSG_KEEPOPEN
closeonkeypress
release
end

changed_to_incarnate:
msgbox Hoopa_changed_to_incarnate_string MSG_KEEPOPEN
closeonkeypress
release
end

Hoopa_changed_to_therain_string:
.byte 0xFD, 0x3, Space, c_, h_, a_, n_, g_, e_, d_, Space, t_, o_, Space, T_, h_, e_, r_, a_, i_, n_, Space, f_, o_, r_, m_, Exclam, Termin

Hoopa_changed_to_incarnate_string:
.byte 0xFD, 0x3, Space, c_, h_, a_, n_, g_, e_, d_, Space, t_, o_, Space, I_, n_, c_, a_, r_, n_, a_, t_, e_, Space, f_, o_, r_, m_, Exclam, Termin

wont_have_effect_string:
.byte I_, t_, Space, w_, o_, n_, t_, Space, h_, a_, v_, e_, Space, a_, n_, y_, Space, e_, f_, f_, e_, c_, t_, Exclam, Termin
