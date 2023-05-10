#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <bits/stdc++.h>
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
#include <thread>
#include <unistd.h>
#endif
	
void play_audio(string);
bool playMusic = false;
bool isMute = false;

// CAMERA COORDINATES
GLdouble eyeX = 22.8;
GLdouble eyeY = 50.0;
GLdouble eyeZ = -58.75; 
GLdouble centerX = 23.25;
GLdouble centerY = 49.5;
GLdouble centerZ = -57.85;
GLdouble upX = 0;
GLdouble upY = 50.0;
GLdouble upZ = 0;
int currentCam = 0;

// Saving current window size
int currWidth = 1920;
int currHeight = 1080;
// Whether in-game or on title screen
int WIDTH = 640/2;
int HEIGHT = 480/2;
bool title = true;			//for any of the below menu pages, this will be true
bool mainMenu = true; 		//for main-menu
bool instr = false;			//for instructions screen
bool creds = false;			//for credits screen
bool exitScreen = false;	//for exit screen
bool exitPrompt = false;	//for exit prompt
bool endProg = false;
bool vicScreen = false;		//for victory screen

#define unit 10
#define BITS 8

int FPS = 100;

int start3D = 0;

Game* theGame;
//
GLfloat texpts[2][2][2] = { {{1.0, 1.0},{1.0, 0.0}},{{0.0, 1.0},{0.0, 0.0} } };
#define imageWidth 64
#define imageHeight 64
//GLubyte image[3 * imageWidth*imageHeight];
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

    unsigned char* image = SOIL_load_image("textures/lava_texture.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
}

void timer(int value) {
	if (value == 0)
		return;
	glutPostRedisplay();
	glutTimerFunc(1000, timer, value-1);
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
		glLoadIdentity();
	}
	if (title || vicScreen || exitPrompt)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-1*WIDTH, WIDTH, -1*HEIGHT, HEIGHT, -1.0f, 1.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}

// void computePos(float deltaMove) {

// 	x += deltaMove * lx * 0.1f;
// 	z += deltaMove * lz * 0.1f;
// }

// void computeDir(float deltaAngle) {

