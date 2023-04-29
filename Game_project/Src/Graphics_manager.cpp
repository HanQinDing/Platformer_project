#include "Graphics_manager.hpp"

namespace Visual {
	AEGfxVertexList* meshes[static_cast<int>(NUM_FRAMES) - 1];	// Contains all meshes
	AEGfxTexture* player_texture[Stance_mgr::STANCE_COUNT][PLAYER_STATE_COUNT][DIRECTION_COUNT];
}



namespace Visual {

	Graphics::Graphics(Direction direction_enum, Frames frame_enum, float curr_frame) :
					   direction{direction_enum}, max_frame{frame_enum}, current_frame{curr_frame}{}

	AEGfxVertexList* Graphics::Get_mesh() {
		return Visual::meshes[static_cast<int>(max_frame) - 1];
	}

	void Graphics::Set_texture(Object_type obj_type, int state, int stance){
		switch (obj_type) {
			case TYPE_PLAYER: {
				AEGfxTextureSet(player_texture[stance][state][direction], static_cast<float>(static_cast<int>(current_frame) % max_frame) / static_cast<float>(max_frame), 0);
			}
		}
	}

}



void Load_mesh() {
	for (int i = 1; i < static_cast<int>(Visual::NUM_FRAMES); ++i) {
		float mesh_size = 1.0f / (static_cast<float>(i));
		std::cout << mesh_size << "\n";
		AEGfxMeshStart();
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
			0.5f, -0.5f, 0xFFFFFFFF, mesh_size, 1.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
		AEGfxTriAdd(
			0.5f, -0.5f, 0xFFFFFFFF, mesh_size, 1.0f,
			0.5f, 0.5f, 0xFFFFFFFF, mesh_size, 0.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
		Visual::meshes[(i-1)] = AEGfxMeshEnd();
	}
}

void Load_texture() {
	//Visual::textures[static_cast<int>(TYPE_PLAYER)].push_back(AEGfxTextureLoad("Assets/Textures/player1_walking_right.png"));
}



