#pragma once
#include "Utils.hpp"
#include "Buff.hpp"




class Stats {
    Stats_array stats;
    std::vector<Buff*> buffs;
    bool is_alive;
    AEVec2 velocity;


public:
    Stats();
    Stats(std::initializer_list<float> stat_list, AEVec2 vel = { 0.0f,0.0f }, bool alive = true);

    float Get_stats(Stat stat_enum) const;
    AEVec2 Get_velocity() const; 
    std::vector<Buff*>& Get_buffs_vector();
    bool Is_alive() const;

    void Set_stats(Stat stat_enum, float value);
    void Apppend_stats(Stat stat_enum, float value);
    void Add_buff(Buff* new_buff);
    void Set_velocity(AEVec2 vel);
    void Set_alive(bool alive);
    void Set_all_stats(std::initializer_list<float> stat_list);


    //To delete
    void Print_data();
};

