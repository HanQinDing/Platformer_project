#include "Stance_manager.hpp"

namespace Stance_mgr {

    
    Skill Tiger_passive;
    Skill Tiger_norm_atk;
    Skill Tiger_spell1;
    Skill Tiger_spell2;
    Skill Tiger_spell3;


    Skill Turtle_passive;
    Skill Turtle_norm_atk;
    Skill Turtle_spell1;
    Skill Turtle_spell2;
    Skill Turtle_spell3;

    Skill Phoenix_passive;
    Skill Phoenix_norm_atk;
    Skill Phoenix_spell1;
    Skill Phoenix_spell2;
    Skill Phoenix_spell3;

    
    
    Stance* Stance_arr[STANCE_COUNT];
    
    
}


namespace Stance_mgr {

    Stance::Stance(Skill passive, Skill normal_atk, Skill spell1, Skill spell2, Skill spell3):
                   passive_skill{ passive }, normal_attack{ normal_atk } {
                   spells.push_back(spell1);
                   spells.push_back(spell2);
                   spells.push_back(spell3);
    }

    Stance_manager::Stance_manager(Stances curr_stance_enum) {
        curr_enum   = curr_stance_enum;
        curr_stance = Stance_arr[static_cast<int>(curr_enum)];
    }

    void Stance_manager::Switch_stance(Stances new_stance_enum, Stats& stat) {
        if (new_stance_enum != curr_enum) {
            // Clear all the buffs from the previous stance 
            std::vector<Buff*>::iterator new_end = std::remove_if(stat.Get_buffs_vector().begin(), stat.Get_buffs_vector().end(), Find_stance_buff);
            
            for (std::vector<Buff*>::iterator b = new_end; b != stat.Get_buffs_vector().end(); ++b) {
                int pos = 0;
                for (float val : (*b)->stats) {
                    stat.Apppend_stats(static_cast<Stat>(pos++), -(val));
                }  
            }
            stat.Get_buffs_vector().erase(new_end, stat.Get_buffs_vector().end());


            //Change change to the current stance
            int pos{ 0 };
            curr_enum = new_stance_enum;
            curr_stance = Stance_arr[static_cast<int>(curr_enum)];

            //Trigger the passive skills in the current stance
            curr_stance->passive_skill.Use_passive(stat);
            for (Skill& s : curr_stance->spells) {
                s.Use_passive(stat);
            }
        }
    }

    void Load_all_stance() {
        Tiger_passive.passive_func.push_back(Tiger_buff);
        Tiger_norm_atk.active_func.push_back(Tiger_attack);
        Tiger_spell1.active_func.push_back(Tiger_spell_1);
        Tiger_spell2.active_func.push_back(Tiger_spell_2);
        Tiger_spell3.active_func.push_back(Tiger_spell_3);

        Turtle_passive.passive_func.push_back(Turtle_buff);
        Turtle_norm_atk.active_func.push_back(Turtle_attack);
        Turtle_spell1.active_func.push_back(Turtle_spell_1);
        Turtle_spell2.active_func.push_back(Turtle_spell_2);
        Turtle_spell3.active_func.push_back(Turtle_spell_3);

        Phoenix_passive.passive_func.push_back(Phoenix_buff);
        Phoenix_norm_atk.active_func.push_back(Phoenix_attack);
        Phoenix_spell1.active_func.push_back(Phoenix_spell_1);
        Phoenix_spell2.active_func.push_back(Phoenix_spell_2);
        Phoenix_spell3.active_func.push_back(Phoenix_spell_3);

        Stance* Tiger_stance = new Stance(Tiger_passive, Tiger_norm_atk, Tiger_spell1, Tiger_spell2, Tiger_spell3);
        Stance* Turtle_stance = new Stance(Turtle_passive, Turtle_norm_atk, Turtle_spell1, Turtle_spell2, Turtle_spell3);
        Stance* Phoenix_stance = new Stance(Phoenix_passive, Phoenix_norm_atk, Phoenix_spell1, Phoenix_spell2, Phoenix_spell3);

        Stance_arr[STANCE_TIGER] = Tiger_stance;
        Stance_arr[STANCE_TURTLE] = Turtle_stance;
        Stance_arr[STANCE_PHOENIX] = Phoenix_stance;



    }


    Stances& operator++(Stances& num) {
        num = (static_cast<int>(num) == (static_cast<int>(STANCE_COUNT) - 1)) ? static_cast<Stances>(0) : static_cast<Stances>(static_cast<int>(num) + 1);
        return num;
    }
    Stances& operator--(Stances& num) {
        num = (static_cast<int>(num) == static_cast<int>(0)) ? static_cast<Stances>((static_cast<int>(STANCE_COUNT) - 1)) : static_cast<Stances>(static_cast<int>(num) - 1);
        return num;
    }




}
