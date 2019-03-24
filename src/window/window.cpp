#include "window.h"

SDL_Window *Window::mWindow = NULL;
SDL_GLContext Window::mContext;
SDL_Event Window::event;

int Window::SCREEN_WIDTH = 800;
int Window::SCREEN_HEIGHT = 600;
bool Window::SCREEN_FULLSCREEN = false;

Window::Window()
{

}


Window::~Window()
{
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	
}

void Window::Create()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	if (Window::SCREEN_FULLSCREEN)
	{
		mWindow = SDL_CreateWindow("2DRPG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Window::SCREEN_WIDTH, Window::SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		mWindow = SDL_CreateWindow("2DRPG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Window::SCREEN_WIDTH, Window::SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	}

	mContext = SDL_GL_CreateContext(mWindow);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 4 / 3, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glClearColor(1.f, 0.f, 0.f, 1.f);
}