#include "Zone1.hpp"
#include <iostream>
void Zone1_load() {
	//Load_map_data("../Assets/Scenes/Zone1.txt");
	std::cout << "Zone 1 load\n";
	std::initializer_list<float> stat_list = { 10.0f,10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f };
	Player* p1 = new Player(stat_list);
	Add_object(p1);
}

void Zone1_initialize() {

}

void Zone1_update() {
	Update_all_pre_phy();
	Update_all_post_phy();
}

void Zone1_draw() {
	Draw_all();
}

void Zone1_free() {

}

void Zone1_unload() {

}