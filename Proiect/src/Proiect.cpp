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
#include <ao/ao.h>
#include <mpg123.h>
#include<thread>
#endif

void play_audio(string);
bool playMusic = false;
bool isMute = false;
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
// Saving current window size
int currWidth = 1920;
int currHeight = 1080;
// Whether in-game or on title screen
int WIDTH = 640/2;
int HEIGHT = 480/2;
bool title = true;		//for any of the below menu pages, this will be true
bool mainMenu = true; 	//for main-menu
bool instr = false;		//for instructions screen
bool creds = false;		//for credits screen

#define unit 10
#define BITS 8

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

	if (!title)
	{
		theGame->onMove(key, x, y);
		stop = 1;
	}
	else
	{
		//some code if necessary
	}
	glutPostRedisplay();
}

void myinit(void)
{
    GLfloat fogColor[4] = { 0.7, 0.7, 0.7, 1.0 };

    glEnable(GL_FOG);

    glFogfv(GL_FOG_COLOR, fogColor);
        glFogf(GL_FOG_DENSITY, 0.0027);
        glHint(GL_FOG_HINT, GL_DONT_CARE);
        glFogf(GL_FOG_START, 0.1);
        glFogf(GL_FOG_END, 1.0);

    glClearColor(0.7, 0.7, 0.7, 1.0);

}

void changeSize(int w, int h) {
	currWidth = w;
	currHeight = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (!title)
	{
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
	else
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-1*WIDTH, WIDTH, -1*HEIGHT, HEIGHT, -1.0f, 1.0f);
		glMatrixMode(GL_MODELVIEW);
	}
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

	if (key == ' ')
	{
		
		title = false;
		mainMenu = false;
		creds = false;
		instr = false;
		start3D = 1;
		theGame->start();
	}
	else if (key == 'I' || key == 'i')
	{
		title = true;
		mainMenu = false;
		creds = false;
		instr = true;
		glutPostRedisplay();
	}
	else if (key == 'C' || key == 'c')
	{
		title = true;
		mainMenu = false;
		creds = true;
		instr = false;
		glutPostRedisplay();
	}
	else if (key == 'Q' || key == 'q')
	{
		// function for smooth exiting of the game
	}
	else if (key == 27)
	{
		title = true;
		mainMenu = true;
		creds = false;
		instr = false;
		glutPostRedisplay();
	}
	else if (key == 's' || key == 'S')
	{
		isMute = (!isMute);
		playMusic = false;
	}
}

void LoadTextureTitle(string str)
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
    unsigned char* image = SOIL_load_image(str.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
}


