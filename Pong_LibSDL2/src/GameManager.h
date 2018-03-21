/*
 * GameManager.h
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#ifndef SRC_GAMEMANAGER_H_
#define SRC_GAMEMANAGER_H_

#include <iostream>

#include "PlayerPaddle.h"
#include "AiPaddle.h"
#include "Ball.h"

#include "SDL2/SDL_ttf.h"

class GameManager {
public:
	GameManager(SDL_Renderer *pRenderer, Ball &b, PlayerPaddle &player, AiPaddle &ai)
		: pRenderer(pRenderer), ball(b), player(player), ai(ai) {};

	void init(int screenW, int screenH);

	bool handleInput();
	// render all objects
	void render();
	// update all objects
	void update();

	void drawUI();
	void checkCollision();
	void restartRound();

	PlayerPaddle &getPlayer()  {return player;}

	virtual ~GameManager();
private:
	SDL_Renderer *pRenderer;
	Ball &ball;
	PlayerPaddle &player;
	AiPaddle &ai;

	int playerScore = 0;
	int aiScore = 0;

	int screenW = 0;
	int screenH = 0;

	TTF_Font* scoreFont = NULL;

	void renderScore(int score, int x, int y);
};

#endif /* SRC_GAMEMANAGER_H_ */
