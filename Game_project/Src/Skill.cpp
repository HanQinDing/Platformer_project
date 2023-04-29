#pragma once
#include "Skill.hpp"

void Skill::Use_passive(Stats& stat) {
	for (SFR func : passive_func) {
		func(stat);
	}
}
void Skill::Use_active(Stats& stat) {
	for (SFR func : active_func) {
		func(stat);
	}
}

void Tiger_buff(Stats& stat) {
	Stats_array stat_buffs = { 0.0f };
	stat_buffs[PHY_POWER] = 20.0f;
	stat_buffs[MOVE_SPD]  = 20.0f;

	stat.Apppend_stats(PHY_POWER, stat_buffs[PHY_POWER]);
	stat.Apppend_stats(MOVE_SPD,  stat_buffs[MOVE_SPD]);

	Buff_stance* new_buff = new Buff_stance(stat_buffs);
	stat.Add_buff(dynamic_cast<Buff*>(new_buff));

	std::cout << MY_FUNCTION_MACRO << "\n";
}
void Tiger_attack(Stats& stat) {
	std::cout << MY_FUNCTION_MACRO << "\n";
}
void Tiger_spell_1(Stats& stat) {
	std::cout <<MY_FUNCTION_MACRO << "\n";
}
void Tiger_spell_2(Stats& stat) {
	std::cout <<MY_FUNCTION_MACRO << "\n";
}
void Tiger_spell_3(Stats& stat) {
	std::cout <<MY_FUNCTION_MACRO << "\n";
}


void Turtle_buff(Stats& stat) {
	Stats_array stat_buffs = { 0.0f };
	stat_buffs[PHY_DEF] = 20.0f;
	stat_buffs[MAGIC_DEF] = 20.0f;

	stat.Apppend_stats(PHY_DEF, stat_buffs[PHY_DEF]);
	stat.Apppend_stats(MAGIC_DEF, stat_buffs[MAGIC_DEF]);

	Buff_stance* new_buff = new Buff_stance(stat_buffs);
	stat.Add_buff(dynamic_cast<Buff*>(new_buff));
	std::cout <<MY_FUNCTION_MACRO << "\n";
}
void Turtle_attack(Stats& stat) {
	std::cout <<MY_FUNCTION_MACRO << "\n";
}
void Turtle_spell_1(Stats& stat) {
	std::cout <<MY_FUNCTION_MACRO << "\n";
}
void Turtle_spell_2(Stats& stat) {
	std::cout <<MY_FUNCTION_MACRO << "\n";
}
void Turtle_spell_3(Stats& stat) {
	std::cout <<MY_FUNCTION_MACRO << "\n";
}


void Phoenix_buff(Stats& stat) {
	Stats_array stat_buffs = { 0.0f };
	stat_buffs[MAGIC_POWER] = 20.0f;

	stat.Apppend_stats(MAGIC_POWER, stat_buffs[MAGIC_POWER]);

	Buff_stance* new_buff = new Buff_stance(stat_buffs);
	stat.Add_buff(dynamic_cast<Buff*>(new_buff));
	std::cout <<MY_FUNCTION_MACRO << "\n";
}
void Phoenix_attack(Stats& stat) {
	std::cout <<MY_FUNCTION_MACRO << "\n";
}
void Phoenix_spell_1(Stats& stat) {
	std::cout <<MY_FUNCTION_MACRO << "\n";
}
void Phoenix_spell_2(Stats& stat) {
	std::cout <<MY_FUNCTION_MACRO << "\n";
}
void Phoenix_spell_3(Stats& stat) {
	std::cout <<MY_FUNCTION_MACRO << "\n";
}

