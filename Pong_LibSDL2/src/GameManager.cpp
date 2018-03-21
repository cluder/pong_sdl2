/*
 * GameManager.cpp
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#include "GameManager.h"

SDL_Rect posPlayerScore;

void GameManager::init(int screenW, int screenH) {
	this->screenW = screenW;
	this->screenH = screenH;

	this->scoreFont = TTF_OpenFont("img/OpenSans-Regular.ttf", 40);
}

bool GameManager::handleInput() {
	bool quit = false;

	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			cout << "QUIT requested, exiting ..." << endl;
			quit = true;
		}
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
			cout << "ESC pressed, exiting ... " << endl;
			quit = true;
		}

		// pass event to player
		player.handleEvent(e);
	}
	return quit;
}

void GameManager::render() {

	// clear screen
	SDL_SetRenderDrawColor(pRenderer, 0x0, 0x0, 0x0, SDL_ALPHA_OPAQUE );
	SDL_RenderClear(pRenderer);

	drawUI();

	player.render();
	ball.render();
	ai.render();

	// update screen
	SDL_RenderPresent(pRenderer);
}

void GameManager::update() {
	player.update();
	ball.update();
	ai.update(ball);

	checkCollision();
}

void GameManager::checkCollision() {
	// check paddle collision

	SDL_Rect ballRect = ball.getRect();
	SDL_Rect playerRect = player.getRect();
	SDL_Rect aiRect = ai.getRect();

	SDL_Rect result;

	if (SDL_IntersectRect(&playerRect,&ballRect, &result) == SDL_TRUE) {
		// ball hit player paddle
		// reset ball to player edge
		// bounce
		ball.setX(playerRect.x + playerRect.w);
		ball.setXVelocity(ball.getSpeed());

		ball.hit();
	}

	if (SDL_IntersectRect(&ballRect, &aiRect, &result) == SDL_TRUE) {
		// ball hit ai paddle
		// reset ball to player edge
		// bounce
		ball.setX(aiRect.x - ballRect.w);
		ball.setXVelocity(ball.getSpeed() * -1);

		ball.hit();
	}

	// check play field collision
	SDL_Rect windowSize;
	SDL_RenderGetViewport(pRenderer, &windowSize);

	if (ball.getX() < 0) {
		// left wall hit - AI scores
		aiScore++;
		restartRound();
		return;
	}

	if (ball.getX() + ball.getTexW() > windowSize.w) {
		// right wall hit - Player scores
		playerScore++;
		restartRound();
		return;
	}

	if (ball.getY() < 0) {
		// top hit - bounce down
		ball.setY(0);
		ball.setYVelocity(ball.getSpeed());
	}

	if (ball.getY() + ball.getTexH() > windowSize.h) {
		// bottom hit - bounce up
		ball.setY(windowSize.h - ball.getTexH());
		ball.setYVelocity(ball.getSpeed() * -1);
	}
}

void GameManager::restartRound() {

	SDL_Rect windowSize;
	SDL_RenderGetViewport(pRenderer, &windowSize);

	// reset ball position
	ball.resetSpeed();

	ball.setX(windowSize.w/2);
	ball.setY(windowSize.h/2);

	ball.setXVelocity(ball.getXVelocity() * -1);

}

void GameManager::renderScore(int score, int x, int y) {
	// player score
	string sPlayerScore = std::to_string(score);
	SDL_Color scoreColor = { 255, 255, 255 };
	SDL_Surface* tmpSurface = TTF_RenderText_Solid(scoreFont,
			sPlayerScore.c_str(), scoreColor);
	SDL_Texture* playerScoreTex = SDL_CreateTextureFromSurface(pRenderer,
			tmpSurface);
	SDL_FreeSurface(tmpSurface);
	int texW;
	int texH;
	SDL_QueryTexture(playerScoreTex, NULL, NULL, &texW, &texH);
	posPlayerScore.x = x;
	posPlayerScore.y = y;
	posPlayerScore.w = texW;
	posPlayerScore.h = texH;
	SDL_RenderCopy(pRenderer, playerScoreTex, NULL, &posPlayerScore);
}

void GameManager::drawUI() {

	// draw middle line
	SDL_SetRenderDrawColor(pRenderer, 0xFF,0xFF,0xFF,120);

	SDL_RenderDrawLine(this->pRenderer, this->screenW/2, 20, this->screenW/2,this->screenH-20);

	// player score
	renderScore(playerScore, screenW / 2 - 100, 30);
	// ai score
	renderScore(aiScore, screenW / 2 + 100, 30);
}

GameManager::~GameManager() {

}
