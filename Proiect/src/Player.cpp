/*
 * Player.cpp
 *
 *  Created on: May 14, 2020
 *      Author: gabriel
 */

#include "Player.h"
#include <iostream>
#include "SOIL/SOIL.h"

Player::Player() {
	// TODO Auto-generated constructor stub

}

using namespace std;

int leftKey = 0;
int topkey = 0;
int rightKey = 0;
int downKey = 0;

int standing = 0;

int themove = 0;
int lastMove = 0;
int peLat = 0;
enum {
	LEFT,
	RIGHT,
	TOP,
	DOWN,
	START
};

int lastKey= 99;
int currentKey = START;



GLfloat texpts2[2][2][2] = { {{1.0, 1.0},{1.0, 0.0}},{{0.0, 1.0},{0.0, 0.0} } };
#define imageWidth2 64
#define imageHeight2 64
GLubyte image2[3 * imageWidth2*imageHeight2];
GLuint texture2;


void LoadTextureLava2(void)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height;
    // sursa imaginii https://www.hiclipart.com/free-transparent-background-png-clipart-miami
    unsigned char* image = SOIL_load_image("texture.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    //SOIL_free_image_data(image);
    //glBindTexture(GL_TEXTURE_2D, 0);
}




void Player::spawn() {

	if (currentKey == START) {

		this->spawnFromTop();
		this->pos = 0;
		this->temp_pos = 0;

	} else if (currentKey == LEFT) {
		// if standing
		if (this->pos == 0) {
			this->spawnLateralDown();
			if (themove - lastMove != 0) {
				lastMove +=1;
				this->temp_pos = 1;
			}
		}
		// if sleeping in x
		else if (this->pos == 1) {
			this->spawnFromTop();
			if (themove - lastMove != 0) {
				lastMove +=1;
				this->temp_pos = 0;
				this->x = this->x+10;
			}
		}
		// if sleeping in z
		else if (this->pos == 2) {
			this->spawnDownTop();
			if (themove - lastMove != 0)
			{
				lastMove += 1;
				this->temp_pos = 2;
			}
		}

	} else if(currentKey == TOP) {
		// if standing
		if (this->pos == 0) {
			this->spawnDownTop();
			if(themove - lastMove !=0 ){
				lastMove +=1;
				this->temp_pos = 2;
			}
		}
		// if sleeping in x
		else if (this->pos == 1) {
			this->spawnLateralDown();
			if(themove - lastMove !=0) {
				lastMove +=1;
				this->temp_pos = 1;
			}
		}
		//if sleeping in z
		else if (this->pos == 2) {
			this->spawnFromTop();
			if(themove - lastMove !=0) {
				lastMove +=1;
				this->temp_pos = 0;
				this->z = this->z + 10;
			}
		}


	} else if (currentKey == RIGHT){
		if (this->pos == 0) {
			this->spawnLateralDown();
			if (themove - lastMove != 0) {
				lastMove +=1;
				this->temp_pos = 1;
				this->x = this->x - 10;
			}
		}
		else if (this->pos == 1) {
			this->spawnFromTop();
			if (themove - lastMove != 0) {
				lastMove +=1;
				this->temp_pos = 0;
			}
		}
		else if (this->pos == 2) {
			this->spawnDownTop();
			if (themove - lastMove != 0) {
				lastMove +=1;
				this->temp_pos = 2;
			}
		}

	} else if (currentKey == DOWN) {


		if (this->pos == 0) {
			this->spawnDownTop();
			if(themove - lastMove !=0 ){
				lastMove +=1;
				this->temp_pos = 2;
				this->z = this->z - 10;
			}
		}
		if (this->pos == 1) {
			this->spawnLateralDown();
			if(themove - lastMove !=0) {
				lastMove +=1;
				this->temp_pos = 1;
			}
		}
		else if (this->pos == 2) {
			this->spawnFromTop();
			if(themove - lastMove !=0) {
				lastMove +=1;
				this->temp_pos = 0;
			}
		}


	}


}



Player::~Player() {
	// TODO Auto-generated destructor stub
}

void Player::update() {



}
int k = 0;

void printLastKey(int last ){

	switch(last){
	case 0 :
		cout << "LEFT";
		break;

	case 1 :
		cout << "RIGHT";
		break;

	case 2 :
		cout << "TOP";
		break;

	case 3 :
		cout << "DOWN";
		break;
	}

}

