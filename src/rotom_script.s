.text
.thumb
.align 2

.include "defines/asm_defines.s"
.include "defines/xse_commands.s"

rotom_main:
	lock
	msgbox appliance_detection_string MSG_KEEPOPEN
	closeonkeypress
	callasm find_rotom+1
	compare 0x800D 0x0
	if 0x1 _goto finish_rotom_menu
	compare 0x800D 0x2
	if 0x1 _goto choose_candidate_rotom

investigation_prompt:
	bufferpartypokemon 0x1 0x8004
	msgbox rotom_investigation_string MSG_KEEPOPEN
	closeonkeypress
	msgbox investigation_prompt_string MSG_YESNO
	compare 0x800D 0x0
	if 0x1 _goto finish_rotom_menu
	preparemsg appliance_choice_string
	waitmsg
	multichoice 0xF 0x0 0xD 0x0
	compare 0x800D 0x6
	if 0x1 _goto finish_rotom_menu
	callasm rotom_change+1
	compare 0x800D 0x0
	if 0x1 _goto rotom_already_in_motor
	compare 0x800D 0x4
	if 0x1 _goto rotom_already_out_of_motor
	compare 0x800D 0x3
	if 0x1 _goto delete_move_after_revert
	copyvar 0x8007 0x800D
	msgbox entered_motor_string MSG_KEEPOPEN
	closeonkeypress
	compare 0x8007 0x2
	if 0x1 _goto rotom_learn_special_move
	special 0xDD
	bufferattack 0x2 0x8003
	msgbox forgot_special_move_string MSG_KEEPOPEN
	closeonkeypress

rotom_learn_special_move:
	callasm rotom_determine_special_move+1
	compare 0x8006 0x0
	if 0x1 _goto finish_rotom_menu
	special 0xDF
	compare 0x800D 0x4
	if 0x1 _goto rotom_move_delete_prompt

learned_special_move:
	callasm rotom_learn_special_move_func+1
	bufferattack 0x2 0x8006
	fanfare 0x101
	msgbox learn_special_move_string MSG_KEEPOPEN
	waitfanfare
	closeonkeypress

finish_rotom_menu:
	release
	end

rotom_move_delete_prompt:
	bufferattack 0x2 0x8006
	msgbox try_to_learn_move_string MSG_YESNO
	compare 0x800D 0x0
	if 0x1 _goto revert_for_not_learning_new_move
	special 0xDC
	waitstate
	compare 0x8005 0x3
	if 0x2 _goto finish_rotom_menu
	msgbox pff_move_string MSG_KEEPOPEN
	closeonkeypress
	callasm store_move_to_var8003_from_var8005_in_slot_var8004+1
	bufferattack 0x2 0x8003
	special 0xDD
	bufferpartypokemon 0x1 0x8004
	msgbox forgot_special_move_string MSG_KEEPOPEN
	closeonkeypress
	callasm rotom_determine_special_move+1
	goto learned_special_move

rotom_already_in_motor:
	msgbox already_appliance_string MSG_KEEPOPEN
	closeonkeypress
	goto finish_rotom_menu

rotom_already_out_of_motor:
	msgbox not_in_motor_string MSG_KEEPOPEN
	closeonkeypress
	goto finish_rotom_menu

delete_move_after_revert:
	bufferattack 0x2 0x8003
	special 0xDD
	setvar 0x8006 0x0
	callasm rotom_learn_special_move_func+1
	msgbox left_motor_string MSG_KEEPOPEN
	closeonkeypress
	msgbox forgot_special_move_string MSG_KEEPOPEN
	closeonkeypress
	callasm rotom_determine_special_move+1
	compare 0x8006 0x0
	if 0x1 _goto finish_rotom_menu
	callasm rotom_learn_special_move_func+1
	goto finish_rotom_menu

revert_for_not_learning_new_move:
	setvar 0x800D 0x5
	callasm rotom_change+1
	msgbox left_motor_string MSG_KEEPOPEN
	closeonkeypress
	goto finish_rotom_menu

choose_candidate_rotom:
	special 0xA2
	waitstate
	callasm check_chosen_rotom+1
	compare 0x800D 0x1
	if 0x1 _goto investigation_prompt
	msgbox not_valid_rotom_msg MSG_KEEPOPEN
	closeonkeypress
	goto finish_rotom_menu

appliance_detection_string:
.byte I_, t_, Apos , s_, Space, f_, u_, l_, l_, Space, o_, f_, Space, c_, a_, r_, d_, b_, o_, a_, d_, Space, b_, o_, x_, e_, s_
.byte w_, i_, t_, h_, JumpLine, e_, l_, e_, c_, t_, r_, i_, c_, a_, l_, Space, a_, p_, p_, l_, i_, a_, n_, c_, e_, s_, Space
.byte i_, n_, Space, t_, h_, e_, m_, Dot, Termin

