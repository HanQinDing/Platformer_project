#pragma once
#include "Scene.hpp"
#include "Utils.hpp"

class Scene_manager {
public:
	Scene_id current_scene = ZONE1;
	bool restart = false;
	bool quit = false;
	bool end = false;
	Scene gs_array[SCENE_AMT];
	Scene_manager();

	// Functions to manage the scenes
};

void Add_scene(Scene_id id, void (*load)(), void (*initialize)(), void (*update)(), void (*draw)(), void (*free)(), void (*unload)());
void Start_scene();
void Update_scene();
void End_scene(Scene_id id);
void Restart_scene();
void Next_scene();
void Next_scene(Scene_id next_scene);
bool Get_quit();
void Quit_game();
Scene_id Get_current_scene();