void Player::onMove(int key,int x,int y) {
	cout<<this->pos<<this->temp_pos<<endl;
	this->pos = this->temp_pos;
	switch(key) {

		case GLUT_KEY_LEFT:
			//std::cout<<"Typed LEFT"<<endl;
			this->x = this->x + 10;
			leftKey = 1;
			topkey = 0;
			rightKey = 0;
			downKey = 0;
			themove = themove + 1;
			currentKey = LEFT;
			cout <<"LEFT" << leftKey<<endl;
			cout <<"RIGHT" <<rightKey <<endl;
			cout <<"TOP" <<topkey <<endl;
			cout <<"DOWN" <<downKey <<endl;
			cout<< "MOve" << themove <<endl;
			cout <<"Last Move" <<lastMove <<endl;
			cout <<"Last KEY: ";

			printLastKey(lastKey);
			cout<<endl;
			cout <<"Current Key: ";
			printLastKey(currentKey);
			cout<<endl;
			//cout<<"Pe lat" << peLat <<endl;
			cout <<"In picioare " << standing <<endl;
			break;

		case GLUT_KEY_RIGHT:
			std::cout<<"Typed RIGHT"<<endl;
			this->x = this->x - 10;
			leftKey = 0;
			topkey = 0;
			rightKey = 1;
			downKey = 0;
			themove = themove + 1;
			currentKey = RIGHT;
			cout <<"LEFT" << leftKey<<endl;
			cout <<"RIGHT" <<rightKey <<endl;
			cout <<"TOP" <<topkey <<endl;
			cout <<"DOWN" <<downKey <<endl;
			cout<< "MOve" << themove <<endl;
			cout <<"Last Move: " <<lastMove <<endl;
			cout <<"Last KEY:";
			printLastKey(lastKey);
			cout<<endl;
			cout <<"Current Key: ";
			printLastKey(currentKey);
			cout<<endl;
			cout <<"In picioare " << standing <<endl;
			break;

		case GLUT_KEY_UP:
			std::cout<<"Typed UP"<<endl;
			this->z= this->z + 10;
			topkey = 1;
			leftKey = 0;
			rightKey = 0;
			downKey = 0;
			themove = themove + 1;
			currentKey = TOP;
			cout <<"LEFT" << leftKey<<endl;
			cout <<"RIGHT" <<rightKey <<endl;
			cout <<"TOP" <<topkey <<endl;
			cout <<"DOWN" <<downKey <<endl;
			cout<< "MOve" << themove <<endl;
			cout <<"Last Move: " <<lastMove <<endl;
			cout <<"Last KEY:";
			printLastKey(lastKey);
			cout<<endl;
			cout <<"Current Key:";
			printLastKey(currentKey);
			cout<<endl;
			cout <<"In picioare " << standing <<endl;
			break;

		case GLUT_KEY_DOWN:
			std::cout<<"Typed Down"<<endl;
			this->z = this->z - 10;
			topkey = 0;
			leftKey = 0;
			rightKey = 0;
			downKey = 1;
			themove = themove + 1;
			currentKey = DOWN;
			cout <<"LEFT" << leftKey<<endl;
			cout <<"RIGHT" <<rightKey <<endl;
			cout <<"TOP" <<topkey <<endl;
			cout <<"DOWN" <<downKey <<endl;
			cout<< "MOve" << themove <<endl;
			cout <<"Last Move" <<lastMove <<endl;
			cout <<"Last KEY:";
			printLastKey(lastKey);
			cout<<endl;
			cout <<"Current Key: ";
			printLastKey(currentKey);
			cout<<endl;
			cout <<"In picioare " << standing <<endl;
			break;
	}



}
int loadingDown = 0;
int loadingTop = 0;

