#include "Buff.hpp"


/*!****************************

		Base Buff 

*******************************/
Buff::Buff(Buff_type buff_enum, Stats_array buff_stats): buff_type{buff_enum}, stats{buff_stats}{}
bool Buff::Check_condtion() { return false; }


/*!****************************

		Permanent buff

*******************************/
Buff_perm::Buff_perm(Stats_array buff_stats):Buff(BUFF_PERM,buff_stats){}


/*!****************************

		Stance's buff

*******************************/
Buff_stance::Buff_stance(Stats_array buff_stats) :Buff(BUFF_STANCE, buff_stats) {}

bool Find_stance_buff(Buff* buff) {
	return (buff->buff_type == BUFF_STANCE);
}

/*!****************************

		Timer buff

*******************************/
Buff_time::Buff_time(Stats_array buff_stats, float max_time) :Buff(BUFF_PERM, buff_stats), timer{max_time}{}

bool Buff_time::Check_condtion() {
	timer -= AEFrameRateControllerGetFrameTime();
	return (timer <= 0.0f);
}
