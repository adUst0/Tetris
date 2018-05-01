#pragma once

#include "Board.h"
#include "Figure.h"
#include "GUI.h"

enum GameMode{PLAYER, AI};

class Game
{
private:
	Board *board;

	GameMode mode;
	float waitTime;

	Figure *fallingFigure;
	int fallingFigureRow;
	int fallingFigureCol;
	Figure *nextFigure;

	GUI gui;

	void moveFigureLeft();
	void moveFigureRight();
	void moveFigureDown();
	void rotateFigure();

	void setMode(GameMode mode);
	bool isPlayerMode() const;

	Figure* createNewFigure();
	void setNextFigureAsCurrent();

	void handleMoveFigureEvent(sf::Event &event);
	void handleChangeModeEvent(sf::Event &event);

	void drawScene();
public:
	Game(GameMode mode = PLAYER);
	~Game();

	void start();
};
