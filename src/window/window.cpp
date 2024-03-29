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
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	
}

void Window::Create()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	if (Window::SCREEN_FULLSCREEN)
	{
		mWindow = SDL_CreateWindow("iNOBEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Window::SCREEN_WIDTH, Window::SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		mWindow = SDL_CreateWindow("iNOBEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Window::SCREEN_WIDTH, Window::SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	}
    if (mWindow == NULL) {
        SDL_Log("Could not create window: %s\n", SDL_GetError());
    }
	mContext = SDL_GL_CreateContext(mWindow);
	SDL_GL_SetSwapInterval(0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ((float) SCREEN_WIDTH) / SCREEN_HEIGHT, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(true);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	glEnable(GL_TEXTURE_2D);
	glClearColor(1.f, 0.f, 0.f, 1.f);
}