#pragma once
#include "Player.hpp"
#include "Utils.hpp"

struct Obejct_manager {
	std::vector<Player*> player_arr;
};


//loop through all game objects
void Update_all_pre_phy();
void Update_all_post_phy();
void Draw_all();

//Add game objects into the repsective vectors
void Add_object(Player* p);

//retrieve respective game object vectors
std::vector<Player*> Get_player_arr();