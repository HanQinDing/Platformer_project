#pragma once
#include "Object_manager.hpp"
#include <vector>
#include <iostream>

namespace Objects {
	Obejct_manager obj_mgr;

}

void Update_all_pre_phy() {
	for (Player* p : Objects::obj_mgr.player_arr) {
		p->Actor_pre_physics();
	}
}

void Update_all_post_phy() {
	for (Player* p : Objects::obj_mgr.player_arr) {
		p->Actor_post_physics();
	}
}

void Draw_all() {
	for (Player* p : Objects::obj_mgr.player_arr) {
		p->Actor_draw();
	}
}

void Add_object(Player* p) {
	Objects::obj_mgr.player_arr.push_back(p);
}

std::vector<Player*> Get_player_arr() {
	return Objects::obj_mgr.player_arr;
}



