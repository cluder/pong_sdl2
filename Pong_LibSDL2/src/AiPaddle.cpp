/*
 * AiPaddle.cpp
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#include "AiPaddle.h"
#include "GameManager.h"

void AiPaddle::update(Uint32 tpf, Ball &ball) {

	// paddle mid
	int padCenterY = this->y + this->texH/2;

	// absolute distance to ball
	float absDistance = abs(padCenterY - ball.getCenterY());

	// if the distance is less than the paddle height, we reduce the speed accordingly
	float fact = 1.0f / this->texH * absDistance;
	if (fact > 1) {
		fact = 1;
	}

	// calculate velocity speed and direction
	this->yVelocity = this->speed * fact;

	if (padCenterY > ball.getCenterY()) {
		// paddle lower than ball - move up
		this->yVelocity *= -1;
	}

	this->y += yVelocity * ((float)tpf/1000.0f);

	// limit paddle movement
	if (this->y + this->texH > GameManager::screenH) {
		this->y = GameManager::screenH - this->texH;
	}
	if (this->y + this->texH < 0) {
		this->y = 0;
	}

}

void AiPaddle::init() {
	tex = IMG_LoadTexture(renderer, "res/paddle.bmp");
	// query and save texture size
	SDL_QueryTexture(tex, NULL, NULL, &texW, &texH);

	// tint color red
	SDL_SetTextureColorMod(tex, 0xF0, 0x00,0x00);

	// we want to draw the paddle at location 'x'
	// adjust x to be in the center of the paddle
	x = x-texW/2;
}

void AiPaddle::render() {
	// draw paddle
	SDL_QueryTexture(tex, NULL, NULL, &texW, &texH);

	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.h = texH;
	dstRect.w = texW;

	SDL_RenderCopy(renderer, tex, NULL, &dstRect);
}

SDL_Rect AiPaddle::getRect() {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = texW;
	rect.h = texH;

	return rect;
}

AiPaddle::~AiPaddle() {
	SDL_DestroyTexture(tex);
}

