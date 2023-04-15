#pragma once
#include "Utils.hpp"

namespace Grid_size {
	int	GRID_WIDTH{ 0 };
	int GRID_HEIGHT{ 0 };
}

void Load_array(int width, int height);
void Unload_array();
void Set_cell_value(int i, int j, int val);
int  Get_cell_value(int i, int j);