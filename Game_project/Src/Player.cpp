#include "Player.hpp"



Player::Player(std::initializer_list<float> stat_list, AEVec2 vel, bool alive, AEVec2 pos, AEVec2 size, float rot):
			   Actor(pos, size, rot), stats_manager{Stats(stat_list,vel,alive)} {
		object_type = TYPE_PLAYER;
		stance_manager = Stance_mgr::Stance_manager(Stance_mgr::STANCE_TIGER);
		stance_manager.curr_stance->passive_skill.Use_passive(stats_manager);
}


void Player::Actor_init() {

}

void Player::Actor_pre_physics() {
	int y_scalar{ 0 }, x_scalar{ 0 };

	// Set the scalar based on which direction the player clicks
	y_scalar = AEInputCheckCurr(Game_controls::KEY_MOVE_UP) ? 1 : AEInputCheckCurr(Game_controls::KEY_MOVE_DOWN) ? -1 : 0;
	x_scalar = AEInputCheckCurr(Game_controls::KEY_MOVE_LEFT) ? -1 : AEInputCheckCurr(Game_controls::KEY_MOVE_RIGHT) ? 1 : 0;

	
	
	// Set the velocity of the player's velocity vector 
	stats_manager.Set_velocity( { (static_cast<float>(x_scalar) * stats_manager.Get_stats(MOVE_SPD)),(static_cast<float>(y_scalar) * stats_manager.Get_stats(MOVE_SPD)) });


	
	//curr_state = AEInputCheckCurr(Game_controls::KEY_NORMAL_ATTACK) ? PLAYER_ATTACK : (stats.Get_velocity().x != 0 || stats.Get_velocity().y != 0) ? PLAYER_MOVE : PLAYER_IDLE;
	if (AEInputCheckTriggered(Game_controls::KEY_NORMAL_ATTACK)) {
		stance_manager.curr_stance->normal_attack.Use_active(stats_manager);

	}
	else if (AEInputCheckTriggered(Game_controls::KEY_SPELL_1)) {
		stance_manager.curr_stance->spells[0].Use_active(stats_manager);
	}

	else if (AEInputCheckTriggered(Game_controls::KEY_SPELL_2)) {
		stance_manager.curr_stance->spells[1].Use_active(stats_manager);
	}

	else if (AEInputCheckTriggered(Game_controls::KEY_SPELL_3)) {
		stance_manager.curr_stance->spells[2].Use_active(stats_manager);
	}
	else if (AEInputCheckTriggered(AEVK_UP)) {
		Stance_mgr::Stances new_stance = stance_manager.curr_enum;
		stance_manager.Switch_stance(++new_stance, stats_manager);
	}
	else if (AEInputCheckTriggered(AEVK_DOWN)) {
		Stance_mgr::Stances new_stance = stance_manager.curr_enum;
		stance_manager.Switch_stance(--new_stance, stats_manager);
	}

	if (AEInputCheckTriggered(AEVK_L)) {
		stats_manager.Print_data();
	}
	switch (curr_state) {
		case PLAYER_ATTACK: {

		}
	}

	graphic.current_frame += AEFrameRateControllerGetFrameTime() * static_cast<float>(graphic.max_frame);
}
void Player::Actor_post_physics() {

	switch (curr_state) {
		case PLAYER_ATTACK: {

		}
	}
	AEVec2 pos_change = stats_manager.Get_velocity() * AEFrameRateControllerGetFrameTime();
	position += pos_change;
}