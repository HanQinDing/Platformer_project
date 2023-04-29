#pragma once
#include "Utils.hpp"
#include "Stance_manager.hpp"


namespace Visual {
	enum Frames {
		ONE_FRAME = 1,
		TWO_FRAMES,
		THREE_FRAMES,
		FOUR_FRAMES,
		FIVE_FRAMES,
		SIX_FRAMES,
		SEVEN_FRAMES,
		EIGHT_FRAMES,
		NUM_FRAMES
	};

	enum Direction {
		UP,
		LEFT,
		DOWN,
		RIGHT,
		DIRECTION_COUNT
	};

	struct Graphics {
		Direction   direction;
		Frames	    max_frame;
		float       current_frame;

		AEGfxVertexList* Get_mesh();
		void Set_texture(Object_type obj_type, int state = 0, int stance = 0);
		Graphics(Direction direction_enum = DOWN,Frames frame_enum = ONE_FRAME, float curr_frame = 0.0f);
	};
}



void Load_mesh();
void Load_texture();
