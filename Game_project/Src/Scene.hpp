#pragma once
enum Scene_id {
	ZONE1,
	SCENE_AMT


};
Scene_id& operator++(Scene_id& id);

class Scene {
public:
	Scene_id id;
	void (*Scene_load)();
	void (*Scene_initialize)();
	void (*Scene_update)();
	void (*Scene_draw)();
	void (*Scene_free)();
	void (*Scene_unload)();
	Scene();
	Scene(Scene_id state_id, void (*Load)(), void (*Initialize)(), void (*Update)(), void (*Draw)(), void (*Free)(), void (*Unload)());

};

