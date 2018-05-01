#include "Board.h"
#include "Figure.h"

Board::Board() {
	for (int i = 0; i < getRows(); i++) {
		for (int j = 0; j < getCols(); j++) {
			setCellEmpty(i, j);
		}
	}
}

Board::Board(const Board& other) {
	for (int i = 0; i < getRows(); i++) {
		for (int j = 0; j < getCols(); j++) {
			grid[i][j] = other.grid[i][j];
		}
	}
}


Board& Board::operator=(const Board& other) {
	if(this != &other) {
		for (int i = 0; i < getRows(); i++) {
			for (int j = 0; j < getCols(); j++) {
				grid[i][j] = other.grid[i][j];
			}
		}
	}
	return *this;
}

void Board::reset() {
	for (int i = 0; i < getRows(); i++) {
		for (int j = 0; j < getCols(); j++) {
			setCellEmpty(i, j);
		}
	}
}

int Board::getRows() const {
	return BOARD_ROWS;
}
int Board::getCols() const {
	return BOARD_COLS;
}
int Board::getColHeight(int colIndex) const {
	int colHeight = 0;

	for(int i = getRows() - 1; i >= 0; i--) {
		if(!isCellEmpty(i, colIndex)) {
			colHeight = getRows() - i; // height is reversed RowIndex+1;
		}
	}

	return colHeight;
}

bool Board::isCellEmpty(int i, int j) const {
	return grid[i][j] == FIGURE_FREE_POS;
}
void Board::setCellEmpty(int i, int j) {
	grid[i][j] = FIGURE_FREE_POS;
}

bool Board::isGameOver() const {
	int hasFilledCell = false;
	for (int j = 0; j < getCols(); j++) {
		if (!isCellEmpty(0, j)) {
			hasFilledCell = true;
			return hasFilledCell;
		}
	}
	return hasFilledCell;
}

bool Board::isRowFull(int rowIndex) const {
	bool retVal = true;
	for (int j = 0; j < getCols(); j++) {
		if (isCellEmpty(rowIndex, j)) {
			retVal = false;
			return retVal;
		}
	}
	return retVal;
}
void Board::removeRow(int rowIndex) {
	for (int i = rowIndex; i > 0; i--) {
		for (int j = 0; j < getCols(); j++) {
			grid[i][j] = grid[i - 1][j];
		}
	}
	for (int j = 0; j < getCols(); j++) {
		setCellEmpty(0, j);
	}
}
int Board::removeFullRows() {
	int removedRows = 0;
	for (int i = 0; i < getRows(); i++) {
		if (isRowFull(i)) {
			removeRow(i);
			removedRows++;
		}
	}
	return removedRows;
}

bool Board::isPossibleMovement(int rowIndex, int colIndex, Figure *fallingFigure) const {
	int retVal = true;

	if (rowIndex < 0 || rowIndex >= getRows() || colIndex < 0 || colIndex >= getCols()) {
		retVal = false;
		return retVal;
	}

	for (int i1 = rowIndex, i2 = 0; i1 < rowIndex + FIGURE_ROWS; i1++, i2++) {
		for (int j1 = colIndex, j2 = 0; j1 < colIndex + FIGURE_COLS; j1++, j2++) {

			// Check if index is out of bounds
			if (i1 >= getRows() || j1 >= getCols()) {
				if (!fallingFigure->isCellEmpty(i2, j2)) {
					retVal = false;
					return retVal;
				}
			}

			// Check for collision wit other figure
			if (!fallingFigure->isCellEmpty(i2, j2) && !this->isCellEmpty(i1, j1)) {
				retVal = false;
				return retVal;
			}
		}
	}

	return retVal;
}

void Board::putFigure(int rowIndex, int colIndex, Figure *fallingFigure) {
	for (int i1 = rowIndex, i2 = 0; i1 < rowIndex + FIGURE_ROWS && i1 < getRows(); i1++, i2++) {
		for (int j1 = colIndex, j2 = 0; j1 < colIndex + FIGURE_COLS && j1 < getCols(); j1++, j2++) {
			if (!fallingFigure->isCellEmpty(i2, j2)) {
				grid[i1][j1] = fallingFigure->getFigureNumber() + '0';
			}
		}
	}
}

void Board::removeFigure(int rowIndex, int colIndex, Figure *fallingFigure) {
	for (int i1 = rowIndex, i2 = 0; i1 < rowIndex + FIGURE_ROWS && i1 < getRows(); i1++, i2++) {
		for (int j1 = colIndex, j2 = 0; j1 < colIndex + FIGURE_COLS && j1 < getCols(); j1++, j2++) {
			if (!fallingFigure->isCellEmpty(i2, j2)) {
				setCellEmpty(i1, j1);
			}
		}
	}
}

int Board::getFigureNumberAtPos(int i, int j) {
	if(isCellEmpty(i, j)) {
		return -1;
	}

	return grid[i][j] - '0';
}
