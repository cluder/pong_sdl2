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
void Ball::update(Uint32 tpf) {
	x += xVelocity * (tpf/1000.f);
	y += yVelocity * (tpf/1000.f);
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

SDL_Rect Ball::getRect() {
	SDL_Rect ballRect;
	ballRect.x = x;
	ballRect.y = y;
	ballRect.w = texW;
	ballRect.h = texH;

	return ballRect;
}

// free the texture
Ball::~Ball() {
	SDL_DestroyTexture(tex);
}

