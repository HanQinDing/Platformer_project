#pragma once
#include "Utils.hpp"

class Actor {
	Actor_transform start_transform;
	AEVec2 position;
	AEVec2 a_scale;
	float  rotation;
	AEVec2 velocity;
	bool is_alive;
	bool is_under_gravity;
	AEGfxTexture* texture;

public:
	Actor(AEVec2 pos = {0.0f,0.0f}, AEVec2 size = {1.0f,1.0f}, float rot = 0.0f, AEVec2 vel = { 0.0f,0.0f }, bool alive = true, bool gravity = false, AEGfxTexture* sprite = nullptr);
	
	virtual void Actor_init();
	virtual void Actor_pre_physics();
	virtual void Actor_post_physics();
	virtual void Actor_draw(AEGfxVertexList* mesh);

};