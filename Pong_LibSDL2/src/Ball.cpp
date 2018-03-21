/*
 * Ball.cpp
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#include "Ball.h"

Ball::Ball(SDL_Renderer *renderer, int x, int y) {
	this->pRenderer = renderer;
	this->x = x;
	this->y = y;
}

// loads the ball texture
void Ball::init() {
	tex = IMG_LoadTexture(pRenderer, "img/ball.png");
}


// move ball according to x/y velocity
// check for collision with other objects
void Ball::update() {

	x += xVelocity;
	y += yVelocity;

	// TODO check for wall collisions
	SDL_Rect windowSize;
	SDL_RenderGetViewport(pRenderer, &windowSize);

	if (x < 0) {
		// left wall hit - AI scores
		x = 0;
		xVelocity = speed;
	}

	if (x + this->texW > windowSize.w) {
		// right wall hit - Player scores
		xVelocity = speed * -1;
	}

	if (y < 0) {
		y = 0;
		yVelocity = speed;
	}

	if (y + this->texH > windowSize.h) {
		yVelocity = speed * -1;
	}

}

// draws the ball at position x,y
void Ball::render() {
	SDL_QueryTexture(tex, NULL, NULL, &texW, &texH);
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.h = texH;
	dstRect.w = texW;

	SDL_RenderCopy(pRenderer, tex, NULL, &dstRect);
}

// free the texture
Ball::~Ball() {
	SDL_DestroyTexture(tex);
}

