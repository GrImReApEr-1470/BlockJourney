/*
 * Player.h
 *
 *  Created on: May 14, 2020
 *      Author: gabriel
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include <GL/glut.h>

#include "Shape.h"

class Player : public Shape {
public:
	int pos = 0;  // is the player standing/sleeping in x/sleeping in y
	int temp_pos = 0;
	Player(float x,float y,float z):Shape(x,y,z) {}
	void spawn();
	Player();
	virtual ~Player();
	void update();
	void onMove(int key,int x,int y);

	void spawnLateralDown();
	void spawnFromTop();
	void spawnDownTop();

};

#endif /* PLAYER_H_ */
