/*
 * Square.cpp
 *
 *  Created on: May 14, 2020
 *      Author: gabriel
 */

#include "Plate.h"
#include "SOIL/SOIL.h"
#define imageWidth3 64
#define imageHeight3 64



void LoadTextureLava3(void)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height;
    unsigned char* image = SOIL_load_image("texture.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    //SOIL_free_image_data(image);
    //glBindTexture(GL_TEXTURE_2D, 0);
}


void Plate::spawn() {

	static GLfloat par_1[] = { 0.9, 0.9, 0.9, 1.0 };
	 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, par_1);

	// Placa
		glColor3f(0.9f, 0.9f, 0.4f);
		glEnable(GL_TEXTURE_2D);
		if (loadingState == 0) {
		LoadTextureLava3();
		loadingState = 1;
		}
		//glNormal3f(0.0, 1.0, 0.0);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.2, 0.0);glVertex3f( 0.0 + x, 0.1 + y, 0.0 + z);
		glTexCoord2f(0.0, 0.0);glVertex3f( 10.0+ x, 0.1 + y, 0.0 + z);
		glTexCoord2f(0.0, 0.2);glVertex3f( 10.0+ x, 0.1 + y, 10.0 + z);
		glTexCoord2f(0.3, 0.2);glVertex3f( 0.0+ x, 0.1 + y, 10.0 + z);
		glEnd();
		glBegin(GL_POLYGON);
		glTexCoord2f(0.2, 0.0);glVertex3f( 0.0 + x, 2.1 + y, 0.0 + z);
		glTexCoord2f(0.0, 0.0);glVertex3f( 10.0 + x, 2.1 + y, 0.0 + z);
		glTexCoord2f(0.0, 0.2);glVertex3f( 10.0 + x, 2.1 + y, 10.0 + z);
		glTexCoord2f(0.2, 0.2);glVertex3f( 0.0 + x, 2.1 + y, 10.0 + z);
		//glEnd();

		static GLfloat par_2[] = { 0.3, 0.3, 0.3, 1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, par_2);
		glColor3f(0.3f, 0.3f, 0.3f);
		glBegin(GL_POLYGON);
		glTexCoord2f(1.0, 0.0);glVertex3f( 0.0 + x, 0.0 + y, 0.0 + z);
		glTexCoord2f(0.0, 0.0);glVertex3f( 10.0 + x, 0.0 + y, 0.0 + z);
		glTexCoord2f(0.0, 1.0);glVertex3f( 10.0 + x, 2.0 + y, 0.0 + z);
		glTexCoord2f(1.0, 1.0);glVertex3f( 0.0 + x, 2.0 + y, 0.0 + z);
		glEnd();

		glBegin(GL_POLYGON);
		glTexCoord2f(1.0, 0.0);glVertex3f( 0.0 + x, 0.0 + y, 10.0 + z);
		glTexCoord2f(0.0, 0.0);glVertex3f( 10.0 + x, 0.0 + y, 10.0 + z);
		glTexCoord2f(0.0, 1.0);glVertex3f( 10.0 + x, 2.0 + y, 10.0 + z);
		glTexCoord2f(1.0, 1.0);glVertex3f( 0.0 + x, 2.0 + y, 10.0 + z);
		glEnd();

		glBegin(GL_POLYGON);
		glTexCoord2f(1.0, 0.0);glVertex3f( 0.0 + x, 0.0 + y, 0.0 + z);
		glTexCoord2f(0.0, 0.0);glVertex3f( 0.0 + x, 0.0 + y, 10.0 + z);
		glTexCoord2f(0.0, 1.0);glVertex3f( 0.0 + x, 2.0 + y, 10.0 + z);
		glTexCoord2f(1.0, 1.0);glVertex3f( 0.0 + x, 2.0 + y, 0.0 + z);
		glEnd();

		glBegin(GL_POLYGON);
		glTexCoord2f(1.0, 0.0);glVertex3f( 10.0 + x, 0.0 + y, 0.0 + z);
		glTexCoord2f(0.0, 0.0);  glVertex3f( 10.0 + x, 0.0 + y, 10.0 + z);
		glTexCoord2f(0.0, 1.0);glVertex3f( 10.0 + x, 2.0 + y, 10.0 + z);
		glTexCoord2f(1.0, 1.0);glVertex3f( 10.0 + x, 2.0 + y, 0.0 + z);
		glEnd();
		glDisable(GL_TEXTURE_2D);

}


Plate::Plate() {

}

Plate::~Plate() {

}

void Plate::update() {
}
