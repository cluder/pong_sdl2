/*
 * PlayerPaddle.h
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#ifndef SRC_PLAYERPADDLE_H_
#define SRC_PLAYERPADDLE_H_
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using namespace std;

class PlayerPaddle {
public:
	PlayerPaddle(SDL_Renderer* gRenderer, int x, int y);
	void init();
	void handleEvent(SDL_Event &e);
	void render();
	void update();
	virtual ~PlayerPaddle();

	SDL_Rect getRect();

	int getX() {return x;}
	int getY() {return y;}

	int getTexW() {return texW;}
	int getTexH() {return texH;}
private:
	int texW = 0;
	int texH = 0;
	int x = 0;
	int y = 0;
	SDL_Texture* tex = NULL;
	SDL_Renderer* pRenderer = NULL;

	float paddleSpeed = 5;
	bool moveUp = false;
	bool moveDown = false;
};

#endif /* SRC_PLAYERPADDLE_H_ */
