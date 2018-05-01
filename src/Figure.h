#pragma once
//   1   2     3    4   5    6      7
//   --------------------------------
//   1   22   33   44   5    7     8 
//   1   2     3   44   56   77   88 
//   1   2     3         6   7    8  
//   1   
static const int FIGURE_ROWS      = 4;
static const int FIGURE_COLS      = 4;
static const char FIGURE_FREE_POS = ' ';

class Figure {
public:
	Figure(int figureNumber, int rotation);

	void rotate(int times = 1);
	void setRotation(int rotation);
	bool isCellEmpty(int i, int j) const;
	void setCellEmpty(int i, int j);
	char getFigureNumber() const;

	int getRows() const;
	int getCols() const;
private:
	char grid[FIGURE_ROWS][FIGURE_COLS];
	int rotation;
	int figureNumber;

	bool isFirstColEmpty() const;
	bool isFirstRowEmpty() const;
	void moveToTopLeftCorner();
};