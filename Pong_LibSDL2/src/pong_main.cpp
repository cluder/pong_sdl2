#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "GameManager.h"
#include "PlayerPaddle.h"
#include "Ball.h"
#include "AiPaddle.h"

using namespace std;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 400;

SDL_Renderer* gRenderer = NULL;

SDL_Texture *gBall;

// ini SDL
SDL_Window* initSDL(SDL_Window* window)
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return NULL;
	}

	// Create window
	window = SDL_CreateWindow("SDL Pong", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n",
				SDL_GetError());
	}

	gRenderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL) {
		cerr << "error creating renderer" << endl;
	}

	// Initialize renderer color
	SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0x0 );

	// init png support
	IMG_Init(IMG_INIT_PNG);

	TTF_Init();

	return window;
}


void mainLoop(GameManager &manager)
{
	// main loop
	bool quit = false;
	do
	{
		// check for key presses / exit
		quit = manager.handleInput();

		// update player paddle position
		manager.update();

		// render scene
		manager.render();

	} while (!quit);
}

int main(int argc, char **argv)
{
	// The window we'll be rendering to
	SDL_Window* window = NULL;

	// Initialize SDL
	window = initSDL(window);

	// create entities
	PlayerPaddle pp(gRenderer, 20, 100);
	pp.init();

	AiPaddle ai(gRenderer, SCREEN_WIDTH-50, 100);
	ai.init();

	Ball ball(gRenderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	ball.init();

	GameManager manager(gRenderer, ball, pp, ai);
	manager.init(SCREEN_WIDTH, SCREEN_HEIGHT);

	// main loop
	mainLoop(manager);

	// Destroy window
	SDL_DestroyWindow(window);

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	return 0;
}
