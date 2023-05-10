#include "Shape.h"
#include "Player.h"
#include "Plate.h"
#include <stdio.h>
using namespace std;
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <ao/ao.h>
#include <mpg123.h>
#include<thread>
float const unit = 10.0;
#include "Game.h"

void thread_audio(string);
Shape *shape;
Player player(0, 2, 0);
Plate plate1(0, 0, 0);
Plate plate2(unit, 0, 0);

Plate finishPlate;
Shape *playerShape;

Plate plates[30];

#define START 0
#define GAME_OVER -1
#define LEVEL1 1
#define LEVEL2 2
#define LEVEL3 3
#define LEVEL4 4


int dead = 0;

bool playsplosh = true;

int level = 1;

static int gameStatus = START;
void play_terminal_audio(string);
Game::Game()
{
	// TODO Auto-generated constructor stub
}

void Game::onMove(int key, int x, int y)
{

	if (dead != 1)
		player.onMove(key, x, y);
}

void Game::update()
{
}

void Game::level1()
{

	glPushMatrix();
	shape = &player;
	// glTranslatef(0, 0, 0);

	shape->spawn();

	int matrice[15][10] = {
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 2, 1, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

	// shape->setY(20);

	// glTranslatef(0, 0, 0);
	glPopMatrix();
	// shape = &plate2;
	// shape->spawn();

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 10; j++)
		{

			if (matrice[i][j] == 1)
			{

				shape = &plates[i];
				shape->setX(i * 10);
				shape->setZ(j * 10);
				//			glEnable(GL_TEXTURE_2D);
				//			LoadTexturePlate();
				shape->spawn();
				//			glDisable(GL_TEXTURE_2D);
			}
		}
	}

	shape = &player;

	cout << "X PLAYER index : " << shape->getX()  << endl;
	cout << "Z PLAYER index: " << shape->getZ()  << endl;
	int player_i = shape->getX() / 10;
	int player_j = shape->getZ() / 10;

	if (matrice[player_i][player_j] == 2 && player.temp_pos==0)
	{
		dead = 1;
		cout << "FINISH" << endl;
		if (shape->getY() > -18)
			shape->setY(shape->getY() - 0.1);
		else
		{
			dead = 0;
			gameStatus = LEVEL2;
			shape->setX(0);
			shape->setY(0);
			shape->setZ(0);
		}
	}

	// if(player.temp_pos==1 && (matrice[player_i-1][player_j] == 0))

	if ((player.temp_pos==1 && (matrice[player_i+1][player_j] == 0)) ||
	 (player.temp_pos==2 && (matrice[player_i][player_j+1] == 0)) ||
	 (matrice[player_i][player_j] == 0 || 
	 shape->getX() < 0 || 
	 shape->getZ() < 0 || 
	 shape->getZ() > 90 || 
	 shape->getX() > 140))
	{   
		cout << "GAME OVER";
		if(playsplosh)
		{
        	thread_audio("splosh.mp3");
        	playsplosh = false;
        }

		if (shape->getY() > -20.4)
		{   
			dead = 1;
			shape->setY(shape->getY() - 0.1);
		}
		else {
			level = 1;
			shape = &player;
			gameStatus = GAME_OVER;
			shape->setZ(0);
			shape->setX(0);
			shape->setY(2) ;
			dead = 0;
		}
	}
}

void Game::level2() {
    
	glPushMatrix();
	shape = &player;
	// glTranslatef(0, 0, 0);
	shape->spawn();

	int matrice[15][10] = {
		{1, 0, 0, 0, 0, 0, 0, 0, 1, 2},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
		{0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
		{0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 1, 0, 0, 1, 1, 1, 1},
		{0, 0, 0, 1, 0, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 0, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
		glPopMatrix();

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (matrice[i][j] == 1)
			{
				shape = &plates[i];
				shape->setX(i * 10);
				shape->setZ(j * 10);
				shape->spawn();
			}
		}
	}

	shape = &player;

	cout << "X PLAYER index : " << shape->getX() / 10 << endl;
	cout << "Z PLAYER index : " << shape->getZ() / 10 << endl;

	int player_i = shape->getX() / 10;
	int player_j = shape->getZ() / 10;

	if (matrice[player_i][player_j] == 2 && player.temp_pos == 0)
	{
		dead = 1;

		cout << "FINISH" << endl;
		if (shape->getY() > -18)
			shape->setY(shape->getY() - 0.1);
		else
		{
			dead = 0;
			gameStatus = LEVEL3;
			shape->setX(0);
			shape->setY(0);
			shape->setZ(0);
		}
	}

	if ((player.temp_pos==1 && (matrice[player_i+1][player_j] == 0)) ||
	 (player.temp_pos==2 && (matrice[player_i][player_j+1] == 0)) ||
	 (matrice[player_i][player_j] == 0 || 
	 shape->getX() < 0 || 
	 shape->getZ() < 0 || 
	 shape->getZ() > 90 || 
	 shape->getX() > 140))
	{  
		cout << "GAME OVER";
		if(playsplosh)
		{
        	thread_audio("splosh.mp3");
        	playsplosh = false;
        }


		if (shape->getY() > -20.4)
		{
			dead = 1;
			shape->setY(shape->getY() - 0.1);
		}
		else
		{
			level = 2;
			gameStatus = GAME_OVER;
			shape->setY(2);
			dead = 0;
		}
	}
}

void Game::level3()
{

	glPushMatrix();
	shape = &player;
	// glTranslatef(0, 0, 0);
	shape->spawn();

	int matrice[15][10] = {
		{1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 0, 0, 0, 1},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
		{1, 1, 1, 1, 0, 0, 0, 1, 1, 1},
		{0, 1, 1, 1, 0, 0, 0, 1, 1, 1},
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
		{0, 0, 0, 0, 1, 2, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 0, 0, 0}};
	glPopMatrix();

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (matrice[i][j] == 1)
			{
				shape = &plates[i];
				shape->setX(i * 10);
				shape->setZ(j * 10);
				shape->spawn();
			}
		}
	}

	shape = &player;

	cout << "X PLAYER index : " << shape->getX() / 10 << endl;
	cout << "Z PLAYER index: " << shape->getZ() / 10 << endl;

	int player_i = shape->getX() / 10;
	int player_j = shape->getZ() / 10;

	if (matrice[player_i][player_j] == 2 && player.temp_pos == 0)
	{
		dead = 1;

		cout << "FINISH" << endl;
		if (shape->getY() > -18)
			shape->setY(shape->getY() - 0.1);
		else
		{
			dead = 0;
			gameStatus = LEVEL4;
			shape->setX(0);
			shape->setY(0);
			shape->setZ(0);
		}
	}


	if ((player.temp_pos==1 && (matrice[player_i+1][player_j] == 0)) ||
	 (player.temp_pos==2 && (matrice[player_i][player_j+1] == 0)) ||
	 (matrice[player_i][player_j] == 0 || 
	 shape->getX() < 0 || 
	 shape->getZ() < 0 || 
	 shape->getZ() > 90 || 
	 shape->getX() > 140))
	{   
		cout << "GAME OVER";
		if(playsplosh)
		{
        	thread_audio("splosh.mp3");
        	playsplosh = false;
        }

		if (shape->getY() > -20.4)
		{
			dead = 1;
			shape->setY(shape->getY() - 0.1);
		}
		else
		{
			level = 3;
			gameStatus = GAME_OVER;
			shape->setY(2);
			dead = 0;
		}
	}
}

