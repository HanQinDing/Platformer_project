#include "Utils.hpp"

//Draw_layer& operator++(Draw_layer& layer) {
//	layer = (layer == static_cast<Draw_layer>(static_cast<int>(LAYER_COUNT) - 1)) ? LAYER_1 : static_cast<Draw_layer>(static_cast<int>(layer) + 1);
//	return layer;
//}


/*!****************************

	Helper Class/Functions

*******************************/

AEVec2 operator+(const AEVec2& lhs, const AEVec2& rhs) {
	return { lhs.x + rhs.x, lhs.y + rhs.y };
}

// Subtraction
AEVec2 operator-(const AEVec2& lhs, const AEVec2& rhs) {
	return { lhs.x - rhs.x, lhs.y - rhs.y };
}

// Multiplication with scalar
AEVec2 operator*(const AEVec2& lhs, float scalar) {
	return AEVec2{ lhs.x * scalar, lhs.y * scalar };
}

// Multiplication with scalar (reverse order)
AEVec2 operator*(float scalar, const AEVec2& rhs) {
	return AEVec2{ rhs.x * scalar, rhs.y * scalar };
}

// Addition with assignment
AEVec2& operator+=(AEVec2& lhs, const AEVec2& rhs) {
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

// Subtraction with assignment
AEVec2& operator-=(AEVec2& lhs, const AEVec2& rhs) {
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}