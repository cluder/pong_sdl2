/*
 * AiPaddle.cpp
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#include "AiPaddle.h"

AiPaddle::AiPaddle(SDL_Renderer* renderer, int x, int y) {
	this->x = x;
	this->y = y;
	this->pRenderer = renderer;
}

void AiPaddle::update(Ball &ball) {

//	paddle.velocity = ball.getY() - paddle.getY() ? -1 : 1 * PADDLE_VELOCITY

	if (this->y < ball.getY()) {
		this->yVelocity = this->ySpeed;
	} else {
		this->yVelocity = this->ySpeed * -1;
	}

	this->y += yVelocity;

}

void AiPaddle::init() {
	tex = IMG_LoadTexture(pRenderer, "img/paddle.bmp");

	// tint color red
	SDL_SetTextureColorMod(tex, 0xF0, 0x00,0x00);
}

void AiPaddle::render() {
	// draw paddle
	SDL_QueryTexture(tex, NULL, NULL, &texW, &texH);

	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.h = texH;
	dstRect.w = texW;

	SDL_RenderCopy(pRenderer, tex, NULL, &dstRect);
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

