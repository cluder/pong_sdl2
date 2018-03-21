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
	SDL_SetRenderDrawColor(pRenderer, 0x0, 0x0, 0x0, 0x0 );
	SDL_RenderClear(pRenderer);

	drawUI();

	player.render();
	ball.render();
	ai.render();

	// update screen
	SDL_RenderPresent(pRenderer);

}

void GameManager::update() {
//	cout << " update " << endl;
	player.update();
	ball.update();
	ai.update(ball);

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

	// player score
	renderScore(playerScore, screenW / 2 - 100, 30);

	// ai score
	renderScore(0, screenW / 2 + 100, 30);
}

GameManager::~GameManager() {

}
