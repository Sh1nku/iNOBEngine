#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>

class Window
{
public:
	Window();
	~Window();

	static SDL_Window *mWindow;
	static SDL_GLContext mContext;
	static SDL_Event event;
	void Create();

	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	static bool SCREEN_FULLSCREEN;

private:
};

