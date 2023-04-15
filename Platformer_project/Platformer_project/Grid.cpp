#include "Grid.hpp"

static int** BINARY_COLLISION_ARRAY;

/*!****************************
	Allocate memory for array
*******************************/
void Load_array(int width, int height) {
	Grid_size::GRID_WIDTH = width;
	Grid_size::GRID_HEIGHT = height;

	BINARY_COLLISION_ARRAY = new int* [Grid_size::GRID_HEIGHT];
	for (int i = 0; i < Grid_size::GRID_HEIGHT; ++i) {
		BINARY_COLLISION_ARRAY[i] = new int[Grid_size::GRID_WIDTH];
	}

}



/*!****************************
	free memory in array
*******************************/
void Unload_array() {
	for (int i = 0; i < Grid_size::GRID_WIDTH; ++i) {
		delete[] BINARY_COLLISION_ARRAY[i];
	}
	delete[] BINARY_COLLISION_ARRAY;
}

/*!****************************
	Set value in a cell
*******************************/
void Set_cell_value(int i, int j, int val) {
	BINARY_COLLISION_ARRAY[i][j] = val;
}

/*!****************************
	Return value in a cell
*******************************/
int  Get_cell_value(int i, int j) {
	return (BINARY_COLLISION_ARRAY[i][j]);
}