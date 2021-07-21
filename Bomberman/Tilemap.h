#pragma once

#include "Libs.h"

class TileMap{
public:

	sf::Texture tileTexture;
	sf::Sprite tiles;

	sf::Vector2i map[100][100];
	sf::Vector2i loadCounter = sf::Vector2i(0, 0);

	std::string tileLocation;

	void openFile() {

		std::ifstream openfile("Files/Images/Map.txt");

		if (openfile.is_open()) {
			openfile >> tileLocation;
			tileTexture.loadFromFile(tileLocation);
			tiles.setTexture(tileTexture);
			
			while (!openfile.eof()) {

				std::string str;
				openfile >> str;

				char x = str[0], y = str[2];
				if (!isdigit(x) || !isdigit(y)) {
					map[loadCounter.x][loadCounter.y] = sf::Vector2i(-1, -1);
				}
				else{
					map[loadCounter.x][loadCounter.y] = sf::Vector2i(x - '0', y - '0');
				}
				if (openfile.peek() == '\n') {
					loadCounter.x = 0;
					loadCounter.y++;
				}
				else {
					loadCounter.x++;
				}
			}
			loadCounter.y++;		
		}
	}
	void saveFile() {
		
		std::ofstream savefile("Files/Images/Map.txt");
		
		savefile << tileLocation << '\n';

		for (int i = 0; i < loadCounter.y; i++) {
			for (int j = 0; j < loadCounter.x; j++) {
				
				if (map[j][i].x == -1) {
					savefile << "x";
				}
				else {
					savefile << map[j][i].x;
				}
				savefile << ",";
				if (map[j][i].y == -1) {
					savefile << "x";
				}
				else {
					savefile << map[j][i].y;
				}
				if (j < loadCounter.x - 1) {
					savefile << " ";
				}
			}
			if (i < loadCounter.y - 1) {
				savefile << "\n";
			}
		}
		

	}

	void drawMap(sf::RenderWindow& window) {

		for (int i = 0; i < loadCounter.x; i++) {
			for (int j = 0; j < loadCounter.y; j++) {
				if (map[i][j].x != -1 && map[i][j].y != -1) {
					tiles.setPosition((float)i * 48, (float)j * 48);
					tiles.setTextureRect(sf::IntRect(map[i][j].x * 48, map[i][j].y * 48, 48, 48));
					window.draw(tiles);
				}

			}
		}
	}

};