void titleScreen(void){
	glClearColor(0.300, 0.140, 0.140, 1.00);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (mainMenu)
	{
		glEnable(GL_TEXTURE_2D);
		LoadTextureTitle("game_title.jpg");
		glBegin(GL_POLYGON);
		glTexCoord2f(1.0, 0.0);glVertex3f( -100, 150.0, 0.0);
		glTexCoord2f(0.0, 0.0);glVertex3f( 120, 150.0, 0.0);
		glTexCoord2f(0.0, 1.0);glVertex3f( 120, 190.0, 0.0);
		glTexCoord2f(1.0, 1.0);glVertex3f( -100, 190.0, 0.0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		
		glRasterPos3f(-70, 00, 0);
		char heading1[] = "Press Spacebar to start the game";
		for (int i = 0; i<strlen(heading1); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading1[i]);
		glRasterPos3f(-70, -20, 0);
		char heading2[] = "Press I to read instruction to the game";
		for (int i = 0; i<strlen(heading2); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading2[i]);
		glRasterPos3f(-70, -40, 0);
		char heading3[] = "Press C to see the credits";
		for (int i = 0; i<strlen(heading3); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading3[i]);
		glRasterPos3f(-70,-60, 0);
		char heading4[] = "Press Esc to return to the main screen at any time";
		for (int i = 0; i<strlen(heading4); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading4[i]);
		glRasterPos3f(-70,-80, 0);
		char heading5[] = "Press Q to return to Quit the game";
		for (int i = 0; i<strlen(heading5); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading5[i]);
		
		
	}
	else if (creds){

		glEnable(GL_TEXTURE_2D);
		LoadTextureTitle("credits.jpg");
		glBegin(GL_POLYGON);
		glTexCoord2f(1.0, 0.0);glVertex3f( -100, 150.0, 0.0);
		glTexCoord2f(0.0, 0.0);glVertex3f( 100, 150.0, 0.0);
		glTexCoord2f(0.0, 1.0);glVertex3f( 100, 190.0, 0.0);
		glTexCoord2f(1.0, 1.0);glVertex3f( -100, 190.0, 0.0);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		glRasterPos3f(-70, 00, 0);
		char heading1[] = "Chaitanya Manohar Giri (20BCS034)";
		for (int i = 0; i<strlen(heading1); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading1[i]);
		glRasterPos3f(-70, -20, 0);
		char heading2[] = "Harshal Ram Dube (20BCS052)";
		for (int i = 0; i<strlen(heading2); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading2[i]);
		glRasterPos3f(-70, -40, 0);
		char heading3[] = "Prathamesh P Pai (20BCS103)";
		for (int i = 0; i<strlen(heading3); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading3[i]);
		glRasterPos3f(-70,-60, 0);
		char heading4[] = "Samuel Mathew (20BCS116)";
		for (int i = 0; i<strlen(heading4); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading4[i]);
	}
	else if (instr)
	{
		glEnable(GL_TEXTURE_2D);
		LoadTextureTitle("instructions.jpg");
		glBegin(GL_POLYGON);
		glTexCoord2f(1.0, 0.0);glVertex3f( -100, 150.0, 0.0);
		glTexCoord2f(0.0, 0.0);glVertex3f( 95, 150.0, 0.0);
		glTexCoord2f(0.0, 1.0);glVertex3f( 95, 190.0, 0.0);
		glTexCoord2f(1.0, 1.0);glVertex3f( -100, 190.0, 0.0);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		glRasterPos3f(-170, 00, 0);
		char heading1[] = "The objective of the game is to move the block along the maze.";
		for (int i = 0; i<strlen(heading1); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading1[i]);
		glRasterPos3f(-170, -20, 0);
		char heading2[] = "Player can use the arrow keys to move the block in 4 directions or press Esc to return to the main screen.";
		for (int i = 0; i<strlen(heading2); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading2[i]);
		glRasterPos3f(-170, -40, 0);
		char heading3[] = "The game ends when the block is standing upright over the hole in the maze.";
		for (int i = 0; i<strlen(heading3); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading3[i]);
	}
}

void renderScene(void) {
	if((!playMusic) && (!isMute))
	{
		std::thread audio_thread(play_audio, "wrong-place.mp3");
    	audio_thread.detach();
	}
	changeSize(currWidth, currHeight);
	if (!title){
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
	}
	else
	{
		titleScreen();
	}
	//theGame->display();
	glFlush();
	glutSwapBuffers();
}


void play_audio(string audioFile)
{   
	playMusic = true;
    mpg123_handle *mh;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;

    int driver;
    ao_device *dev;

    ao_sample_format format;
    int channels, encoding;
    long rate;

    /* initializations */
    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));
    

    /* open the file and get the decoding format */
    while(1)
    {   

    	mpg123_open(mh, &audioFile[0]);
    	mpg123_getformat(mh, &rate, &channels, &encoding);

    	/* set the output format and open the output device */
    	format.bits = mpg123_encsize(encoding) * 8;
    	format.rate = rate;
    	format.channels = channels;
    	format.byte_format = AO_FMT_NATIVE;
    	format.matrix = 0;
    	dev = ao_open_live(driver, &format, NULL);

    	/* decode and play */
        if(isMute)
        	mpg123_volume(mh, 0.0f);
        else
        	mpg123_volume(mh,0.5f);
    	char *p =(char *)buffer;
    	while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
    	{   

    		if(isMute)
        	mpg123_volume(mh, 0.0f);
       		else
        	mpg123_volume(mh,0.5f);
        	ao_play(dev, p, done);
    	}
	}
    /* clean up */
    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
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


