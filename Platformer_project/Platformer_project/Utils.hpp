#pragma once
#include "AEEngine.h"


/*!****************************
 
	Game settings

*******************************/
namespace Game_controls {
	int KEY_MOVE_LEFT   = AEVK_A;
	int KEY_MOVE_RIGHT  = AEVK_D;
	int KEY_JUMP		= AEVK_SPACE;
	int KEY_PAUSE		= AEVK_ESCAPE;
}

namespace Window_size {
	int	WINDOW_WIDTH{ 1600 };
	int WINDOW_HEIGHT{ 900 };
}

/*!****************************

	Enums

*******************************/
enum Object_type {
	TYPE_EMPTY,
	TYPE_WALL
};





/*!****************************

	Helper Class/Functions

*******************************/

struct Actor_transform {
	AEVec2 position;
	AEVec2 size;
	float  rotation;

	Actor_transform(AEVec2 pos = { 0.0f,0.0f }, AEVec2 scale = { 1.0f,1.0f }, float rot = 0.0f) :
					position{ pos }, size{ scale }, rotation{ rot }{}
	//Actor_transform& operator=(Actor_transform& rhs) {
	//	position = rhs.position;
	//	size	 = rhs.size;
	//	rotation = rhs.rotation;
	//	return *this;
	//}

};