void Game::level4()
{

	glPushMatrix();
	shape = &player;
	// glTranslatef(0, 0, 0);
	shape->spawn();

	int matrice[15][10] = {
		{1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 1, 2, 1, 1, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 1, 0, 0, 0, 0}};
	glPopMatrix();

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (matrice[i][j] == 1)
			{
				shape = &plates[i];
				shape->setX(i * 10);
				shape->setZ(j * 10);
				shape->spawn();
			}
		}
	}

	shape = &player;

	cout << "X PLAYER index : " << shape->getX() / 10 << endl;
	cout << "Z PLAYER index: " << shape->getZ() / 10 << endl;

	int player_i = shape->getX() / 10;
	int player_j = shape->getZ() / 10;

	if (matrice[player_i][player_j] == 2 && player.temp_pos == 0)
	{
		dead = 1;

		cout << "FINISH" << endl;
		if (shape->getY() > -18)
			shape->setY(shape->getY() - 0.1);
		else
		{
			dead = 0;
			gameStatus = START;
			shape->setX(0);
			shape->setY(0);
			shape->setZ(0);
		}
	}

	if ((player.temp_pos==1 && (matrice[player_i+1][player_j] == 0)) ||
	 (player.temp_pos==2 && (matrice[player_i][player_j+1] == 0)) ||
	 (matrice[player_i][player_j] == 0 || 
	 shape->getX() < 0 || 
	 shape->getZ() < 0 || 
	 shape->getZ() > 90 || 
	 shape->getX() > 140))
	{   
		cout << "GAME OVER";
		if(playsplosh)
		{
        	thread_audio("splosh.mp3");
        	playsplosh = false;
        }


		if (shape->getY() > -20.4)
		{
			dead = 1;
			shape->setY(shape->getY() - 0.1);
		}
		else
		{
			level = 4;
			gameStatus = GAME_OVER;
			shape->setY(2);
			dead = 0;
		}
	}
}
bool winsound[4] {false};
void Game::display()
{

	switch (gameStatus)
	{
	case START:
		// this->start();
		break;

	case LEVEL1:
	    winsound[0] = true;
		this->level1();
		break;

	case LEVEL2:
	    if(winsound[0])
	    	thread_audio("win.mp3");
	    winsound[0] = false;
	    winsound[1] = true;
		shape = &player;
		this->level2();
		break;

	case LEVEL3:
		if(winsound[1])
	    	thread_audio("win.mp3");
	    winsound[1] = false;
	    winsound[2] = true;
		shape = &player;

		this->level3();
		break;

	case LEVEL4:
	    if(winsound[2])
	    	thread_audio("win.mp3");
	    winsound[2] = false;
	    winsound[3] = true;
		shape = &player;

		this->level4();
		break;

	case GAME_OVER:

		playsplosh = true;
		gameStatus = level;
		shape = &player;
		shape->setX(0);
		shape->setZ(0);
		player.pos = -1;
		player.temp_pos = -1;
		break;
	}
}
void Game::start()
{
	gameStatus = LEVEL1;
}

Game::~Game()
{
	// TODO Auto-generated destructor stub
}
void thread_audio(string name)
{
	std::thread audio_thread(play_terminal_audio, name);
    audio_thread.detach();
}
void play_terminal_audio(string audioFile)
{   
    
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
 
        mpg123_volume(mh, 1.0f);
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
    	char *p =(char *)buffer;
    	while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
    	{   
        	ao_play(dev, p, done);
    	}
	
    /* clean up */
    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
}