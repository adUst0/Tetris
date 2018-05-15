#pragma once
#include <SFML/Graphics.hpp>
#include "Figure.h"
#include "Board.h"

class GUI {
private:
	sf::RenderWindow window;

	sf::Texture backgroundTexture;
	sf::Texture frameTexture;
	sf::Texture blockTexture;

	sf::Sprite background;
	sf::Sprite frame;
	sf::Sprite block;
public:
	GUI();

	void drawBackground();
	void drawFrame();
	void drawFigure(int posx, int posy, Figure *fig);
	void drawBoard(Board *board);
	void drawInstructions();
	void clearScreen();
	void updateScreen();

	sf::RenderWindow* getPtrToWindow();
};