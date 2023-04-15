#include "File_manager.hpp"


void Load_map_data(const char* file_name) {
	std::ifstream ifs(file_name);
	try {
		if (!ifs) {
			char msg[100];
			sprintf_s(msg, "Unable to find %s", file_name);
			throw msg;
		}
		int g_width, g_height, ID;
		char extra;
		ifs >> g_width >> extra >> g_height;
		Load_array(g_width, g_height);
		for (int i = (Grid_size::GRID_HEIGHT-1); i >=0 ; --i) {
			for (int j = 0; j < Grid_size::GRID_WIDTH; ++j) {
				ifs >> ID;
				(ID == static_cast<int>(TYPE_WALL)) ? Set_cell_value(i, j, ID) : Set_cell_value(i, j, static_cast<int>(TYPE_EMPTY));
			}
		}

	}
	catch (const char* msg) {
		std::cout << "ERROR: " << msg << "\n";
	}

	//Entity::Entity_reserve(count);	// Reserve space in entity vector equal to object count
	//Entity::Entity_readjust_inital();
}