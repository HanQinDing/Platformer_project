#include "Scene.hpp"

Scene::Scene() : id{ static_cast<Scene_id>(0) }, Scene_load{ nullptr }, Scene_initialize{ nullptr }, Scene_update{ nullptr }, Scene_draw{ nullptr }, Scene_free{ nullptr }, Scene_unload{ nullptr } {}

Scene::Scene(Scene_id state_id, void (*Load)(), void (*Initialize)(), void (*Update)(), void (*Draw)(), void (*Free)(), void (*Unload)()) :
	id{ state_id }, Scene_load{ Load }, Scene_initialize{ Initialize }, Scene_update{ Update }, Scene_draw{ Draw }, Scene_free{ Free }, Scene_unload{ Unload } {}

Scene_id& operator++(Scene_id& id) {
	id = (id == static_cast<Scene_id>(static_cast<int>(SCENE_AMT) - 1)) ? ZONE1 : static_cast<Scene_id>(static_cast<int>(id) + 1);
	return id;
}