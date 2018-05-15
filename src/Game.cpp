#include "Game.h"
#include "Board.h"
#include "Figure.h"
#include "GUI.h"
#include "TetrisAI.h"
#include <SFML/Graphics.hpp>

static const float WAIT_TIME_AI = 0.04;
static const float WAIT_TIME_PLAYER = 0.4;

Game::Game(GameMode mode) : gui() {
	this->board = new Board();
	setMode(mode);

	srand(time((time_t*)(0)));

	this->fallingFigure = createNewFigure();
	this->fallingFigureRow = 0;
	this->fallingFigureCol = 0;
	this->nextFigure = createNewFigure();
}

Game::~Game() {
	delete this->board;
	delete this->fallingFigure;
	delete this->nextFigure;
}

bool Game::isPlayerMode() const {
	return this->mode == PLAYER;
	// else this->mode == AI;
}

void Game::setMode(GameMode mode) {
	this->mode = mode;
	if(mode == PLAYER) {
		waitTime = WAIT_TIME_PLAYER;
	}
	else {
		waitTime = WAIT_TIME_AI;
	}
}

void Game::start() {
	sf::Clock clock;
	float timer = 0;

	sf::RenderWindow *window = gui.getPtrToWindow();

	while (window->isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window->close();
			}

			if (event.type == sf::Event::KeyPressed) {

				if(isPlayerMode()) {
					handleMoveFigureEvent(event);
				}

				handleChangeModeEvent(event);
			}
		}

		// Move figure down over time
		if(timer > waitTime) {
			if (board->isPossibleMovement(fallingFigureRow + 1, fallingFigureCol, fallingFigure)) {
				fallingFigureRow++;
			}
			else {
				if (board->isGameOver() || !board->isPossibleMovement(fallingFigureRow, fallingFigureCol, fallingFigure)) {
					break;
				}
				board->putFigure(fallingFigureRow, fallingFigureCol, fallingFigure);
				board->removeFullRows();

				// Get next figure and generate new next figure
				setNextFigureAsCurrent();
				nextFigure = createNewFigure();
			}
			timer = 0;
		}

		drawScene();
	}
}

Figure* Game::createNewFigure() {
	return new Figure(rand() % 7 + 1, 0);
}

void Game::setNextFigureAsCurrent() {
	delete fallingFigure;
	fallingFigure = nextFigure;
	fallingFigureRow = 0;
	if(isPlayerMode()) {
		fallingFigureCol = 0;
	}
	else {
		std::pair<int, int> bestPosition = TetrisAI::getBestPosition(*board, *fallingFigure);
		fallingFigure->setRotation(bestPosition.first);
		fallingFigureCol = bestPosition.second;
	}
}

void Game::moveFigureLeft() {
	if (board->isPossibleMovement(fallingFigureRow, fallingFigureCol - 1, fallingFigure)) {
		fallingFigureCol--;
	}
}

void Game::moveFigureRight() {
	if (board->isPossibleMovement(fallingFigureRow, fallingFigureCol + 1, fallingFigure)) {
		fallingFigureCol++;
	}

}

void Game::moveFigureDown() {
	while (board->isPossibleMovement(fallingFigureRow + 1, fallingFigureCol, fallingFigure)) {
		fallingFigureRow++;
	}
}

void Game::rotateFigure() {
	fallingFigure->rotate();
	if (!board->isPossibleMovement(fallingFigureRow, fallingFigureCol, fallingFigure)) {
		fallingFigure->rotate(3);
	}
}

void Game::drawScene() {
	gui.clearScreen();
	gui.drawBackground();
	gui.drawBoard(this->board);
	if(board->isPossibleMovement(fallingFigureRow, fallingFigureCol, fallingFigure)) {
		gui.drawFigure(fallingFigureCol, fallingFigureRow, fallingFigure);
	}
	gui.drawFigure(15, 7, nextFigure);
	gui.drawFrame();
	gui.drawInstructions();
	gui.updateScreen();
}

void Game::handleMoveFigureEvent(sf::Event &event) {

	if(event.key.code ==  sf::Keyboard::Up) {
		rotateFigure();	
	}
	if(event.key.code ==  sf::Keyboard::Left) {
		moveFigureLeft();	
	}
	if(event.key.code ==  sf::Keyboard::Right) {
		moveFigureRight();	
	}
	if(event.key.code ==  sf::Keyboard::Down) {
		moveFigureDown();	
	}

}
void Game::handleChangeModeEvent(sf::Event &event) {
	if(event.key.code == sf::Keyboard::X) {
		if(isPlayerMode()) {
			setMode(AI);
		}
		else {
			setMode(PLAYER);
		}
	}		
}