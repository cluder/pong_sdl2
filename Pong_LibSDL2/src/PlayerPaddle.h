/*
 * PlayerPaddle.h
 *
 *  Created on: 18.03.2018
 *      Author: core
 */

#ifndef SRC_PLAYERPADDLE_H_
#define SRC_PLAYERPADDLE_H_
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using namespace std;

class PlayerPaddle {
public:
	PlayerPaddle(SDL_Renderer* renderer, float x, float y, float speed)
		: pRenderer(renderer), x(x), y(y), speed(speed)  {};
	void init();
	void handleEvent(SDL_Event &e);
	void render();
	void update(Uint32 tpf);
	virtual ~PlayerPaddle();

	SDL_Rect getRect();
	void printPos(string str = "") { cerr << str << "pos:" << y << " - " << y+texH << endl;};

	int getX() {return x;}
	int getY() {return y;}

	int getTexW() {return texW;}
	int getTexH() {return texH;}
private:
	SDL_Renderer* pRenderer = NULL;
	float x;
	float y;
	float speed;

	int texW = 0;
	int texH = 0;
	SDL_Texture* tex = NULL;

	bool moveUp = false;
	bool moveDown = false;
};

#endif /* SRC_PLAYERPADDLE_H_ */
