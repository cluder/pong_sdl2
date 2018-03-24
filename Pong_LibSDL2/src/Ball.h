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
	Ball(SDL_Renderer* gRenderer, int y, int x);
	void init();
	void render();
	void update(Uint32 tpf);
	virtual ~Ball();

	// hit a paddle - increase speed
	void hit();
	void resetSpeed() {xVelocity = initialSpeed; yVelocity = 0;}
	SDL_Rect getRect();

	float getCenterY() {return this->y + this->texH/2 ;}

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
	void setYVelocity(float velocity) {yVelocity = velocity;}

private:
	SDL_Renderer *pRenderer = NULL;
	SDL_Texture *tex = NULL;
	float x;
	float y;
	int texW = 0;
	int texH = 0;

	// movement speed
	float initialSpeed = 300;
	float speed = initialSpeed;
	float maxSpeed = 500;

	float xVelocity = speed;
	float yVelocity = 0;

	// sound
	Mix_Music* plop;

};

#endif /* SRC_BALL_H_ */

