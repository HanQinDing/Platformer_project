#pragma once
#include "Skill.hpp"
#include "Stats.hpp"
#include "Utils.hpp"

namespace Stance_mgr {

     enum Stances {
        ///STANCE_NORMAL,
        STANCE_TIGER,
        STANCE_TURTLE,
        STANCE_PHOENIX,
        STANCE_COUNT
    };

    struct Stance {
        Skill passive_skill;
        Skill normal_attack;
        std::vector<Skill> spells;
        Stance(Skill passive, Skill normal_atk, Skill spell1, Skill spell2, Skill spell3);

    };

    struct Stance_manager {
        Stances curr_enum;
        Stance* curr_stance;

        Stance_manager(Stances curr_stance_enum = STANCE_TIGER);
        void Switch_stance(Stances new_stance, Stats& stat);
    };

    Stances& operator++(Stances& num);
    Stances& operator--(Stances& num);
    void Load_all_stance();


}