rotom_investigation_string:
.byte O_, h_, Interro, Space, 0xFD, 0x3, Space,  w_, o_, u_, l_, d_, Space, l_, i_, k_, e_, Space, t_, o_, JumpLine, i_, n_, v_, e_, s_, t_, i_, g_, a_, t_, e_, Space
.byte t_, h_, e_, Space, m_, o_, t_, o_, r_, s_, Space, o_, f_, Para, t_, h_, e_, Space,  e_, l_, e_, c_, t_, r_, i_, c_, a_, l_, Space
.byte a_, p_, p_, l_, i_, a_, n_, c_, e_, s_, Dot, Termin

investigation_prompt_string:
.byte I_, s_, Space, t_, h_, a_, t_, Space, O_, K_, Interro, Termin

appliance_choice_string:
.byte W_, h_, i_, c_, h_, Space, a_, p_, p_, l_, i_, a_, n_, c_, e_, Apos, s_, Space, m_, o_, t_, o_, r_, s_, Space, w_, i_, l_, l_, Space, y_, o_, u_
.byte a_, l_, l_, o_, w_, Space, 0xFD, 0x3, Space, t_, o_, Space, e_, n_, t_, e_, r_, Interro, Termin

entered_motor_string:
.byte 0xFD, 0x3, Space, e_, n_, t_, e_, r_, e_, d_, Space, t_, h_, e_, Space, m_, o_, t_, o_, r_, s_, Dot, Termin

left_motor_string:
.byte 0xFD, 0x3, Space, e_, m_, e_, r_, g_, e_, d_, Space, f_, r_, o_, m_, Space, t_, h_, e_, Space, m_, o_, t_, o_, r_, s_, Dot, Termin 

forgot_special_move_string:
.byte 0xFD, 0x3, Space, f_, o_, r_, g_, o_, t_, Space, 0xFD, 0x4, Exclam, Termin

learn_special_move_string:
.byte 0xFD, 0x3, Space, l_, e_, a_, r_, n_, e_, d_, Space, 0xFD, 0x4, Exclam, Termin

try_to_learn_move_string:
.byte 0xFD, 0x3, Space, i_, s_, Space, t_, r_, y_, i_, n_, g_, Space, t_, o_, JumpLine, l_, e_, a_, r_, n_, 0xFD, 0x4, Dot
.byte Para, B_, u_, t_, Comma, Space, i_, t_, Space, c_, a_, n_, Apos, t_, Space, l_, e_, a_, r_, n_, JumpLine, m_, o_, r_, e_
.byte Space, t_, h_, a_, n_, Space, f_, o_, u_, r_, Space, m_, o_, v_, e_, s_, Dot, Para, D_, e_, l_, e_, t_, e_, Space, a_, Space
.byte m_, o_, v_, e_, Space, t_, o_, Space, m_, a_, k_, e_, JumpLine, r_, o_, o_, m_, Space, f_, o_, r_, 0xFD, 0x4, Interro, Termin

pff_move_string:
.byte 0xFC, 0x8, 0x20, 0xA2, 0xB8, 0x0, 0xFC, 0x8, 0xF, 0xA3, 0xB8, 0x0, 0xD5, 0xE2, 0xD8, 0xFC, 0x8, 0xF, 0xB0, 0x0, 0xFC, 0x8
.byte 0xF, 0xB0, 0x0, 0xFC, 0x8, 0xF, 0xB0, 0x0, 0xFC, 0x8, 0xF, 0xFC, 0x10, 0x31, 0x0, 0xCA, 0xE3, 0xE3, 0xDA, 0xAB, Termin

already_appliance_string:
.byte T_, h_, i_, s_, Space, R_, o_, t_, o_, m_, Space, h_, a_, s_, Space, a_, l_, r_, e_, a_, d_, y_, Space, e_, n_, t_, e_, r_, e_, d_, JumpLine
.byte t_, h_, a_, t_, Space, a_, p_, p_, l_, i_, a_, n_, c_, e_, Space, m_, o_, t_, o_, r_, Dot, Termin

not_in_motor_string:
.byte 0xFD, 0x3, Space, h_, a_, s_, n_, Apos, t_, Space, e_, n_, t_, e_, r_, e_, d_, Space, a_, Space, m_, o_, t_, o_, r_, Dot, Termin

not_valid_rotom_msg:
.byte N_, o_, t_, Space, a_, Space, v_, a_, l_, i_, d_, Space, r_, o_, t_, o_, m_, Dot, Termin
