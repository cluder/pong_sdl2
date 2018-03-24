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
	AiPaddle(SDL_Renderer* renderer, float x, float y, float speed, bool isLeft,
				float sightRange)
		: renderer(renderer), x(x), y(y),
		  initialX(x), initialY(y),
		  speed(speed), isLeft(isLeft),
		  sightRange(sightRange)
		{};

	void init();
	void render();
	void update(Uint32 tpf, Ball &ball);

	void resetPos();;

	SDL_Rect getRect();

	virtual ~AiPaddle();

private:
	SDL_Renderer* renderer = NULL;
	float x;
	float y;
	float initialX;
	float initialY;
	float speed;
	bool isLeft;

	int texW = 0;
	int texH = 0;
	SDL_Texture* tex = NULL;

	float yVelocity = speed;

	float sightRange;

	void moveToBall(float absYDistance, int padCenterY, Uint32 tpf, Ball& ball);
	void moveToCenter(Uint32 tpf);
	bool ballMovesAway(Ball &ball);
};

#endif /* SRC_AIPADDLE_H_ */
