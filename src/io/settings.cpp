#include "settings.h"
#include "../window/window.h"
#include <fstream>

const char* SETTINGS_FILE = "settings.txt";

Settings::Settings() {

}

Settings::~Settings() {

}

bool Settings::Load() {
	//Load the settings from file if file exists
	std::ifstream load(SETTINGS_FILE, std::ifstream::in);
	if (load.good()) {
		char buffer[256];
		while (!load.eof()) {
			load.getline(buffer, 256);
			sscanf(buffer, "Screen Width = %d", &Window::SCREEN_WIDTH);
			sscanf(buffer, "Screen Height = %d", &Window::SCREEN_HEIGHT);
			//Probably gonna crash. Have no idea why it wants an int pointer
			sscanf(buffer, "Fullscreen = %d", (int*)&Window::SCREEN_FULLSCREEN);
		}
	}
	//Save default values to the file
	else {
		std::ofstream save(SETTINGS_FILE, std::ofstream::out);
		save << "Screen Width = " << Window::SCREEN_WIDTH << std::endl;
		save << "Screen Height = " << Window::SCREEN_HEIGHT << std::endl;
		save << "Fullscreen = " << Window::SCREEN_FULLSCREEN << std::endl;
	}
	return true;
}