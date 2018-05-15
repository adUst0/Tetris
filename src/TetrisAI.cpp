#include "TetrisAI.h"
#include "Board.h"
#include "Figure.h"
#include <utility>

static const float Q_HEIGHT    = -3.2;
static const float Q_HOLES     = -4.5;
static const float Q_FULL_ROWS = +3.3;
static const float Q_BUMPINESS = -1.8;

std::pair<int, int> TetrisAI::getBestPosition(Board &board, Figure &fig) {
	const int ROTATIONS = 4;
	const int COLUMNS = board.getCols();

	float score[ROTATIONS][COLUMNS];
	for(int i = 0; i < ROTATIONS; i++)
		for(int j = 0; j < COLUMNS; j++)
			score[i][j] = -99999999;

	Board tempBoard;
	for(int i = 0; i < ROTATIONS; i++) {
		for(int j = 0; j < COLUMNS; j++) {
			fig.setRotation(i);
			tempBoard = board;

			if(!tempBoard.isPossibleMovement(0, j, &fig)) {
				continue;
			}

			int rowIndex = 0;
			while(tempBoard.isPossibleMovement(rowIndex+1, j, &fig)) {
				rowIndex++;
			}
			tempBoard.putFigure(rowIndex, j, &fig);
			score[i][j] = TetrisAI::calculateScore(tempBoard, fig, j);
		}
	}

	int bestColumn = 0;
	int bestRotation = 0;
	float bestScore = score[0][0];

	for(int i = 0; i < ROTATIONS; i++) {
		for(int j = 0; j < COLUMNS; j++) {
			if(score[i][j] > bestScore) {
				bestRotation = i;
				bestColumn = j;
				bestScore = score[i][j];
			}
		}
	}

	return std::make_pair(bestRotation, bestColumn);
}

float TetrisAI::calculateScore(Board &board, Figure &fig, int colIndex) {
	float score = 0;

    score += Q_HEIGHT * getAggregateHeight(board);
	//for(int j = colIndex; j < colIndex + fig.getCols(); j++) {
	//	score += Q_HEIGHT * board.getColHeight(j);
	//}

	score += Q_FULL_ROWS * getFullRows(board);
	score += Q_HOLES * getHolesCount(board);
	score += Q_BUMPINESS * getBumpiness(board);

	return score;
}

int TetrisAI::getAggregateHeight(Board &board) {
	int aggregateHeight = 0;

	for(int j = 0; j < board.getCols(); j++) {
		aggregateHeight += board.getColHeight(j);
	}

	return aggregateHeight;
}

int TetrisAI::getFullRows(Board &board) {
	int fullRows = 0;

	for (int i = 0; i < board.getRows(); i++) {
		bool isRowFull = true;
		for (int j = 0; j < board.getCols(); j++) {
			if (board.isCellEmpty(i, j)) {
				isRowFull = false;
				break;
			}
		}
		if (isRowFull) {
			fullRows++;
		}
	}

	return fullRows;
}

int TetrisAI::getHolesCount(Board &board) {
	int holes = 0;

	for (int j = 0; j < board.getCols(); j++) {
		int firstBlockIndex = board.getRows() - 1;
		for (int i = 0; i < board.getRows(); i++) {
			if (!board.isCellEmpty(i, j)) {
				firstBlockIndex = i;
				break;
			}
		}
		for (int i = firstBlockIndex + 1; i < board.getRows(); i++) {
			if (board.isCellEmpty(i, j)) {
				holes++;
			}
		}
	}
	return holes;
}

int TetrisAI::getBumpiness(Board &board) {
	int bumpiness = 0;

	for(int j = 0; j < board.getCols() - 1; j++) {
		bumpiness += abs(board.getColHeight(j) - board.getColHeight(j + 1));
	}

	return bumpiness;
}
