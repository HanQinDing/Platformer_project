#pragma once
#include "Utils.hpp"
#include "Stats.hpp"
#include "Buff.hpp"

using SFR = void (*)(Stats&);

struct Skill {

    std::vector<SFR> passive_func;
    std::vector<SFR> active_func;

    void Use_passive(Stats& stat);
    void Use_active(Stats& stat);

};

void Tiger_buff(Stats& stat);
void Tiger_attack(Stats& stat);
void Tiger_spell_1(Stats& stat);
void Tiger_spell_2(Stats& stat);
void Tiger_spell_3(Stats& stat);


void Turtle_buff(Stats& stat);
void Turtle_attack(Stats& stat);
void Turtle_spell_1(Stats& stat);
void Turtle_spell_2(Stats& stat);
void Turtle_spell_3(Stats& stat);

void Phoenix_buff(Stats& stat);
void Phoenix_attack(Stats& stat);
void Phoenix_spell_1(Stats& stat);
void Phoenix_spell_2(Stats& stat);
void Phoenix_spell_3(Stats& stat);
