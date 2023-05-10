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
	void resetXYZ(int x, int y, int z){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void resetPlayer();
	void spawnLateralDown();
	void spawnFromTop();
	void spawnDownTop();

};

#endif /* PLAYER_H_ */