void Player::spawnLateralDown() {
	// cout<<"sleeping in x"<<endl;
	static GLfloat par_3[] = { 0.2, 0.2, 0.1, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, par_3);
	glColor3f(0.2f, 0.2f, 0.1f);
				glEnable(GL_TEXTURE_2D);
				if (loadingDown==0) {
				LoadTextureLava2();
				loadingDown = 1;
				}
						glBegin(GL_POLYGON);
						glTexCoord2f(1.0, 0.0);glVertex3f( 0.0 + x, 0.0 + y, 0.0 + z);
						glTexCoord2f(0.0, 0.0);glVertex3f( 20.0 + x, 0.0 + y, 0.0 + z);
						glTexCoord2f(0.0, 1.0);glVertex3f( 20.0 + x, 0.0 + y, 10.0 + z);
						glTexCoord2f(1.0, 1.0);glVertex3f( 0.0 + x, 0.0 + y, 10.0 + z);
						glEnd();
					static GLfloat par_4[] = { 1.0, 1.0, 0.0, 1.0 };
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, par_4);
					glColor3f(1.0f, 1.1f, 0.0f);
						glBegin(GL_POLYGON);
						glTexCoord2f(1.0, 0.0);glVertex3f( 0.0 + x, 10.1 + y, 0.0 + z);
						glTexCoord2f(0.0, 0.0);glVertex3f( 20.0 + x, 10.1 + y, 0.0 + z);
						glTexCoord2f(0.0, 1.0);glVertex3f( 20.0 + x, 10.1 + y, 10.0 + z);
						glTexCoord2f(1.0, 1.0);glVertex3f( 0.0 + x, 10.1 + y, 10.0 + z);
						glEnd();
					static GLfloat par_2[] = { 0.4, 0.4, 0.4, 1.0 };
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, par_2);
					glColor3f(0.4f, 0.4f, 0.4f);
						glBegin(GL_POLYGON);
						glTexCoord2f(1.0, 0.0);glVertex3f( 0.0 + x, 0.0 + y, 0.0 + z);
						glTexCoord2f(0.0, 0.0);glVertex3f( 20.0 + x, 0.0 + y, 0.0 + z);
						glTexCoord2f(0.0, 1.0);	glVertex3f( 20.0 + x, 10.0 + y, 0.0 + z);
						glTexCoord2f(1.0, 1.0);glVertex3f( 0.0 + x, 10.0 + y, 0.0 + z);
						glEnd();

						glBegin(GL_POLYGON);
						glTexCoord2f(1.0, 0.0);glVertex3f( 0.0 + x, 0.0 + y, 10.0 + z);
						glTexCoord2f(0.0, 0.0);glVertex3f( 20.0 + x, 0.0 + y, 10.0 + z);
						glTexCoord2f(0.0, 1.0);glVertex3f( 20.0 + x, 10.0 + y, 10.0 + z);
						glTexCoord2f(1.0, 1.0);glVertex3f( 0.0 + x, 10.0 + y, 10.0 + z);
						glEnd();

						glBegin(GL_POLYGON);
						glTexCoord2f(1.0, 0.0);glVertex3f( 0.0 + x, 0.0 + y, 0.0 + z);
						glTexCoord2f(0.0, 0.0);glVertex3f( 0.0 + x, 0.0 + y, 10.0 + z);
						glTexCoord2f(0.0, 1.0);glVertex3f( 0.0 + x, 10.0 + y, 10.0 + z);
						glTexCoord2f(1.0, 1.0);glVertex3f( 0.0 + x, 10.0 + y, 0.0 + z);
						glEnd();

						glBegin(GL_POLYGON);
						glTexCoord2f(1.0, 0.0);glVertex3f( 20.0 + x, 0.0 + y, 0.0 + z);
						glTexCoord2f(0.0, 0.0);glVertex3f( 20.0 + x, 0.0 + y, 10.0 + z);
						glTexCoord2f(0.0, 1.0);glVertex3f( 20.0 + x, 10.0 + y, 10.0 + z);
						glTexCoord2f(1.0, 1.0);glVertex3f( 20.0 + x, 10.0 + y, 0.0 + z);
						glEnd();
						glDisable(GL_TEXTURE_2D);
}

void Player::spawnFromTop() {
	// cout<<"standing"<<endl;
	static GLfloat par_2[] = { 0.4, 0.4, 0.4, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, par_2);

	glColor3f(0.4f, 0.4f, 0.4f);
					glBegin(GL_POLYGON);
					glVertex3f( 0.0 + x, 0.0+ y, 0.0 + z);
					glVertex3f( 10.0 + x, 0.0+ y, 0.0 + z);
					glVertex3f( 10.0 + x, 0.0 + y, 10.0 + z);
					glVertex3f( 0.0 + x, 0.0 + y, 10.0 + z);
					glEnd();

	static GLfloat par_4[] = { 1.0, 1.1, 0.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, par_4);
				glColor3f(1.0f, 1.1f, 0.0f);
				glEnable(GL_TEXTURE_2D);
				if (loadingTop==0) {
				LoadTextureLava2();
				loadingTop = 1;
				}
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0, 0.0);glVertex3f( 0.0 + x, 20.2+ y, 0.0 + z);
					glTexCoord2f(0.0, 0.0);glVertex3f( 10.0 + x, 20.2+ y, 0.0 + z);
					glTexCoord2f(0.0, 1.0);glVertex3f( 10.0 + x, 20.2 + y, 10.0 + z);
					glTexCoord2f(1.0, 1.0);glVertex3f( 0.0 + x, 20.2+ y, 10.0 + z);
					glEnd();
				//glDisable(GL_TEXTURE_2D);
					static GLfloat par_3[] = { 0.4, 0.4, 0.4, 1.0 };
						glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, par_3);
				glColor3f(0.4f, 0.4f, 0.4f);
