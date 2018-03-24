/*
 * Ball.h
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#ifndef SRC_BALL_H_
#define SRC_BALL_H_

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

using namespace std;

class Ball {
public:
	Ball(SDL_Renderer* gRenderer, int x, int y, float initXSpeed, float initYSpeed)
		:pRenderer(gRenderer), x(x), y(y),
		 initialXSpeed(initXSpeed), initialYSpeed(initYSpeed)
		{};

	void init();
	void render();
	void update(Uint32 tpf);
	virtual ~Ball();

	// hit a paddle - increase speed
	void hit();
	void resetSpeed() {xVelocity = initialXSpeed; yVelocity = initialYSpeed;}
	SDL_Rect getRect();

	float getCenterY() {return this->y + this->texH/2 ;}
	float getCenterX() {return this->x + this->texW/2 ;}

	int getX() {return x;}
	void setX(int x) {this->x = x;}

	int getTexW() {return this->texW;}
	void setTexW(int x) {this->texW = x;}

	int getY() {return y;}
	void setY(int y) {this->y = y;}

	int getTexH() {return this->texH;}
	void setTexH(int y) {this->texH = y;}

	float getSpeed() const {return speed;}
	void setSpeed(float speed) {this->speed = speed;}

	float getXVelocity() const {return xVelocity;}
	void setXVelocity(float velocity) {xVelocity = velocity;}

	float getYVelocity() const {return yVelocity;}
	void setYVelocity(float velocity) {if (yVelocity < maxSpeed) yVelocity = velocity;}

private:
	SDL_Renderer *pRenderer = NULL;
	SDL_Texture *tex = NULL;
	float x;
	float y;
	int texW = 0;
	int texH = 0;

	// movement speed
	float initialXSpeed = 200;
	float initialYSpeed = 100;

	float speed = initialXSpeed;
	float maxSpeed = 400;

	float xVelocity = speed;
	float yVelocity = initialYSpeed;

	// sound
	Mix_Music* plop = NULL;

};

#endif /* SRC_BALL_H_ */

