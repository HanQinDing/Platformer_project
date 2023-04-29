// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"
#include "Zone1.hpp"
#include "Utils.hpp"
#include "Scene_manager.hpp"
#include "Stance_manager.hpp"
#include "Graphics_manager.hpp"


// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	int gGameRunning = 1;

	// Initialization of your own variables go here

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, Window_size::WINDOW_WIDTH, Window_size::WINDOW_HEIGHT, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("New RPG");

	// reset the system modules
	AESysReset();
	Add_scene(ZONE1, &Zone1_load, &Zone1_initialize, &Zone1_update, &Zone1_draw, &Zone1_free, &Zone1_unload);
	Load_mesh();
	Load_texture();
	Stance_mgr::Load_all_stance();

	// Game Loop
	Start_scene();
	while (!Get_quit()) {
		Update_scene();
	}

	// free the system
	AESysExit();
}