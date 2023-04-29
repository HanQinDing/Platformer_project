#pragma once
#include "Utils.hpp"
#include "Graphics_manager.hpp"
 

class Actor {

public:
	Object_type object_type{ TYPE_EMPTY };

	Actor_transform start_transform;
	AEVec2 position;
	AEVec2 a_scale;
	float  rotation;
	Visual::Graphics graphic;

	Actor(AEVec2 pos = {0.0f,0.0f}, AEVec2 size = {1.0f,1.0f}, float rot = 0.0 );
	
	virtual void Actor_init();
	virtual void Actor_pre_physics();
	virtual void Actor_post_physics();
	virtual void Actor_draw();

};