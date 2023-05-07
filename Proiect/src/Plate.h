
#ifndef PLATE_H_
#define PLATE_H_
#include <iostream>
#include <stdio.h>
#include "Shape.h"
#include <GL/glut.h>

using namespace std;

class Plate : public Shape{

public:


	int loadingState = 0;
	Plate();
	Plate(float x,float y,float z):Shape(x,y,z) {}
	virtual ~Plate();
	void spawn();
	void update();

};

#endif /* PLATE_H_ */
