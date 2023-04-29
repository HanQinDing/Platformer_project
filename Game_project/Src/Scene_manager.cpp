#include "Scene_manager.hpp"

namespace Gsm {
	Scene_manager gsm = Scene_manager();
}


Scene_manager::Scene_manager() {}

void Add_scene(Scene_id id, void (*load)(), void (*initialize)(), void (*update)(), void (*draw)(), void (*free)(), void (*unload)()) {
	Gsm::gsm.gs_array[id] = { Scene(id, load,initialize, update, draw, free, unload) };
}


void Start_scene() {
	if (!Gsm::gsm.restart) {	//New scene/Level
		Gsm::gsm.gs_array[Gsm::gsm.current_scene].Scene_load();
	}
	Gsm::gsm.gs_array[Gsm::gsm.current_scene].Scene_initialize();
}

void Update_scene() {
	AESysFrameStart();
	AEInputUpdate();
	Gsm::gsm.gs_array[Gsm::gsm.current_scene].Scene_update();
	Gsm::gsm.gs_array[Gsm::gsm.current_scene].Scene_draw();
	AESysFrameEnd();
}


void End_scene(Scene_id id) {
	Gsm::gsm.gs_array[(Gsm::gsm.current_scene)].Scene_free();
	Gsm::gsm.restart = (id == Gsm::gsm.current_scene) ? true : false;
	if (!(Gsm::gsm.restart)) {  //Not Restart, new scene
		Gsm::gsm.gs_array[(Gsm::gsm.current_scene)].Scene_unload();
		Gsm::gsm.current_scene = id;
	}
	Start_scene();

}

bool Get_quit() {
	return Gsm::gsm.quit;
}

void Restart_scene() {
	End_scene(Gsm::gsm.current_scene);
}

void Next_scene() {
	Scene_id next_scene = Gsm::gsm.current_scene;
	End_scene(++next_scene);
}

void Next_scene(Scene_id next_scene) {
	++next_scene;
	End_scene(next_scene);
}

void Quit_game() {
	Gsm::gsm.quit = true;
}

Scene_id Get_current_scene() {
	return Gsm::gsm.current_scene;
}