//				glEnable(GL_TEXTURE_2D);
				//LoadTextureLava2();
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0, 0.0);glVertex3f( 0.0 + x, 0.0 + y, 0.0 + z);
					glTexCoord2f(0.0, 0.0);glVertex3f( 10.0 + x, 0.0 + y, 0.0 + z);
					glTexCoord2f(0.0, 1.0);glVertex3f( 10.0 + x, 20.0 + y, 0.0 + z);
					glTexCoord2f(1.0, 1.0);glVertex3f( 0.0 + x, 20.0 + y, 0.0 + z);
					glEnd();

					glBegin(GL_POLYGON);
					glTexCoord2f(1.0, 0.0);glVertex3f( 0.0 + x, 0.0 + y, 10.0 + z);
					glTexCoord2f(0.0, 0.0);glVertex3f( 10.0 + x, 0.0 + y, 10.0 + z);
					glTexCoord2f(0.0, 1.0);glVertex3f( 10.0 + x, 20.0 + y, 10.0 + z);
					glTexCoord2f(1.0, 1.0);glVertex3f( 0.0 + x, 20.0 + y, 10.0 + z);
					glEnd();

					glBegin(GL_POLYGON);
					glTexCoord2f(1.0, 0.0);glVertex3f( 0.0 + x, 0.0 + y, 0.0 + z);
					glTexCoord2f(0.0, 0.0);glVertex3f( 0.0 + x, 0.0 + y, 10.0 + z);
					glTexCoord2f(0.0, 1.0);glVertex3f( 0.0 + x, 20.0 + y, 10.0 + z);
					glTexCoord2f(1.0, 1.0);glVertex3f( 0.0 + x, 20.0 + y, 0.0 + z);
					glEnd();

					glBegin(GL_POLYGON);
					glTexCoord2f(1.0, 0.0);glVertex3f( 10.0 + x, 0.0 + y, 0.0 + z);
					glTexCoord2f(0.0, 0.0);glVertex3f( 10.0 + x, 0.0 + y, 10.0 + z);
					glTexCoord2f(0.0, 1.0);glVertex3f( 10.0 + x, 20.0 + y, 10.0 + z);
					glTexCoord2f(1.0, 1.0);glVertex3f( 10.0 + x, 20.0 + y, 0.0 + z);
					glEnd();
					glDisable(GL_TEXTURE_2D);

}

void Player::spawnDownTop() {
	cout<<"sleeping in y"<<endl;
	static GLfloat par_2[] = { 0.2, 0.2, 0.1, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, par_2);
	glColor3f(0.2f, 0.2f, 0.1f);

	glBegin(GL_POLYGON);
		glVertex3f( 0.0 + x, 0.0 + y, 0.0 + z);
		glVertex3f( 10.0 + x, 0.0 + y, 0.0 + z);
		glVertex3f( 10.0 + x, 0.0 + y, 20.0 + z);
		glVertex3f( 0.0 + x, 0.0 + y, 20.0 + z);
	glEnd();
	static GLfloat par_3[] = { 1.0, 1.1, 0.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, par_3);
	glColor3f(1.0f, 1.1f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex3f( 0.0 + x, 10.0 + y, 0.0 + z);
		glVertex3f( 10.0 + x, 10.0 + y, 0.0 + z);
		glVertex3f( 10.0 + x, 10.0 + y, 20.0 + z);
		glVertex3f( 0.0 + x, 10.0 + y, 20.0 + z);
	glEnd();
	static GLfloat par_4[] = { 0.2, 0.2, 0.1, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, par_4);
	glColor3f(0.2f, 0.2f, 0.1f);
	glBegin(GL_POLYGON);
		glVertex3f( 0.0 + x, 0.0 + y, 0.0 + z);
		glVertex3f( 10.0 + x, 0.0 + y, 0.0 + z);
		glVertex3f( 10.0 + x, 10.0 + y, 0.0 + z);
		glVertex3f( 0.0 + x, 10.0 + y, 0.0 + z);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f( 0.0 + x, 0.0 + y, 20.0 + z);
		glVertex3f( 10.0 + x, 0.0 + y, 20.0 + z);
		glVertex3f( 10.0 + x, 10.0 + y, 20.0 + z);
		glVertex3f( 0.0 + x, 10.0 + y, 20.0 + z);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f( 0.0 + x, 0.0 + y, 0.0 + z);
		glVertex3f( 0.0 + x, 0.0 + y, 20.0 + z);
		glVertex3f( 0.0 + x, 10.0 + y, 20.0 + z);
		glVertex3f( 0.0 + x, 10.0 + y, 0.0 + z);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f( 10.0 + x, 0.0 + y, 0.0 + z);
		glVertex3f( 10.0 + x, 0.0 + y, 20.0 + z);
		glVertex3f( 10.0 + x, 10.0 + y, 20.0 + z);
		glVertex3f( 10.0 + x, 10.0 + y, 0.0 + z);
	glEnd();
}
