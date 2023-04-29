#pragma once
#include "Utils.hpp"

bool static_AABB(const AEVec2& min1, const AEVec2& max1, const AEVec2& min2, const AEVec2& max2);
bool AABB_collision_check(const AEVec2& min1, const AEVec2& max1, const AEVec2& vel1, 
						  const AEVec2& min2, const AEVec2& max2, const AEVec2& vel2);