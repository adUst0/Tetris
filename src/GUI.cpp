#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "GUI.h"
#include "Figure.h"
#include "Board.h"

static const int BLOCK_SIZE_PX       = 34;
static const int BOARD_INITIAL_POS_X = 102;
static const int BOARD_INITIAL_POS_Y = 68;
static const int WINDOW_WIDTH        = 850;
static const int WINDOW_HEIGHT       = 816;
static const std::string PROGRAM_NAME("Tetris");
static const std::string IMG_FOLDER("resources/");

GUI::GUI() 
	:window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), PROGRAM_NAME) 
{
	backgroundTexture.loadFromFile(IMG_FOLDER + "background.png");
	frameTexture.loadFromFile(IMG_FOLDER + "frame.png");
	blockTexture.loadFromFile(IMG_FOLDER + "tiles.png");

	background.setTexture(backgroundTexture);
	frame.setTexture(frameTexture);
	block.setTexture(blockTexture);
}

void GUI::drawBackground() {
	window.draw(background);
}

void GUI::drawFrame() {
	window.draw(frame);
}

void GUI::drawFigure(int posx, int posy, Figure *fig) {
	block.setTextureRect(sf::IntRect(fig->getFigureNumber()*BLOCK_SIZE_PX,0,BLOCK_SIZE_PX,BLOCK_SIZE_PX));

	for(int i = 0; i < fig->getRows(); i++) {
		for(int j = 0; j < fig->getRows(); j++) {
			if(!fig->isCellEmpty(i, j)) {
				block.setPosition((posx + j)*BLOCK_SIZE_PX, (posy + i)*BLOCK_SIZE_PX);
				block.move(BOARD_INITIAL_POS_X, BOARD_INITIAL_POS_Y); // moves the block by the given offset 
				window.draw(block);
			}
		}
	}
}

void GUI::drawBoard(Board *board) {
	for(int i = 0; i < board->getRows(); i++) {
		for(int j = 0; j < board->getCols(); j++) {
			if(!board->isCellEmpty(i, j)) {
				block.setPosition(j*BLOCK_SIZE_PX, i*BLOCK_SIZE_PX);
				block.move(BOARD_INITIAL_POS_X, BOARD_INITIAL_POS_Y); // moves the block by the given offset
				int figNumber = board->getFigureNumberAtPos(i, j);
				block.setTextureRect(sf::IntRect(figNumber*BLOCK_SIZE_PX, 0 , BLOCK_SIZE_PX, BLOCK_SIZE_PX)); //TODO
				window.draw(block);
			}
		}
	}
}

void GUI::drawInstructions() {
	sf::Font font;
	font.loadFromFile("resources/sansation.ttf");

	std::string instructions = 
		std::string("Move: Left/Right arrow\n") +
		std::string("Slam: Down arrow\n") +
		std::string("Rotate: Up arrow\n") +
		std::string("Switch between Single\nplayer or AI: X");
	
	sf::Text info(instructions, font);
	info.setCharacterSize(22);
	info.setFillColor(sf::Color::Black);
	info.setPosition(530, 580);

	window.draw(info);
}

void GUI::clearScreen() {
	window.clear(sf::Color::White);
}

void GUI::updateScreen() {
	window.display();
}

sf::RenderWindow* GUI::getPtrToWindow() {
	return &(this->window);
}