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

	// cheater !!
	this->y = ball.getY();
	this->y -= this->texH/2;

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

AiPaddle::~AiPaddle() {
	SDL_DestroyTexture(tex);
}

