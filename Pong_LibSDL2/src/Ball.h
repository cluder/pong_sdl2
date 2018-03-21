/*
 * Ball.h
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#ifndef SRC_BALL_H_
#define SRC_BALL_H_

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Ball {
public:
	Ball(SDL_Renderer* gRenderer, int y, int x);
	void init();
	void render();
	void update();
	virtual ~Ball();

	int getY() {return y;}
private:
	SDL_Renderer *pRenderer = NULL;
	SDL_Texture *tex = NULL;
	int x;
	int y;
	int texW = 0;
	int texH = 0;

	// movement
	float speed = 3;

	float xVelocity = speed;
	float yVelocity = speed;

};

#endif /* SRC_BALL_H_ */
