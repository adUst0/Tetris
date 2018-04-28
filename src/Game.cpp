#include "Game.h"
#include "Board.h"
#include "Figure.h"
#include "GUI.h"
#include <SFML/Graphics.hpp>

static const float WAIT_TIME = 0.4;

Game::Game(Mode mode) : gui() {
	this->board = new Board();

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

void Game::start() {
	sf::Clock clock;
	float timer=0;

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
				switch(event.key.code) {
					case sf::Keyboard::Up:
						rotateFigure();
						break;
					case sf::Keyboard::Left:
						moveFigureLeft();
						break;
					case sf::Keyboard::Right:
						moveFigureRight();
						break;
					case sf::Keyboard::Down:
						moveFigureDown();
						break;
					default:
						break;
				}
			}
		}

		// Move figure down over time
		if(timer > WAIT_TIME) {
			if (board->isPossibleMovement(fallingFigureRow + 1, fallingFigureCol, fallingFigure)) {
				fallingFigureRow++;
			}
			else {
				if (board->isGameOver() || !board->isPossibleMovement(fallingFigureRow, fallingFigureCol, fallingFigure)) {
					break;
				}
				board->putFigure(fallingFigureRow, fallingFigureCol, fallingFigure);
				board->removeFullRows();
				getNewFallingFigure();
				this->nextFigure = createNewFigure();
			}
			timer = 0;
		}
	
		drawScene();
	}
}

Figure* Game::createNewFigure() {
	return new Figure(rand() % 7 + 1, 0);
}

void Game::getNewFallingFigure() {
	delete this->fallingFigure;
	this->fallingFigure = this->nextFigure;
	fallingFigureRow = 0;
	fallingFigureCol = 0;
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
	gui.updateScreen();
}