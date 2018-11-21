#pragma once
#include "Figure.h"

#define BOARD_ROWS 20
#define BOARD_COLS 10

class Board {
public:
	Board();
	Board(const Board& other);
	Board& operator=(const Board& other) ;

	int getRows() const;
	int getCols() const;
	int getColHeight(int colIndex) const;

	bool isCellEmpty(int i, int j) const;
	void setCellEmpty(int i, int j);

	void reset();

	bool isGameOver() const;

	bool isRowFull(int rowIndex) const;
	void removeRow(int rowIndex);
	int removeFullRows();

	bool isPossibleMovement(int rowIndex, int colIndex, Figure *fallingFigure) const;
	void putFigure(int rowIndex, int colIndex, Figure *fallingFigure);
	void removeFigure(int rowIndex, int colIndex, Figure *fallingFigure);

	int getFigureNumberAtPos(int i, int j);
private:
	char grid[BOARD_ROWS][BOARD_COLS];
};