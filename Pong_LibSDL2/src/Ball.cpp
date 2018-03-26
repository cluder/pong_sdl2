/*
 * Ball.cpp
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#include "Ball.h"
#include "SDL2/SDL_mixer.h"
#include <iostream>
#include "GameManager.h"

using namespace std;

void Ball::init() {

	// load hit sound
	paddleHit = Mix_LoadMUS("res/pong.ogg");
	if (paddleHit == NULL) {
		cerr << "unable to load sound: " << SDL_GetError() << endl;
		exit(-1);
	}
}

// move ball according to x/y velocity
void Ball::update(Uint32 tpf) {
	if (tpf == 0) {
		return;
	}

	// limit y velocity to max window height
	yVelocity = min(yVelocity, (float)GameManager::screenH);
	xVelocity = min(xVelocity, (float)GameManager::screenW);

	float tpf1000 = (tpf/1000.f);
	x += xVelocity * tpf1000;
	y += yVelocity * tpf1000;
}

void Ball::hit() {
	// 5% x speed increase per hit
	setXVelocity(getXVelocity() *1.05);

	// play sound
	int err = Mix_PlayMusic(paddleHit, 0);
	if (err  == -1) {
		cerr << "could not play sound" << SDL_GetError() << endl;
		exit(-1);
	}
}

Ball::~Ball() {
	if (paddleHit != NULL) {
		Mix_FreeMusic(paddleHit);
	}
}

