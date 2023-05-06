/*
 * Game.cpp
 *
 *  Created on: May 19, 2020
 *      Author: gabriel
 */

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

float const unit = 10.0;

#include "Game.h"
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

static int gameStatus = START;

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

	cout << "X PLAYER index : " << shape->getX() / 10 << endl;
	cout << "Z PLAYER index: " << shape->getZ() / 10 << endl;
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
	// Facut toate cazurile pentru level 1
	if (matrice[player_i][player_j] == 0)

	{
		cout << "GAME OVER";

		//		if (shape->getZ() > -20)
		//			shape->setZ(shape->getZ() - 0.1);
		if (shape->getY() > -20.4)
		{
			dead = 1;
			shape->setY(shape->getY() - 0.1);
		}
		else {
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
	// Facut toate cazurile pentru level 1
	if (matrice[player_i][player_j] == 0)

	{
		cout << "GAME OVER";

		//		if (shape->getZ() > -20)
		//			shape->setZ(shape->getZ() - 0.1);
		if (shape->getY() > -20.4)
		{
			dead = 1;
			shape->setY(shape->getY() - 0.1);
		}
		else
		{
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
		{1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
		{1, 0, 1, 1, 1, 1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 1, 0, 0, 1, 0},
		{1, 0, 1, 1, 0, 1, 0, 1, 1, 0},
		{1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
		{1, 0, 0, 1, 1, 1, 1, 1, 2, 1},
		{1, 1, 1, 1, 0, 0, 0, 1, 1, 1},
		{1, 1, 1, 1, 0, 0, 0, 0, 1, 0},
		{1, 0, 0, 1, 0, 1, 0, 0, 0, 0},
		{1, 0, 0, 1, 1, 1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
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
	// Facut toate cazurile pentru level 1

	if (matrice[player_i][player_j] == 0)

	{
		cout << "GAME OVER";

		//		if (shape->getZ() > -20)
		//			shape->setZ(shape->getZ() - 0.1);
		if (shape->getY() > -20.4)
		{
			dead = 1;
			shape->setY(shape->getY() - 0.1);
		}
		else
		{
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
	// Facut toate cazurile pentru level 1
	if (matrice[player_i][player_j] == 0)

	{
		cout << "GAME OVER";

		//		if (shape->getZ() > -20)
		//			shape->setZ(shape->getZ() - 0.1);
		if (shape->getY() > -20.4)
		{
			dead = 1;
			shape->setY(shape->getY() - 0.1);
		}
		else
		{
			gameStatus = GAME_OVER;
			shape->setY(2);
			dead = 0;
		}
	}
}

void Game::display()
{

	switch (gameStatus)
	{
	case START:
		// this->start();
		break;

	case LEVEL1:
		this->level1();
		break;

	case LEVEL2:
		shape = &player;
		this->level2();
		break;

	case LEVEL3:
		shape = &player;

		this->level3();
		break;

	case LEVEL4:
		shape = &player;

		this->level4();
		break;

	case GAME_OVER:
		gameStatus = START;
		shape = &player;
		shape->setX(0);
		shape->setZ(0);
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