// 	angle += deltaAngle;
// 	lx = sin(angle);
// 	lz = -cos(angle);
// }


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
		if ((title || vicScreen) && (!exitPrompt)){
		title = false;
		mainMenu = false;
		creds = false;
		instr = false;
		vicScreen = false;
		start3D = 1;
		theGame->start();
		}
	}
	else if (key == 'I' || key == 'i')
	{
		if (!exitPrompt)
		{
			title = true;
			mainMenu = false;
			creds = false;
			instr = true;
			vicScreen = false;
		}
		glutPostRedisplay();
	}
	else if (key == 'Q' || key == 'q')
	{
		exitPrompt = true;
		glutPostRedisplay();
	}
	else if (key == 'C' || key == 'c')
	{
		if (!exitPrompt)
		{
			title = true;
			mainMenu = false;
			creds = true;
			instr = false;
			vicScreen = false;
		}
		glutPostRedisplay();
	}
	else if (key == 'V' || key == 'v')
	{
		// vicScreen = true;
		// theGame->resetGame();
		if (!exitPrompt && !title && !vicScreen)
		{
			currentCam = (currentCam+1)%2;
			if (currentCam == 0)
			{
				eyeX = 22.8;
				eyeY = 50.0;
				eyeZ = -58.75; 
				centerX = 23.25;
				centerY = 49.5;
				centerZ = -57.85;
				upX = 0;
				upY = 50.0;
				upZ = 0;
			}
			else if (currentCam == 1)
			{
				eyeX = 70.8;
				eyeY = 130.0;
				eyeZ = 0.75;  
				centerX = 70.8;
				centerY = 0.5;
				centerZ = 45.85;
				upX = 0;
				upY = 10.0;
				upZ = 0;
			}
		}
		glutPostRedisplay();
	}
	else if (key == 27)
	{
		theGame->resetGame();
		title = true;
		mainMenu = true;
		creds = false;
		instr = false;
		vicScreen = false;
		start3D = 0;
		loading = 0;
		glutPostRedisplay();
	}
	else if (key == 's' || key == 'S')
	{
		isMute = (!isMute);
		playMusic = false;
	}
	else if (key == 'y' || key == 'Y')
	{
		if (exitPrompt)
		{
			title = true;
			mainMenu = false;
			creds = false;
			instr = false;
			exitPrompt = false;
			exitScreen = true;
			vicScreen = false;
			glutPostRedisplay();
		}
	}
	else if (key == 'n' || key == 'N')
	{
		if (exitPrompt)
		{
			exitPrompt = false;
			glutPostRedisplay();
		}
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
    unsigned char* image = SOIL_load_image(str.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
}

void exitAnimation(int value)
{

}

void titleScreen(void){
	if (vicScreen)
		return;

	glClearColor(0.300, 0.140, 0.140, 1.00);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	if (mainMenu)
	{
		glEnable(GL_TEXTURE_2D);
		LoadTextureTitle("textures/game_title.jpg");
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
		char heading5[] = "Press Q to Quit the game";
		for (int i = 0; i<strlen(heading5); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading5[i]);
		
		
	}
	else if (creds){

		glEnable(GL_TEXTURE_2D);
		LoadTextureTitle("textures/credits.jpg");
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
		LoadTextureTitle("textures/instructions.jpg");
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
		char heading3[] = "Player can even press V to toggle camera angles.";
		for (int i = 0; i<strlen(heading3); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading3[i]);
		glRasterPos3f(-170, -60, 0);
		char heading4[] = "The game ends when the block is standing upright over the hole in the maze.";
		for (int i = 0; i<strlen(heading4); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading4[i]);
	}
	else if (exitScreen)
	{
		glEnable(GL_TEXTURE_2D);
		LoadTextureTitle("textures/thanks.jpg");
		glBegin(GL_POLYGON);
		glTexCoord2f(1.0, 0.0);glVertex3f( -320, -240.0, 0.0);
		glTexCoord2f(0.0, 0.0);glVertex3f( 320, -240.0, 0.0);
		glTexCoord2f(0.0, 1.0);glVertex3f( 320, 240.0, 0.0);
		glTexCoord2f(1.0, 1.0);glVertex3f( -320, 240.0, 0.0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		endProg = true;
	}
}

void victoryScreen(int value)
{
	//cout << value <<endl;
	if (!vicScreen)
		return;
	glClearColor(0, 0, 0, 1.00);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	double p = ((double)rand()) / RAND_MAX;
	int s = value%2;
	if (s != 0)
		LoadTextureTitle("textures/victory1.jpg");
	else
		LoadTextureTitle("textures/victory2.jpg");
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0);glVertex3f( -WIDTH, -HEIGHT, 0.0);
	glTexCoord2f(0.0, 0.0);glVertex3f( WIDTH, -HEIGHT, 0.0);
	glTexCoord2f(0.0, 1.0);glVertex3f( WIDTH, HEIGHT, 0.0);
	glTexCoord2f(1.0, 1.0);glVertex3f( -WIDTH, HEIGHT, 0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	glutPostRedisplay();
	glutTimerFunc(25, victoryScreen, value+1);
}

void exitPromptScreen()
{
	glClearColor(0, 0, 0, 1.00);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPointSize(10);
	glColor3f(1,1,1);
	glBegin(GL_LINE_LOOP);
	glVertex3i(-160, 120, -0.9);
	glVertex3i(160, 120, -0.9);
	glVertex3i(160, -120, -0.9);
	glVertex3i(-160, -120, -0.9);
	glEnd();
	glPointSize(5);
	glColor3f(1,1,1);
	glBegin(GL_LINE_LOOP);
	glVertex3i(-157, 117, -0.9);
	glVertex3i(157, 117, -0.9);
	glVertex3i(157, -117, -0.9);
	glVertex3i(-157, -117, -0.9);
	glEnd();

	//glColor3f(0,0,0);
	glRasterPos3f(-48, 30, 0);
	char heading1[] = "Do you want to quit the game?";
	for (int i = 0; i<strlen(heading1); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading1[i]);

	
	glRasterPos3f(-65, -30, 0);
	char heading2[] = "(Y)es";
	for (int i = 0; i<strlen(heading2); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading2[i]);

	glRasterPos3f(45, -30, 0);
	char heading3[] = "(N)o";
	for (int i = 0; i<strlen(heading3); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading3[i]);


	
}

void renderScene(void) {
	if((!playMusic) && (!isMute))
	{
		std::thread audio_thread(play_audio, "music/wrong-place.mp3");
    	audio_thread.detach();
	}
	changeSize(currWidth, currHeight);
	if (vicScreen)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glutTimerFunc(100, victoryScreen, 0);
	}
	else if (exitPrompt)
	{
		exitPromptScreen();
		glutPostRedisplay();
	}
	else if (!title){
		glClearColor(0.300, 0.140, 0.140, 1.00);
		// if (deltaMove)
		// 	computePos(deltaMove);
		// if (deltaAngle)
		// 	computeDir(deltaAngle);

		// Clear Color and Depth Buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Reset transformations
		glLoadIdentity();

		gluLookAt(eyeX, eyeY, eyeZ, 
				  centerX, centerY, centerZ, 
               	  upX, upY, upZ);


		float cof[] = {0.6,0.7,0.7};
		float poz[] = { 0, 100, 0, 1.0 };
		glLightfv(GL_LIGHT0,GL_AMBIENT,cof);
		glLightfv(GL_LIGHT0, GL_POSITION, poz);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		drawGround();

		if (start3D == 1) 
		{
			theGame->display();
		}
		if (theGame->gameStatus == 100)
		{
			theGame->resetGame();
			vicScreen = true;
		}
		glutPostRedisplay();


		myinit();
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		if (endProg)
		{
			sleep(4);
			exit(2);
		}
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
	srand(time(0));

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1920,1080);
	glutCreateWindow("Block Journey Project");

	// register callbacks

	glutDisplayFunc(renderScene);

	glutReshapeFunc(changeSize);
	//glutIdleFunc(renderScene);
    

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


