#pragma once
#include "Board.h"
#include "Figure.h"
#include <iostream>

class TetrisAI
{
	TetrisAI();

	static float calculateScore(Board &board, Figure &fig, int colIndex);

	static int getAggregateHeight(Board &board);
	static int getFullRows(Board &board);
	static int getHolesCount(Board &board);
	static int getBumpiness(Board &board);
public:
	static std::pair<int, int> getBestPosition(Board &board, Figure &fig);
};

