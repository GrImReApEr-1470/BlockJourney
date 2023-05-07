#ifndef SHAPE_H_
#define SHAPE_H_

class Shape {
public:
	float x;
	float y;
	float z;

	Shape();

	Shape(float x, float y, float z) ;
	virtual void spawn() = 0;







	virtual ~Shape();

	float getX() const {
		return x;
	}

	void setX(float x) {
		this->x = x;
	}

	float getY() const {
		return y;
	}

	void setY(float y) {
		this->y = y;
	}

	float getZ() const {
		return z;
	}

	void setZ(float z) {
		this->z = z;
	}
};

#endif /* SHAPE_H_ */
