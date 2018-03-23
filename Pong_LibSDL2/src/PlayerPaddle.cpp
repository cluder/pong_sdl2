/*
 * PlayerPaddle.cpp
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#include "PlayerPaddle.h"


PlayerPaddle::PlayerPaddle(SDL_Renderer* renderer, int x, int y) {
	this->x = x;
	this->y = y;
	this->pRenderer = renderer;
}

void PlayerPaddle::init() {
	tex = IMG_LoadTexture(pRenderer, "res/paddle.bmp");

	// query and save texture size
	SDL_QueryTexture(tex, NULL, NULL, &texW, &texH);

	// we want to draw the paddle at location 'x'
	// adjust x to be in the center of the paddle
	x = x-texW/2;
}

void PlayerPaddle::render() {


	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.h = texH;
	dstRect.w = texW;

	SDL_RenderCopy(pRenderer, tex, NULL, &dstRect);
}

void PlayerPaddle::handleEvent(SDL_Event &e) {
	if (e.key.keysym.sym == SDLK_UP) {
		if (e.type == SDL_KEYDOWN) {
			moveUp = true;
		} else if (e.type == SDL_KEYUP) {
			moveUp = false;
		}
	}

	if (e.key.keysym.sym == SDLK_DOWN) {
		if (e.type == SDL_KEYDOWN) {
			moveDown = true;
		} else if (e.type == SDL_KEYUP) {
			moveDown = false;
		}
	}

}

void PlayerPaddle::update(Uint32 tpf) {

	if (moveUp && moveDown) {
		return;
	}

	float velocity = 0;
	if (moveDown) {
		velocity = paddleSpeed;
	}

	if (moveUp) {
		velocity = paddleSpeed*-1;
	}

	y += velocity * (tpf/1000.f);

	SDL_Rect windowSize;
	SDL_RenderGetViewport(pRenderer, &windowSize);

	if (y < 0) {
		y = 0;
	}
	if (y + this->texH > windowSize.h) {
		y = windowSize.h - this->texH;
	}
}

SDL_Rect PlayerPaddle::getRect() {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = texW;
	rect.h = texH;

	return rect;
}

PlayerPaddle::~PlayerPaddle() {
    SDL_DestroyTexture(tex);
}

