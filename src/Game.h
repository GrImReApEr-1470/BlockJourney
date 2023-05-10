
#ifndef GAME_H_
#define GAME_H_
#include <string>
#include <iostream>

class Game
{
public:
	Game();
	int gameStatus;
	int dead;
	void onMove(int key, int x, int y);
	void update();
	void display();
	void start();
	void level1();
	void level2();
	void level3();
	void level4();
	void setGameStatus(int x) {
		this->gameStatus = x;
	}
	void resetGame();
	virtual ~Game();
};

#endif /* GAME_H_ */
