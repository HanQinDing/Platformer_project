#pragma once
#include "Utils.hpp"
#include "Actor.hpp"
#include "Stats.hpp"
#include "Stance_manager.hpp"

class Player : public Actor {
	float max_health;
	Stats stats_manager;
	Player_state curr_state { PLAYER_IDLE };
	Stance_mgr::Stance_manager stance_manager;
public:
	Player(std::initializer_list<float> stat_list, AEVec2 vel = { 0.0f,0.0f }, bool alive = true, AEVec2 pos = { 0.0f,0.0f }, AEVec2 size = { 1.0f,1.0f }, float rot = 0.0f);

	void Actor_init() override;
	void Actor_pre_physics() override;
	void Actor_post_physics() override;

	//void Player_movement();
	//void Draw_highlight(AEGfxVertexList* mesh);
	//bool Is_item_in_wall();

	//void Interact() override;	// Used to drop held_item
	//void Interact(Entity* entity) override;

	//static void Player_load(std::vector<Player*>& p_arr);
	//static void Player_clear();
	//static Player* Get_current_player();
	//static void Player_refresh();	// Reset has_interacted flag
};

