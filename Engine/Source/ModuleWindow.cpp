#include "Globals.h"
#include "SDL.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits

#ifdef _DEBUG
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif // _DEBUG

		//Create window
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;
		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL;

		if (FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		if (RESIZEABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		mWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight, flags);

		if(mWindow == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			
			mScreenSurface = SDL_GetWindowSurface(mWindow);
		}
	}
	
	int windowPositionX, windowPositionY;
	SDL_GetWindowPosition(mWindow, &windowPositionX, &windowPositionY);
	mGameWindowsSize = float2(mWidth, mHeight);
	mGameWindowsPosition = float2(windowPositionX, windowPositionY);
	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(mWindow != NULL)
	{
		SDL_DestroyWindow(mWindow);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::SetMousePositionInWindow(float2 position)
{
	SDL_WarpMouseInWindow(mWindow, position.x, position.y);
}

void ModuleWindow::WindowResized(unsigned width, unsigned height)
{
	this->mWidth = width;
	this->mHeight = height;
	mGameWindowsSize = float2(mWidth, mHeight);
}

void ModuleWindow::WindowMoved(unsigned x, unsigned y)
{
	mGameWindowsPosition.x = x;
	mGameWindowsPosition.y = y;
}

void ModuleWindow::WindowFullscreen(bool value)
{
	if (value)
	{
		SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else
	{
		SDL_SetWindowFullscreen(mWindow, 0);
	}

	int w, h;
	SDL_GetWindowSize(mWindow, &w, &h);
	WindowResized(w, h);
}

bool ModuleWindow::IsWindowFullscreen()
{
	Uint32 windowFlags = SDL_GetWindowFlags(mWindow);
	return (windowFlags & SDL_WINDOW_FULLSCREEN_DESKTOP) == SDL_WINDOW_FULLSCREEN_DESKTOP;
}

