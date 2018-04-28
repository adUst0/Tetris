#include "Figure.h"
#include <cstring>
#include <algorithm>


char tetrisFigures[7][4][4] = {
{
// Figure 1
{ '1', ' ', ' ', ' ' },
{ '1', ' ', ' ', ' ' },
{ '1', ' ', ' ', ' ' },
{ '1', ' ', ' ', ' ' }
},
{
// Figure 2
{ '2', '2', ' ', ' ' },
{ '2', ' ', ' ', ' ' },
{ '2', ' ', ' ', ' ' },
{ ' ', ' ', ' ', ' ' }
},
{
// Figure 3
{ '3', '3', ' ', ' ' },
{ ' ', '3', ' ', ' ' },
{ ' ', '3', ' ', ' ' },
{ ' ', ' ', ' ', ' ' }
},
{
// Figure 4
{ '4', '4', ' ', ' ' },
{ '4', '4', ' ', ' ' },
{ ' ', ' ', ' ', ' ' },
{ ' ', ' ', ' ', ' ' }
},
{
// Figure 5
{ '5', ' ', ' ', ' ' },
{ '5', '5', ' ', ' ' },
{ ' ', '5', ' ', ' ' },
{ ' ', ' ', ' ', ' ' }
},
{
// Figure 6
{ '6', ' ', ' ', ' ' },
{ '6', '6', ' ', ' ' },
{ '6', ' ', ' ', ' ' },
{ ' ', ' ', ' ', ' ' }
},
{
// Figure 7
{ ' ', '7', ' ', ' ' },
{ '7', '7', ' ', ' ' },
{ '7', ' ', ' ', ' ' },
{ ' ', ' ', ' ', ' ' }
}
};


Figure::Figure(int figureNumber, int rotation = 0) {
	this->rotation = 0;
	this->figureNumber = figureNumber;

	rotation = rotation % 4;
	memcpy(this->grid, tetrisFigures[figureNumber - 1], FIGURE_ROWS * FIGURE_COLS);

	while (this->rotation != rotation) {
		this->rotate();
	}
}

void Figure::rotate(int times) {
	while (times > 0) {
		this->rotation++;
		if (this->rotation == 4) {
			this->rotation = 0;
		}
		// Transpose grid
		for (int i = 0; i < FIGURE_ROWS; i++) {
			for (int j = i; j < FIGURE_COLS; j++) {
				std::swap(this->grid[i][j], this->grid[j][i]);
			}
		}
		// Reverse elements on row order
		for (int i = 0; i < FIGURE_ROWS; i++) {
			for (int j = 0; j < FIGURE_COLS / 2; j++) {
				std::swap(this->grid[i][j], this->grid[i][FIGURE_COLS - j - 1]);
			}
		}

		moveToTopLeftCorner();
		times--;
	}
}

bool Figure::isCellEmpty(int i, int j) const {
	return grid[i][j] == ' ';
}
void Figure::setCellEmpty(int i, int j) {
	grid[i][j] = ' ';
}

char Figure::getFigureNumber() const {
	return this->figureNumber;
}

bool Figure::isFirstColEmpty() const {
	bool isEmpty = true;
	for (int i = 0; i < FIGURE_ROWS; i++) {
		if (!isCellEmpty(i, 0)) {
			isEmpty = false;
			break;
		}
	}
	return isEmpty;
}

bool Figure::isFirstRowEmpty() const {
	bool isEmpty = true;
	for (int i = 0; i < FIGURE_COLS; i++) {
		if (!isCellEmpty(0, i)) {
			isEmpty = false;
			break;
		}
	}
	return isEmpty;
}

void Figure::moveToTopLeftCorner() {
	while (isFirstColEmpty()) {
		for (int i = 0; i < FIGURE_ROWS; i++) {
			for (int j = 1; j < FIGURE_COLS; j++) {
				grid[i][j - 1] = grid[i][j];
				setCellEmpty(i, j);
			}
		}
	}
	while (isFirstRowEmpty()) {
		for (int i = 1; i < FIGURE_ROWS; i++) {
			for (int j = 0; j < FIGURE_COLS; j++) {
				grid[i - 1][j] = grid[i][j];
				setCellEmpty(i - 1, j);
			}
		}
	}
}

int Figure::getRows() const {
	return FIGURE_ROWS;
}

int Figure::getCols() const {
	return FIGURE_COLS;

}