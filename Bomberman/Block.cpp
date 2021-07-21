#include "Libs.h"

Block::Block(float x, float y, std::string textureName, int typeOfBlock) {

	this-> x = x;
	this-> y = y;
	this->textureName = textureName;
	this->typeOfBlock = typeOfBlock; // 0 - Wall, 1 - Box

	sprite.setPosition(this->x, this->y);
}

void Block::render(sf::RenderWindow& window)
{
	texture.setRepeated(true);
	texture.setSmooth(true);

	if (!texture.loadFromFile(textureName)) {
		std::cout << "ERROR::WITH::CLASS::BLOCK" << std::endl;
	}

	sprite.setTexture(texture);
	
	window.draw(sprite);
}

void Block::setBlockScale(int xScale, int yScale){

	sprite.setTextureRect(sf::IntRect((int)this->x, (int)this->y, xScale, yScale));

}

Block::~Block() {



}