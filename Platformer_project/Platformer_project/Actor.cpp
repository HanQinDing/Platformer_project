#include "Actor.hpp"
Actor::Actor(AEVec2 pos, AEVec2 scale, float rot, AEVec2 vel = { 0.0f,0.0f }, bool alive, bool gravity, AEGfxTexture* sprite):
	start_transform{ Actor_transform(pos,scale,rot) }, position{ pos }, a_scale{ scale }, rotation{ rot }, velocity{ vel }, 
	is_alive{ alive }, is_under_gravity{gravity}, texture {sprite} {}

void Actor::Actor_init() {
	position = start_transform.position;
	a_scale = start_transform.size;
	rotation = start_transform.rotation;
	is_alive = true;
}
void Actor::Actor_pre_physics() {

}
void Actor::Actor_post_physics() {

}
void Actor::Actor_draw(AEGfxVertexList* mesh) {
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(texture, 0, 0);

	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, a_scale.x, a_scale.y);

	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, rotation);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, position.x, position.y);

	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);

	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

