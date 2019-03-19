#pragma once

extern const char* SETTINGS_FILE;

class Window;

class Settings {
public:
	Settings();
	~Settings();
	static bool Load();
};