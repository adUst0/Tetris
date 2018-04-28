#pragma once

#include "Board.h"
#include "Figure.h"
#include "GUI.h"
//#include "TetrisAI.h"

enum Mode { PLAYER = 0, AI = 1 };

class Game
{
protected:
	Board *board;
	Mode mode;

	Figure *fallingFigure;
	int fallingFigureRow;
	int fallingFigureCol;
	Figure *nextFigure;

	GUI gui;
public:
	Game(Mode mode = PLAYER);
	virtual ~Game();

	void start();

	Figure* createNewFigure();
	void getNewFallingFigure();

	void moveFigureLeft();
	void moveFigureRight();
	void moveFigureDown();
	void rotateFigure();

	void drawScene();
};