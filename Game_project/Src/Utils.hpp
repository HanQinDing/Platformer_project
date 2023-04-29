#pragma once
#include "AEEngine.h"
#include <vector>
#include <array>
#include <initializer_list>
#include <fstream>
#include <iostream>
#include <algorithm>



#ifdef _MSC_VER
#define MY_FUNCTION_MACRO __FUNCTION__ // or __FUNCSIG__
#else
#define MY_FUNCTION_MACRO __PRETTY_FUNCTION__
#endif


/*!****************************
 
	Game settings

*******************************/
namespace Game_controls {
	static int KEY_MOVE_UP = AEVK_W;
	static int KEY_MOVE_DOWN  = AEVK_S;
	static int KEY_MOVE_LEFT  = AEVK_A;
	static int KEY_MOVE_RIGHT = AEVK_D;
	static int KEY_NORMAL_ATTACK = AEVK_U;
	static int KEY_SPELL_1 = AEVK_I;
	static int KEY_SPELL_2 = AEVK_O;
	static int KEY_SPELL_3 = AEVK_P;
	static int KEY_PAUSE	=	AEVK_ESCAPE;
}

namespace Window_size {
	static int	WINDOW_WIDTH{ 1600 };
	static int  WINDOW_HEIGHT{ 900 };
}

/*!****************************

	Enums

*******************************/
enum Object_type {
	TYPE_EMPTY,
	TYPE_WALL,
	TYPE_PLAYER,
	OBJECT_NUM
};



enum Stat {
	HEALTH,
	MANA,
	CURR_HEALTH,
	CURR_MANA,
	PHY_POWER,
	MAGIC_POWER,
	PHY_DEF,
	MAGIC_DEF,
	MOVE_SPD,
	ATK_SPD,
	STATS_NUM
};



enum Player_state {
	PLAYER_IDLE,
	PLAYER_MOVE,
	PLAYER_ATTACK,
	PLAYER_STATE_COUNT
};



/*!****************************

	Using

*******************************/
using Stats_array = std::array<float, static_cast<int>(STATS_NUM)>;



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

// Addition
AEVec2 operator+(const AEVec2& lhs, const AEVec2& rhs);

// Subtraction
AEVec2 operator-(const AEVec2& lhs, const AEVec2& rhs);

// Multiplication with scalar
AEVec2 operator*(const AEVec2& lhs, float scalar);

// Multiplication with scalar (reverse order)
AEVec2 operator*(float scalar, const AEVec2& rhs);

// Addition with assignment
AEVec2& operator+=(AEVec2& lhs, const AEVec2& rhs);

// Subtraction with assignment
AEVec2& operator-=(AEVec2& lhs, const AEVec2& rhs);



