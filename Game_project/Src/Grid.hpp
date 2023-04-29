#pragma once
#include "Utils.hpp"

namespace Grid_size {
	static int	GRID_WIDTH;
	static int  GRID_HEIGHT{ 0 };
}

void Load_array(int width, int height);
void Unload_array();
void Set_cell_value(int i, int j, int val);
int  Get_cell_value(int i, int j);