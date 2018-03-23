/*
 * Ball.cpp
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#include "Ball.h"
#include "SDL2/SDL_mixer.h"
#include <iostream>

using namespace std;

Ball::Ball(SDL_Renderer *renderer, int x, int y) {
	this->pRenderer = renderer;
	this->x = x;
	this->y = y;
	plop = NULL;
}

void Ball::init() {

	// loads ball texture
	tex = IMG_LoadTexture(pRenderer, "res/ball.png");
	SDL_QueryTexture(tex, NULL, NULL, &texW, &texH);

	// load hit sound
	plop = Mix_LoadMUS("res/pong.ogg");
	if (plop == NULL) {
		cerr << "unable to load sound: " << SDL_GetError() << endl;
		exit(-1);
	}

}

// move ball according to x/y velocity
void Ball::update(Uint32 tpf) {
	x += xVelocity * (tpf/1000.f);
	y += yVelocity * (tpf/1000.f);
}

// draws the ball at position x,y
void Ball::render() {
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

void Ball::hit() {

	// increase x velocity
	if (this->xVelocity < this->maxSpeed) {
		this->xVelocity += 50;
	}

	// play sound
	int err = Mix_PlayMusic(plop, 0);
	if (err  == -1) {
		cerr << "could not play sound" << SDL_GetError() << endl;
		exit(-1);
	}

}

// free the texture
Ball::~Ball() {
	SDL_DestroyTexture(tex);

	Mix_FreeMusic(plop);
}

