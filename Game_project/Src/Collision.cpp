#include "Collision.hpp"

bool static_AABB(const AEVec2& min1, const AEVec2& max1, const AEVec2& min2, const AEVec2& max2) {
	return !(max1.x < min2.x || max2.x < min1.x || max1.y < min2.y || max2.y < min1.y);
}


bool AABB_collision_check(const AEVec2& min1, const AEVec2& max1, const AEVec2& vel1, const AEVec2& min2, const AEVec2& max2, const AEVec2& vel2)
{
	if (static_AABB(min1, max1, min2, max2)) {	 // return true if static_collision returns true, reduce the need to do the whole dynamic collision
		return true;
	}
	else {
		AEVec2 velocity_rel = { vel2.x - vel1.x, vel2.y - vel1.y };
		if (velocity_rel.x == 0.0f && velocity_rel.y == 0.0f) { return false; }		//Both objects are not colliding, they are stationary

		float T_first{ 0.0f }, T_last{ static_cast<float>(AEFrameRateControllerGetFrameTime()) };

		// Get the T_first and T_last of x-axis using the min and max of the two rect
		if (velocity_rel.x < 0.0f) {												// aabb2 is moving left
			if (min1.x > max2.x) { return false; }						// No intersection, aabb2 is moving away
			T_first = max((max1.x - min2.x) / velocity_rel.x, T_first);
			T_last = min((min1.x - max2.x) / velocity_rel.x, T_last);
		}
		else {
			if (max1.x < min2.x) { return false; }						// No intersection, aabb2 is moving away
			T_first = max((min1.x - max2.x) / velocity_rel.x, T_first);
			T_last = min((max1.x - min2.x) / velocity_rel.x, T_last);

		}


		// Repeat for y-axis
		if (velocity_rel.y < 0.0f) {												// aabb2 is moving left
			if (min1.y > max2.y) { return false; }						// No intersection, aabb2 is moving away
			T_first = max((max1.y - min2.y) / velocity_rel.y, T_first);
			T_last = min((min1.y - max2.y) / velocity_rel.y, T_last);
		}
		else {
			if (max1.y < min2.y) { return false; }						// No intersection, aabb2 is moving away
			T_first = max((min1.y - max2.y) / velocity_rel.y, T_first);
			T_last = min((max1.y - min2.y) / velocity_rel.y, T_last);

		}

		//Case 5 
		if (T_first > T_last) { return false; }	// if T_first > T_last, no collision 

		return true;
	}

}