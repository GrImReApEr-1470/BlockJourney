#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "Plate.h"
#include "Player.h"
#include "Shape.h"
#include "Game.h"
#include <string.h>
#include "SOIL/SOIL.h"

using namespace std;
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif



// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f, z=0.0f;
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;

#define unit 10
int FPS = 100;

int start3D = 0;

Game* theGame;
//
GLfloat texpts[2][2][2] = { {{1.0, 1.0},{1.0, 0.0}},{{0.0, 1.0},{0.0, 0.0} } };
#define imageWidth 64
#define imageHeight 64
GLubyte image[3 * imageWidth*imageHeight];
GLuint texture1;

int loading = 0;

void LoadTextureLava(void)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height;

    unsigned char* image = SOIL_load_image("lava_texture.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    //SOIL_free_image_data(image);
    //glBindTexture(GL_TEXTURE_2D, 0);
}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);

	cout<<"ANa are mere";
}
int stop = 0;
void updateFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, updateFunc, 0);
	theGame->update();
}

void keyFunction(int key, int x, int y) {

	theGame->onMove(key, x, y);
	stop = 1;
	glutPostRedisplay();
}

void myinit(void)
{
    GLfloat fogColor[4] = { 0.7, 0.7, 0.7, 1.0 };

    glEnable(GL_FOG);

    glFogfv(GL_FOG_COLOR, fogColor);
        glFogf(GL_FOG_DENSITY, 0.0027);
        glHint(GL_FOG_HINT, GL_DONT_CARE);
        glFogf(GL_FOG_START, 1.0);
        glFogf(GL_FOG_END, 1.0);

    glClearColor(0.7, 0.7, 0.7, 1.0);

}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 200.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle) {

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}


void drawGround(){



	int x = 0;
	int y = 0;
	int z = 0;
	static GLfloat par_2[] = { 1.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, par_2);
	glColor3f(1.0f, 0.0f, 0.0f);
	glEnable(GL_TEXTURE_2D);
	if (loading == 0) {
	LoadTextureLava();
		loading = 1;
	}
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0);glVertex3f( 0.0 + x, 0.0 + y, 0.0 + z);
	glTexCoord2f(0.0, 0.0);	glVertex3f( 150.0+ x, 0.0 + y, 0.0 + z);
	glTexCoord2f(0.0, 1.0);	glVertex3f( 150.0+ x, 0.0 + y, 100.0 + z);
	glTexCoord2f(1.0, 1.0);	glVertex3f( 0.0+ x, 0.0 + y, 100.0 + z);
	glEnd();
	glDisable(GL_TEXTURE_2D);

			glBegin(GL_POLYGON);
				glVertex3f( 0.0 + x, -10.0 + y, 0.0 + z);
				glVertex3f( 150.0 + x, -10.0 + y, 0.0 + z);
				glVertex3f( 150.0 + x, -10.0 + y, 100.0 + z);
				glVertex3f( 0.0 + x, -10.0 + y, 100.0 + z);
			glEnd();
			static GLfloat par_3[] = { 0.4, 0.2, 0.2, 1.0 };
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, par_3);
			glColor3f(0.4f, 0.2f, 0.2f);
			glBegin(GL_POLYGON);
				glVertex3f( 0.0 + x, 0.0 + y, 0.0 + z);
				glVertex3f( 150.0 + x, 0.0 + y, 0.0 + z);
				glVertex3f( 150.0 + x, -10.0 + y, 0.0 + z);
				glVertex3f( 0.0 + x, -10.0 + y, 0.0 + z);
			glEnd();

			glBegin(GL_POLYGON);
				glVertex3f( 0.0 + x, 0.0 + y, 100.0 + z);
				glVertex3f( 150.0 + x, 0.0 + y, 100.0 + z);
				glVertex3f( 150.0 + x, -10.0 + y, 100.0 + z);
				glVertex3f( 0.0 + x, -10.0 + y, 100.0 + z);
			glEnd();

			glBegin(GL_POLYGON);
				glVertex3f( 0.0 + x, 0.0 + y, 0.0 + z);
				glVertex3f( 0.0 + x, 0.0 + y, 100.0 + z);
				glVertex3f( 0.0 + x, -10.0 + y, 100.0 + z);
				glVertex3f( 0.0 + x, -10.0 + y, 0.0 + z);
			glEnd();

			glBegin(GL_POLYGON);
				glVertex3f( 150.0 + x, 0.0 + y, 0.0 + z);
			    glVertex3f( 150.0 + x, 0.0 + y, 100.0 + z);
				glVertex3f( 150.0 + x, -10.0 + y, 100.0 + z);
				glVertex3f( 150.0 + x, -10.0 + y, 0.0 + z);
			glEnd();


}
void processKeys(unsigned char key, int x, int y) {

	switch (key)
	{
		case ' ':
			start3D = 1;
			theGame->start();
			break;

	}
}

void renderScene(void) {
	glClearColor(0.300, 0.140, 0.140, 1.00);
		if (deltaMove)
			computePos(deltaMove);
		if (deltaAngle)
			computeDir(deltaAngle);

		// Clear Color and Depth Buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Reset transformations
		glLoadIdentity();

		gluLookAt(	22.8, 50.0, -58.75,
					23.25, 49.5,  -57.85,
						0.0f, 50.0f,  0.0f);


		float cof[] = {0.6,0.7,0.7};
		float poz[] = { 0, 100, 0, 1.0 };
		glLightfv(GL_LIGHT0,GL_AMBIENT,cof);
		glLightfv(GL_LIGHT0, GL_POSITION, poz);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
			drawGround();


			if (start3D == 1) {
			theGame->display();
			}
			glutPostRedisplay();


			myinit();

		//theGame->display();
		glFlush();
		glutSwapBuffers();
}


int main(int argc, char **argv) {

	theGame = new Game();

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1920,1080);
	glutCreateWindow("Block Journey Project");

	// register callbacks

	glutDisplayFunc(renderScene);

	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutSpecialUpFunc(keyFunction);

	glutKeyboardFunc(processKeys);
	// here are the new entries
	glutIgnoreKeyRepeat(1);
//	glutSpecialUpFunc(releaseKey);



	glutTimerFunc(1000, updateFunc, 0);
	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}


