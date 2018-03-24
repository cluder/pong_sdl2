#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "GameManager.h"
#include "PlayerPaddle.h"
#include "Ball.h"
#include "AiPaddle.h"

using namespace std;

int GameManager::screenH = 300;
int GameManager::screenW = 500;

static int playerSpeed = 300;
static int aiSpeed = 500;

SDL_Renderer* gRenderer = NULL;
SDL_Texture *gBall;

void print_init_flags(int flags);

// init SDL
SDL_Window* initSDL(SDL_Window* window)
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return NULL;
	}

	// Create window
	window = SDL_CreateWindow("SDL Pong", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, GameManager::screenW, GameManager::screenH, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n",
				SDL_GetError());
	}

	gRenderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED
			| SDL_RENDERER_PRESENTVSYNC
			);
	if (gRenderer == NULL) {
		cerr << "error creating renderer" << endl;
	}

	// Initialize renderer color
	SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, SDL_ALPHA_OPAQUE );

	// init png support
	IMG_Init(IMG_INIT_PNG);

	// init sdl_mixer ogg support
	int flags = MIX_INIT_OGG;
	int initted = Mix_Init(flags);

	if ((initted & flags) != flags) {
		cerr << "error initializing SDL_mixer:" << SDL_GetError() << endl;
		exit (-1);
	}

	int err = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	if (err < 0) {
		cerr << "error initializing SDL_mixer:" << SDL_GetError() << endl;
		exit (-1);
	}

	TTF_Init();

	return window;
}


void mainLoop(GameManager &manager)
{
	// main loop
	bool quit = false;
	Uint32 lastFrame = SDL_GetTicks();
	do
	{
		Uint32 current = SDL_GetTicks();
		Uint32 tpf = current - lastFrame;
		lastFrame = current;

		// check for key presses / exit
		quit = manager.handleInput();

		// update player paddle position
		manager.update(tpf);

		// render scene
		manager.render();

		while (tpf < 10) {
			// limit to max 100 fps
			SDL_Delay(10);
			current = SDL_GetTicks();
			tpf = current - lastFrame;
		}

	} while (!quit);
}

int main(int argc, char **argv)
{
	// The window we'll be rendering to
	SDL_Window* window = NULL;

	// Initialize SDL
	window = initSDL(window);

	// create entities
	PlayerPaddle pp(gRenderer, 20, GameManager::screenH/2, playerSpeed);
	pp.init();
	pp.setDisabled(true);

	// left ai
	AiPaddle aiLeft(gRenderer, 20, GameManager::screenH/2, aiSpeed, true,
			GameManager::screenW/2);
	aiLeft.init();

	AiPaddle aiRight(gRenderer, GameManager::screenW-20, GameManager::screenH/2, aiSpeed, false,
			GameManager::screenW/2);
	aiRight.init();

	Ball ball(gRenderer, GameManager::screenW/2, GameManager::screenH/2);
	ball.init();

	GameManager manager(gRenderer, ball, pp, aiLeft, aiRight);
	manager.init(GameManager::screenW, GameManager::screenH);

	// main loop
	mainLoop(manager);

	// Destroy window
	SDL_DestroyWindow(window);

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	return 0;
}

void print_init_flags(int flags)
{
#define PFLAG(a) if(flags&MIX_INIT_##a) printf(#a " ")
	PFLAG(FLAC);
	PFLAG(MOD);
	PFLAG(MP3);
	PFLAG(OGG);
	if(!flags)
		printf("None");
	printf("\n");
}

