#pragma once
#include "Utils.hpp"

enum Buff_type {
	BUFF_PERM,
	BUFF_STANCE,
	BUFF_TIME,
	BUFF_COUNT
};

struct Buff {
	Buff_type buff_type;
	Stats_array stats;
	Buff(Buff_type buff_enum,Stats_array buff_stats);
	virtual bool Check_condtion();
};

struct Buff_perm : public Buff {
	Buff_perm(Stats_array buff_stats);
};

struct Buff_stance : public Buff {
	Buff_stance(Stats_array buff_stats);
};

struct Buff_time : public Buff {
	float timer;
	Buff_time(Stats_array buff_stats, float max_time);
	bool Check_condtion() override;
};




bool Find_stance_buff(Buff* buff);

