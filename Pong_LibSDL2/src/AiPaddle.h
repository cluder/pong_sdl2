/*
 * AiPaddle.h
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#ifndef SRC_AIPADDLE_H_
#define SRC_AIPADDLE_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Ball.h"

using namespace std;

class AiPaddle {
public:
	AiPaddle(SDL_Renderer* gRenderer, int x, int y);
	void init();
	void render();
	void update(Ball &ball);
	virtual ~AiPaddle();

private:
	int texW = 0;
	int texH = 0;
	int x = 0;
	int y = 0;
	SDL_Texture* tex = NULL;
	SDL_Renderer* pRenderer = NULL;

	float paddleSpeed = 10;
};

#endif /* SRC_AIPADDLE_H_ */
