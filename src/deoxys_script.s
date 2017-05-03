.text
.thumb

.include "defines/asm_defines.s"
.include "defines/xse_commands.s"

deoxys_main:
	lock
	msgbox meteorite_detection_string MSG_KEEPOPEN
	closeonkeypress
	callasm find_deoxys_in_party+1
	compare 0x800D 0x0
	if 0x1 _goto finish_deoxys_menu
	compare 0x800D 0x2
	if 0x1 _goto choose_candidate_deoxys

reaction_prompt:
	bufferpartypokemon 0x1 0x8004
	msgbox deoxys_reaction_string MSG_KEEPOPEN
	closeonkeypress
	msgbox reaction_prompt_string MSG_YESNO
	compare 0x800D 0x0
	callasm deoxys_formes_change+1
	compare 0x800D 0x1
	if 0x1 _call change_to_attack
	compare 0x800D 0x2
	if 0x1 _call change_to_defense
	compare 0x800D 0x3
	if 0x1 _call change_to_speed
	compare 0x800D 0x4
	if 0x1 _call change_to_original

finish_deoxys_menu:
	release
	end

choose_candidate_deoxys:
	special 0x9F
	waitstate
	callasm validate_choosen_pokemon+1
	compare 0x800D 0x1
	if 0x1 _goto reaction_prompt
	msgbox not_valid_deoxys_msg MSG_KEEPOPEN
	closeonkeypress
	goto finish_deoxys_menu

change_to_attack:
	msgbox attack_forme_string MSG_KEEPOPEN
	closeonkeypress
	return

change_to_defense:
	msgbox defense_forme_string MSG_KEEPOPEN
	closeonkeypress
	return

change_to_speed:
	msgbox speed_forme_string MSG_KEEPOPEN
	closeonkeypress
	return

change_to_original:
	msgbox balance_forme_string MSG_KEEPOPEN
	closeonkeypress
	return



meteorite_detection_string:
.byte I_, t_, Apos, s_, Space, a_, Space, m_, e_, t_, e_, o_, r_, Space, t_, h_, a_, t_, Space
.byte f_, e_, l_, l_, Space, f_, r_, o_, m_, Space, s_, p_, a_, c_, e_, Dot, Dot, Dot, Termin

deoxys_reaction_string:
.byte 0xFD, 0x3, Space, i_, s_, Space, r_, e_, a_, c_, t_, i_, n_, g_, Space, t_, o_, Space
.byte t_, h_, e_, Space, m_, e_, t_, e_, o_, r_, i_, t_, e_, Dot, Dot, Dot, Termin

reaction_prompt_string:
.byte W_, o_, u_, l_, d_, Space, y_, o_, u_, Space, l_, i_, k_, e_, Space, t_, o_, Space 
.byte b_, r_, i_, n_, g_, JumpLine, t_, h_, e_, Space, D_, e_, o_, x_, y_, s_, Space
.byte i_, n_, Space, y_, o_, u_, r_, Space, p_, a_, r_, t_, y_, Para
.byte c_, l_, o_, s_, e_, r_, Space, t_, o_, Space, t_, h_, e_, Space, m_, e_, t_
.byte e_, o_, r_, i_, t_, e_, Interro, Termin

attack_forme_string:
.byte 0xFD, 0x3, Space, h_, a_, s_, Space, c_, h_, a_, n_, g_, e_, d_, Space, t_, o_, Space, h_ 
.byte a_, v_, e_, JumpLine, s_, u_, p_, e_, r_, i_, o_, r_, Space, s_, t_, a_, t_, s_, Space 
.byte f_, o_, r_, Space, a_, t_, t_, a_, c_, k_, i_, n_, g_, Exclam, Termin

defense_forme_string:
.byte 0xFD, 0x3, Space, h_, a_, s_, Space, c_, h_, a_, n_, g_, e_, d_, Space, t_, o_, Space, h_, a_, v_
.byte e_, JumpLine, s_, u_, p_, e_, r_, i_, o_, r_, Space, s_, t_, a_, t_, s_, Space, w_, h_, e_
.byte n_, Space, d_, e_, f_, e_, n_, d_, i_, n_, g_, Exclam, Termin

speed_forme_string:
.byte 0xFD, 0x3, Space, h_, a_, s_, Space, c_, h_, a_, n_, g_, e_, d_, Space, t_, o_, Space, h_, a_
.byte v_, e_, JumpLine, i_, n_, c_, r_, e_, a_, s_, e_, d_, Space, s_, p_, e_, e_, d_, Exclam, Termin

balance_forme_string:
.byte 0xFD, 0x3, Space, h_, a_, s_, Space, c_, h_, a_, n_, g_, e_, d_, Space, t_, o_, Space, h_, a_
.byte v_, e_, JumpLine, b_, a_, l_, a_, n_, c_, e_, d_, Space, s_, t_, a_, t_, s_, Exclam, Termin

not_valid_deoxys_msg:
.byte T_, h_, e_, Space, p_, o_, k_, Poke_e, m_, o_, n_, Space, d_, o_, e_, s_, Space, n_, o_, t_
.byte Space, r_, e_, a_, c_, t_, JumpLine, t_, o_, Space, t_, h_, e_, Space, m_, e_, t_, e_, o_
.byte r_, Dot, Termin
