/*
 * GameManager.cpp
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#include "GameManager.h"

void GameManager::init(int screenW, int screenH) {
	this->screenW = screenW;
	this->screenH = screenH;

	this->scoreFont = TTF_OpenFont("res/OpenSans-Regular.ttf", 40);
	this->fpsFont = TTF_OpenFont("res/OpenSans-Regular.ttf", 25);
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

// tpf: time per frame
void GameManager::update(Uint32 tpf) {
	player.update(tpf);
	ball.update(tpf);
	ai.update(tpf, ball);

	checkCollision();

	Uint32 now = SDL_GetTicks();
	if (lastFpsUpdate < now-300) {
		fps = (float)1000/(float)tpf;
		lastFpsUpdate = SDL_GetTicks();
	}
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
		ball.setX(playerRect.x + playerRect.w+1);
		ball.setXVelocity(abs(ball.getXVelocity()));

		ball.hit();

		// ball center
		int ballY = ball.getY()+ball.getTexH()/2;
		// paddle center
		int paddleCenter = playerRect.y + playerRect.h/2;

		if (ballY > paddleCenter) {
			// hit lower region
			cerr << " increase yvel" << endl;

			ball.setYVelocity(ball.getYVelocity()+300);
		} else {
			cerr << " decrease y vel" << endl;
			ball.setYVelocity(ball.getYVelocity()-300);
		}

		cerr << "xVel:" << ball.getXVelocity()
			 << " yVel:" << ball.getYVelocity()  << endl;


	}

	if (SDL_IntersectRect(&ballRect, &aiRect, &result) == SDL_TRUE) {
		// ball hit ai paddle
		// reset ball to paddle edge
		// bounce
		ball.setX(aiRect.x - ballRect.w);
		ball.setXVelocity(-ball.getXVelocity());

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
		ball.setYVelocity(abs(ball.getYVelocity()));
	}

	if (ball.getY() + ball.getTexH() > windowSize.h) {
		// bottom hit - bounce up
		ball.setY(windowSize.h - ball.getTexH());
		ball.setYVelocity(-ball.getYVelocity());
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
	SDL_Surface* tmpSurface = TTF_RenderText_Blended(scoreFont,
			sPlayerScore.c_str(), scoreColor);
	SDL_Texture* playerScoreTex = SDL_CreateTextureFromSurface(pRenderer,
			tmpSurface);
	SDL_FreeSurface(tmpSurface);
	int texW;
	int texH;
	SDL_QueryTexture(playerScoreTex, NULL, NULL, &texW, &texH);
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = texW;
	dstRect.h = texH;
	SDL_RenderCopy(pRenderer, playerScoreTex, NULL, &dstRect);
}

void GameManager::drawUI() {

	// draw middle line
	SDL_SetRenderDrawColor(pRenderer, 0xFF,0xFF,0xFF,120);

	SDL_RenderDrawLine(this->pRenderer, this->screenW/2, 20, this->screenW/2,this->screenH-20);

	// player score
	renderScore(playerScore, screenW / 2 - 100, 30);
	// ai score
	renderScore(aiScore, screenW / 2 + 100, 30);
	// show fps
	drawFps();
}

void GameManager::drawFps() {
	string sFps = "FPS: " +std::to_string(fps);

	SDL_Color color = { 255, 255, 0 };
	SDL_Surface* tmpSurface = TTF_RenderText_Blended(fpsFont,
			sFps.c_str(), color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(pRenderer,
			tmpSurface);
	int texW;
	int texH;
	SDL_QueryTexture(tex, NULL, NULL, &texW, &texH);
	SDL_FreeSurface(tmpSurface);
	SDL_Rect fpsRect;
	fpsRect.x = 20;
	fpsRect.y = 20;
	fpsRect.w = texW;
	fpsRect.h = texH;

	SDL_RenderCopy(pRenderer, tex, NULL, &fpsRect);

}

GameManager::~GameManager() {

}
