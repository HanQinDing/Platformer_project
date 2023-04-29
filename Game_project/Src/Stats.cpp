#include "Stats.hpp"

Stats::Stats() {
    stats.fill(0.0f);
    velocity = { 0.0f,0.0f };
    is_alive = true;
}

Stats::Stats(std::initializer_list<float> stat_list, AEVec2 vel, bool alive) {
    int pos = 0;
    for (float value: stat_list) {
        if (pos >= STATS_NUM) {break;}
        stats[pos] = value;
        ++pos;
    }
    velocity = vel;
    is_alive = alive;
}

float Stats::Get_stats(Stat stat_enum) const {
    return stats[static_cast<int>(stat_enum)];
}

AEVec2 Stats::Get_velocity() const {
    return velocity;
}

std::vector<Buff*>& Stats::Get_buffs_vector() {
    return buffs;
}

bool Stats::Is_alive() const {
    return is_alive;
}

void Stats::Set_stats(Stat stat_enum, float value) {
    stats[static_cast<int>(stat_enum)] = value;
}

void Stats::Apppend_stats(Stat stat_enum, float value) {
    stats[static_cast<int>(stat_enum)] += value;
}

void Stats::Add_buff(Buff* new_buff) {
    buffs.push_back(new_buff);
}

void Stats::Set_velocity(AEVec2 vel) {
    velocity = vel;
}
void Stats::Set_alive(bool alive) {
    is_alive = alive;
}

void Stats::Set_all_stats(std::initializer_list<float> stat_list) {
    int pos = 0;
    for (float value : stat_list) {
        if (pos >= STATS_NUM) { break; }
        stats[pos] = value;
        ++pos;
    }
}

void Stats::Print_data() {
    for (float f : stats) {
        std::cout << f << "\n";
    }
    std::cout << "\n";
}