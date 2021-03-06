
#define SDL_MAIN_HANDLED

#include <iostream>
#include <ctime>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include "GameManager.h"
#include "PlayerPaddle.h"
#include "Ball.h"
#include "AiPaddle.h"

using namespace std;

int GameManager::screenH = 500;
int GameManager::screenW = 800;

static int playerSpeed = 300;
static int aiSpeed = 350;
static int initialBallXSpeed = 250;
static int initialBallYSpeed = 40;

// when set to true, two a.i. player will play
// when set to false, the player can control the left paddle
static bool playerDisabled = true;

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
	int flags = 0;
	int initted = Mix_Init(flags);

	if ((initted & flags) != flags) {
		cerr << "error initializing SDL_mixer:" << SDL_GetError() << endl;
		exit (-1);
	}

	// default=16 bit
	int err = Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 1024);
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

void game_main() 
{
	// create entities
	PlayerPaddle pp(gRenderer, "res/paddle_r.png", 20, GameManager::screenH/2, playerSpeed);
	pp.init();
	pp.setDisabled(playerDisabled);

	// left ai
	AiPaddle aiLeft(gRenderer, "res/paddle_r.png", 20, GameManager::screenH/2, aiSpeed, true,
			GameManager::screenW/2);
	aiLeft.init();
	aiLeft.setDisabled(!playerDisabled);

	// right ai
	AiPaddle aiRight(gRenderer, "res/paddle_r.png", GameManager::screenW-20, GameManager::screenH/2, aiSpeed, false,
			GameManager::screenW/2);
	aiRight.init();

	// ball
	Ball ball(gRenderer, "res/ball.png", GameManager::screenW/2, GameManager::screenH/2,
				initialBallXSpeed, initialBallYSpeed);
	ball.init();

	GameManager manager(gRenderer, ball, pp, aiLeft, aiRight);
	manager.init(GameManager::screenW, GameManager::screenH);

	// set initial positions
	manager.restartRound();

	// start main loop
	mainLoop(manager);
}


int main(int argc, char **argv)
{
	// The window we'll be rendering to
	SDL_Window* window = NULL;

	// random seed
	srand(time(NULL));

	// Initialize SDL
	window = initSDL(window);

	// game logic
	game_main();

	// Destroy window
	SDL_DestroyWindow(window);

	// Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	Mix_CloseAudio();

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

