#pragma once

#include "Libs.h"

class Block {
	
public:
	Block(float x, float y, std::string textureName, int typeOfBlock);
	~Block();

	float x;
	float y;
	std::string textureName;
	int typeOfBlock;

	sf::RenderWindow window;
	sf::Texture texture;
	sf::Sprite sprite;

	void render(sf::RenderWindow& window);
	void setBlockScale(int xScale, int yScale);

private:



};