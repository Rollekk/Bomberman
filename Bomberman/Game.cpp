#include "Libs.h"

Game::Game(float width, float height, std::string title) {

	this->window.create(sf::VideoMode((unsigned int)width, (unsigned int)height), title);
	this->window.setMouseCursorVisible(false);

	this->state = menuState;

	this->menuStrip.x = 0;
	this->menuStrip.y = 220;
	this->playerOneSpeedUp = 5;
	this->playerOneSpeedRight = 5;
	this->playerOneSpeedDown = 5;
	this->playerOneSpeedLeft = 5;

	this->playerTwoSpeedUp = 5;
	this->playerTwoSpeedRight = 5;
	this->playerTwoSpeedDown = 5;
	this->playerTwoSpeedLeft = 5;

	this->wasLeftPlayerOne = false;
	this->wasRightPlayerOne = false;
	this->wasLeftPlayerTwo = false;
	this->wasRightPlayerTwo = false;
	this->playerOneDMG = false;
	this->playerTwoDMG = false;
	this->bombCol = false;
	this->oneBombCol = true;
	this->isRemis = false;
	this->playerOneRect.left = 0;
	this->playerOneRect.top = 0;
	this->playerOneRect.width = 15;
	this->playerOneRect.height = 18;

	this->playerTwoRect.left = 0;
	this->playerTwoRect.top = 0;
	this->playerTwoRect.width = 15;
	this->playerTwoRect.height = 18;
	this->xComputerDir = 0;
	this->yComputerDir = 0;
	this->hypo = 0;

	this->playerOneScore = 0;
	this->playerTwoScore = 0;

	this->DirOne = IdleOne;
	this->DirTwo = IdleTwo;
	this->vs = vsComputer;
	this->cmp = Idle;

	this->xPlayerOne = 50;
	this->yPlayerOne = 50;
	this->minute = 0;

	this->xPlayerTwo = 970;
	this->yPlayerTwo = 580;
	this->xBombPlayerOne = 0;
	this->yBombPlayerOne = 0;
	this->selectPlayerOne = 1;
	this->xBombPlayerTwo = 0;
	this->yBombPlayerTwo = 0;
	this->selectPlayerTwo = 2;
	this->sliderMusicPosition = 325.f;
	this->sliderSoundPosition = 325.f;
	this->sliderMusicSprite.setPosition(sliderMusicPosition, 217.f);
	this->sliderSoundSprite.setPosition(sliderSoundPosition, 278.f);
	this->oneTimeAudio = false;

	this->musicVolume = 5;
	this->soundVolume = 5;

	this->width = width;
	this->height = height;

	this->Resize.x = this->width;
	this->Resize.y = this->height;

	this->mutedMusic = false;
	this->mutedSound = false;
	this->oneKey = true;
	this->wasGame = false;
	this->stopAudio = true;
	this->placedBombPlayerOne = false;
	this->placedBombPlayerTwo = false;
	this->hoverButtonOne = false;
	this->hoverButtonTwo = false;
	this->hoverButtonThree = false;
	this->hoverButtonFour = false;
	this->sliderMusicClicked = false;
	this->sliderSoundClicked = false;

	this->choice = 0;
	this->onePlayerBomb = 1;
	this->twoPlayerBomb = 1;
	this->playerOneHP = 3;
	this->playerTwoHP = 3;
	this->playerOneDMGStop = 3;
	this->playerTwoDMGStop = 3;

	this->GameLoop();

}
void Game::LoadingFiles(){

	if (state == gameState) {

		if (!background.loadFromFile("Files/Images/platform.png")) {
			std::cout << "ERROR::WITH::TXT::PLATFORM" << std::endl;
		}
		if (!heart.loadFromFile("Files/Images/heart.png")) {
			std::cout << "ERROR::WITH::TXT::HEART" << std::endl;
		}
		if (!emptyHeart.loadFromFile("Files/Images/emptyHeart.png")) {
			std::cout << "ERROR::WITH::TXT::EMPTYHEART" << std::endl;
		}
		if (!font.loadFromFile("Files/Fonts/1980.ttf")) {
			std::cout << "ERROR::WITH::FNT::1980" << std::endl;
		}


	}else if (state == menuState) {

		if (!menu.loadFromFile("Files/Images/Menu.png")) {
			std::cout << "ERROR::WITH::TXT::MENU" << std::endl;
		}
		if (!strip.loadFromFile("Files/Images/Strip.jpg")) {
			std::cout << "ERROR::WITH::TXT::Strip" << std::endl;
		}

		menuSprite.setTexture(menu);
		stripSprite.setTexture(strip);

		stripSprite.setPosition(menuStrip.x, menuStrip.y);

		menuSprite.setScale(
			Resize.x / menuSprite.getLocalBounds().width,
			Resize.y / menuSprite.getLocalBounds().height
		);
		stripSprite.setScale(
			Resize.x / menuSprite.getLocalBounds().width,
			Resize.y / menuSprite.getLocalBounds().height
		);

	}else if (state == optionState) {

		if (!muteMusic.loadFromFile("Files/Images/Block.png")) {
			std::cout << "ERROR::WITH::TXT::Block" << std::endl;
		}
		if (!muteSound.loadFromFile("Files/Images/Block.png")) {
			std::cout << "ERROR::WITH::TXT::Block" << std::endl;
		}
		if (!red.loadFromFile("Files/Images/Red.jpg")) {
			std::cout << "ERROR::WITH::TXT::Black" << std::endl;
		}
		if (!strip.loadFromFile("Files/Images/Strip.jpg")) {
			std::cout << "ERROR::WITH::TXT::Strip" << std::endl;
		}
		if (!option.loadFromFile("Files/Images/Options.png")) {
			std::cout << "ERROR::WITH::TXT::OPTION" << std::endl;
		}
		if (!check.loadFromFile("Files/Images/Check.png")) {
			std::cout << "ERROR::WITH::TXT::CHECK" << std::endl;
		}

		if (!font.loadFromFile("Files/Fonts/1980.ttf")) {
			std::cout << "ERROR::WITH::FNT::1980" << std::endl;
		}

	}
	else if (state == helpState) {

		if (!help.loadFromFile("Files/Images/Help.png")) {
			std::cout << "ERROR::WITH::TXT::HELP" << std::endl;
		}
	}
}

void Game::ComputerEnemy(){

	Computer comp;
	TileMap map;

	if (state == gameState) {
		if (vs == vsComputer) {

			list<int> rowList;
			list<int> colList;

			comp.setPath((int) xPlayerOne,(int)  yPlayerOne,(int)  xPlayerTwo,(int)  yPlayerTwo);

			rowList = comp.getColList();
			colList = comp.getRowList();

			std::list<int>::iterator it = rowList.begin();
			std::list<int>::iterator iti = colList.begin();

			if (it == rowList.end()) {
				xPlayerTwo = xPlayerTwo;
			}
			if (iti == colList.end()) {
				yPlayerTwo = yPlayerTwo;
			}else{

					std::advance(it, 1);
					std::advance(iti, 1);

					float tmp1 = (float) *iti * 51;
					float tmp2 = (float) *it * 51;

					xComputerDir = tmp1 - xPlayerTwo;
					yComputerDir = tmp2 - yPlayerTwo;

					hypo = sqrt(xComputerDir*xComputerDir + yComputerDir * yComputerDir);

					xComputerDir /= hypo;
					yComputerDir /= hypo;

					xPlayerTwo += xComputerDir*playerTwoSpeedLeft * 0.8f;
					yPlayerTwo += yComputerDir*playerTwoSpeedUp * 0.8f;

			}
			if (rowList.size() <= 3 && colList.size() <= 3) {
				if (compBombPlace.getElapsedTime().asSeconds() >= 4.f) {
					if (twoPlayerBomb == 1) {
						twoPlayerBomb = 0;
						placedBombPlayerTwo = true;
						xBombPlayerTwo = xPlayerTwo - 8;
						yBombPlayerTwo = yPlayerTwo - 8;
						bombTwoTime.restart();
						compBombPlace.restart();
					}
				}
				
			}
			if (twoPlayerBomb == 1 && bombCol == true) {
				twoPlayerBomb = 0;
				placedBombPlayerTwo = true;
				bombCol = false;
				xBombPlayerTwo = xPlayerTwo - 16;
				yBombPlayerTwo = yPlayerTwo - 16;
				bombTwoTime.restart();
				compBombPlace.restart();
			}
			if (resetBombCol.getElapsedTime().asSeconds() > 4.1f) {
				oneBombCol = true;
				playerTwoSpeedLeft = 5;
				playerTwoSpeedUp = 5;
				resetBombCol.restart();
			}
		}


	}
}
void Game::GameLoop(){

	while (this->window.isOpen())
	{

		sf::Event event;
		while (this->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->window.close();
			if (event.type == sf::Event::KeyReleased) {
				DirOne = IdleOne;
				DirTwo = IdleTwo;
				oneKey = true;

				if (wasRightPlayerOne) {
					playerOneRect.left = 0;
				}
				if (wasLeftPlayerOne) {
					playerOneRect.left = 240;
				}
				if (wasRightPlayerTwo) {
					playerTwoRect.left = 0;
				}
				if (wasLeftPlayerTwo) {
					playerTwoRect.left = 240;
				}
			}
			if (state == optionState) {
				if (event.type == sf::Event::MouseButtonReleased) {
					sliderMusicClicked = false;
					sliderSoundClicked = false;
					if (sf::Mouse::getPosition(this->window).x > 320) {
						music.pause();
						oneTimeAudio = true;
					}
				}
			}
		}
		this->ComputerEnemy();
		this->Audio();
		this->Input();
		this->Cursor();
		this->Display();
		this->MenuOptions();
		this->LoadingFiles();
		this->SliderCollision();
		this->window.display();

	}
}
void Game::Audio() {

	if (stopAudio) {

		if (!music.openFromFile("Files/Audio/breakout.ogg")) {
			std::cout << "ERROR::WITH::MUSIC::BREAKOUT" << std::endl;
		}
		music.setVolume((float) musicVolume);
		music.play();

		if (!click.loadFromFile("Files/Audio/Click.wav")) {
			std::cout << "ERROR::WITH::AUDIO::CLICK" << std::endl;
		}
		sound.setVolume((float) soundVolume);

		if (!enter.loadFromFile("Files/Audio/Enter.wav")) {
			std::cout << "ERROR::WITH::MUSIC::BREAKOUT" << std::endl;
		}
		stopAudio = false;
	}


}
void Game::Cursor() {

	if (!cursor.loadFromFile("Files/Images/cursor.png")) {
		std::cout << "ERROR::WITH::TXT::PLATFORM" << std::endl;
	}

	cursorSprite.setTexture(cursor);
	cursorSprite.setPosition((float)sf::Mouse::getPosition(this->window).x, (float)sf::Mouse::getPosition(this->window).y);

}
void Game::endGame(){

	if (playerOneHP == 0) {
		stringWinner = "Wygrywa Gracz #2";
		stringScore = "Koncowy wynik: " + std::to_string(playerTwoScore);
		state = endState;
	}
	else if (playerTwoHP == 0) {
		stringWinner = "Wygrywa Gracz #1";
		stringScore = "Koncowy wynik: " + std::to_string(playerOneScore);
		state = endState;
	}
	if (stringMinute == "3") {
		state = endState;
		if (playerOneHP > playerTwoHP) {
			stringWinner = "Wygrywa Gracz #1";
			stringScore = "Koncowy wynik: " + std::to_string(playerOneScore);
		}
		else if (playerTwoHP > playerOneHP) {
			stringWinner = "Wygrywa Gracz #2";
			stringScore = "Koncowy wynik: " + std::to_string(playerTwoScore);
		}
		else if (playerOneHP == playerTwoHP) {
			isRemis = true;
			stringWinner = "Remis!";
			stringScore = "Wynik Gracza #1: " + std::to_string(playerOneScore);
			stringRemis = "Wynik Gracza #2: " + std::to_string(playerTwoScore);
		}
	}
}
void Game::SliderCollision() {
	
	if (sliderMusicClicked) {
		if (sf::Mouse::getPosition(this->window).x <= 315.f) {
			sliderMusicSprite.setPosition(315.f, 217.f);
		}
		else if (sf::Mouse::getPosition(this->window).x >= 665.f) {
			sliderMusicSprite.setPosition(665.f, 217.f);
		}
		else {
			sliderMusicSprite.setPosition((float)sf::Mouse::getPosition(this->window).x, 217.f);
		}
	}
	if (sliderSoundClicked) {
		if (sf::Mouse::getPosition(this->window).x <= 315.f) {
			sliderSoundSprite.setPosition(315.f, 278.f);
		}
		else if (sf::Mouse::getPosition(this->window).x >= 665.f) {
			sliderSoundSprite.setPosition(665.f, 278.f);
		}
		else {
			sliderSoundSprite.setPosition((float)sf::Mouse::getPosition(this->window).x, 278.f);
		}
	}

}
void Game::MusicSlider(){

	if (!sliderMusic.loadFromFile("Files/Images/Slider.png")) {
		std::cout << "ERROR::WITH::TXT::Slider" << std::endl;
	}

	if (sliderMusicSprite.getGlobalBounds().contains((float)sf::Mouse::getPosition(this->window).x, (float)sf::Mouse::getPosition(this->window).y)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			sliderMusicClicked = true;
			sliderMusicPosition = (float)sf::Mouse::getPosition(this->window).x;

			if (sf::Mouse::getPosition(this->window).x <= 320) {
				mutedMusic = true;
			}
			else {
				mutedMusic = false;
				if (sf::Mouse::getPosition(this->window).x <= 500) {
					musicVolume = (sf::Mouse::getPosition(this->window).x / 7) - 43;
					music.setVolume((float)musicVolume);
				}
				else if (sf::Mouse::getPosition(this->window).x > 500) {
					musicVolume = (sf::Mouse::getPosition(this->window).x / 7) - 20;
					music.setVolume((float)musicVolume);
				}
			}
		}
	}

	sliderMusicSprite.setTexture(sliderMusic);

	sliderMusicSprite.setScale(
		Resize.x / optionSprite.getLocalBounds().width,
		Resize.y / optionSprite.getLocalBounds().height
	);
}
void Game::SoundSlider(){

	if (!sliderSound.loadFromFile("Files/Images/Slider.png")) {
		std::cout << "ERROR::WITH::TXT::Slider" << std::endl;
	}

	if (sliderSoundSprite.getGlobalBounds().contains((float)sf::Mouse::getPosition(this->window).x, (float)sf::Mouse::getPosition(this->window).y)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			sliderSoundClicked = true;
			sliderSoundPosition = (float)sf::Mouse::getPosition(this->window).x;

			if (sf::Mouse::getPosition(this->window).x <= 320) {
				mutedSound = true;
			}
			else {
				mutedSound = false;
				if (sf::Mouse::getPosition(this->window).x <= 500) {
					soundVolume = (sf::Mouse::getPosition(this->window).x / 7) - 43;
					sound.setVolume((float)soundVolume);
				}
				else if (sf::Mouse::getPosition(this->window).x > 500) {
					soundVolume = (sf::Mouse::getPosition(this->window).x / 7) - 20;
					sound.setVolume((float)soundVolume);
				}
			}
		}
	}

	sliderSoundSprite.setTexture(sliderSound);

	sliderSoundSprite.setScale(
		Resize.x / optionSprite.getLocalBounds().width,
		Resize.y / optionSprite.getLocalBounds().height
	);

}
void Game::MenuOptions() {

	if (state == menuState) {
		if (choice == 0) {
			state = menuState;
		}
		if (choice == 1) {
			state = gameState;
			music.pause();
			wasGame = true;
		}
		if (choice == 2) {
			state = optionState;
		}
		if (choice == 3) { state = helpState; }
		if (choice == 4) { state = exitState; }
	}
}

void Game::StartGame() {
	
	sf::Sprite playerOneSprite;
	sf::Sprite playerTwoSprite;
	sf::Sprite bombOneSprite;
	sf::Sprite bombTwoSprite;
	sf::Sprite explosionSpriteRight;
	sf::Sprite explosionSpriteLeft;
	sf::Sprite explosionSpriteUp;
	sf::Sprite explosionSpriteDown;
	sf::Sprite explosionTwoSpriteRight;
	sf::Sprite explosionTwoSpriteLeft;
	sf::Sprite explosionTwoSpriteUp;
	sf::Sprite explosionTwoSpriteDown;
	TileMap map;

	if (selectPlayerOne == 1) {
		if (!playerOne.loadFromFile("Files/Images/Player1.png")) {
			std::cout << "ERROR::WITH::TXT::DINOS" << std::endl;
		}
	}
	else if (selectPlayerOne == 2) {
		if (!playerOne.loadFromFile("Files/Images/Player2.png")) {
			std::cout << "ERROR::WITH::TXT::DINOS" << std::endl;
		}
	}
	else if (selectPlayerOne == 3) {
		if (!playerOne.loadFromFile("Files/Images/Player3.png")) {
			std::cout << "ERROR::WITH::TXT::DINOS" << std::endl;
		}
	}
	else if (selectPlayerOne == 4) {
		if (!playerOne.loadFromFile("Files/Images/Player4.png")) {
			std::cout << "ERROR::WITH::TXT::DINOS" << std::endl;
		}
	}

	if (selectPlayerTwo == 1) {
		if (!playerTwo.loadFromFile("Files/Images/Player1.png")) {
			std::cout << "ERROR::WITH::TXT::DINOS" << std::endl;
		}
	}
	else if (selectPlayerTwo == 2) {
		if (!playerTwo.loadFromFile("Files/Images/Player2.png")) {
			std::cout << "ERROR::WITH::TXT::DINOS" << std::endl;
		}
	}
	else if (selectPlayerTwo == 3) {
		if (!playerTwo.loadFromFile("Files/Images/Player3.png")) {
			std::cout << "ERROR::WITH::TXT::DINOS" << std::endl;
		}
	}
	else if (selectPlayerTwo == 4) {
		if (!playerTwo.loadFromFile("Files/Images/Player4.png")) {
			std::cout << "ERROR::WITH::TXT::DINOS" << std::endl;
		}
	}

	playerOneSprite.setTexture(playerOne);
	playerOneSprite.setScale(sf::Vector2f(2.0f, 2.0f));
	playerOneSprite.setPosition(sf::Vector2f(xPlayerOne, yPlayerOne));

	playerTwoSprite.setTexture(playerTwo);
	playerTwoSprite.setScale(sf::Vector2f(2.0f, 2.0f));
	if (vs == vsPlayerTwo) {
		playerTwoSprite.setPosition(sf::Vector2f(xPlayerTwo, yPlayerTwo));
	}
	else if (vs == vsComputer) {
		if (xPlayerTwo > 300) {
			playerTwoSprite.setPosition(sf::Vector2f(xPlayerTwo - 22, yPlayerTwo - 22));
		}
		else {
			playerTwoSprite.setPosition(sf::Vector2f(xPlayerTwo, yPlayerTwo));
		}
	}
	if (!bomb.loadFromFile("Files/Images/Bomb.png")) {
		std::cout << "ERROR::WITH::TXT:BOMBS" << std::endl;
	}

	if (!explosion.loadFromFile("Files/Images/explosion.png")) {
		std::cout << "ERROR::WITH::TXT:EXPLOSION" << std::endl;
	}

	if (!bombTwo.loadFromFile("Files/Images/Bomb2.png")) {
		std::cout << "ERROR::WITH::TXT:BOMBS" << std::endl;
	}

	if (!explosionTwo.loadFromFile("Files/Images/explosion2.png")) {
		std::cout << "ERROR::WITH::TXT:EXPLOSION" << std::endl;
	}
	background.setRepeated(true);
	bckgrnd.setTexture(background);
	bckgrnd.setTextureRect(sf::IntRect(32, 32, 1055, 665));

	bombOneSprite.setTexture(bomb);
	bombOneSprite.setScale(sf::Vector2f(1.8f, 1.8f));
	bombOneSprite.setTextureRect(sf::IntRect(0, 0, 24, 24));
	bombOneSprite.setPosition(xBombPlayerOne, yBombPlayerOne);

	bombTwoSprite.setTexture(bomb);
	bombTwoSprite.setScale(sf::Vector2f(1.8f, 1.8f));
	bombTwoSprite.setTextureRect(sf::IntRect(0, 0, 24, 24));
	bombTwoSprite.setPosition(xBombPlayerTwo, yBombPlayerTwo);

	if (bombTime.getElapsedTime().asSeconds() >= 2.9f) {

		explosionSpriteLeft.setTexture(explosion);
		explosionSpriteRight.setTexture(explosion);
		explosionSpriteUp.setTexture(explosion);
		explosionSpriteDown.setTexture(explosion);

		explosionSpriteLeft.setTextureRect(sf::IntRect(0, 0, 24, 24));
		explosionSpriteRight.setTextureRect(sf::IntRect(0, 0, 24, 24));
		explosionSpriteUp.setTextureRect(sf::IntRect(0, 0, 24, 24));
		explosionSpriteDown.setTextureRect(sf::IntRect(0, 0, 24, 24));

		explosionSpriteLeft.setPosition(xBombPlayerOne + 24, yBombPlayerOne);
		explosionSpriteRight.setPosition(xBombPlayerOne - 24, yBombPlayerOne);
		explosionSpriteUp.setPosition(xBombPlayerOne, yBombPlayerOne + 24);
		explosionSpriteDown.setPosition(xBombPlayerOne, yBombPlayerOne - 24);
	}

	if (bombTwoTime.getElapsedTime().asSeconds() >= 2.9f) {

		explosionTwoSpriteLeft.setTexture(explosionTwo);
		explosionTwoSpriteRight.setTexture(explosionTwo);
		explosionTwoSpriteUp.setTexture(explosionTwo);
		explosionTwoSpriteDown.setTexture(explosionTwo);

		explosionTwoSpriteLeft.setTextureRect(sf::IntRect(0, 0, 24, 24));
		explosionTwoSpriteRight.setTextureRect(sf::IntRect(0, 0, 24, 24));
		explosionTwoSpriteUp.setTextureRect(sf::IntRect(0, 0, 24, 24));
		explosionTwoSpriteDown.setTextureRect(sf::IntRect(0, 0, 24, 24));

		explosionTwoSpriteLeft.setPosition(xBombPlayerTwo + 24, yBombPlayerTwo);
		explosionTwoSpriteRight.setPosition(xBombPlayerTwo - 24, yBombPlayerTwo);
		explosionTwoSpriteUp.setPosition(xBombPlayerTwo, yBombPlayerTwo + 24);
		explosionTwoSpriteDown.setPosition(xBombPlayerTwo, yBombPlayerTwo - 24);

	}

	if (DirOne == IdleOne) {
		if (animationPlayerOne.getElapsedTime().asSeconds() > 0.1f) {
			if (wasRightPlayerOne) {
				playerOneRect.top = 0;
				if (playerOneRect.left == 72) {
					playerOneRect.left = 0;
				}
				else {
					playerOneRect.left += 24;
				}

				animationPlayerOne.restart();
			}
			if (wasLeftPlayerOne) {
				playerOneRect.top = 19;
				if (playerOneRect.left >= 216) {
					playerOneRect.left = 168;
				}
				else {
					playerOneRect.left += 24;
				}

				animationPlayerOne.restart();
			}
		}
	}
	playerOneSprite.setTextureRect(playerOneRect);

	if (DirTwo == IdleTwo || cmp == Idle) {
		if (animationPlayerTwo.getElapsedTime().asSeconds() > 0.1f) {
			if (wasRightPlayerTwo) {
				playerTwoRect.top = 0;
				if (playerTwoRect.left == 72) {
					playerTwoRect.left = 0;
				}
				else {
					playerTwoRect.left += 24;
				}

				animationPlayerTwo.restart();
			}
			if (wasLeftPlayerTwo) {
				playerTwoRect.top = 19;
				if (playerTwoRect.left >= 216) {
					playerTwoRect.left = 168;
				}
				else {
					playerTwoRect.left += 24;
				}

				animationPlayerTwo.restart();
			}
		}
	}
	playerTwoSprite.setTextureRect(playerTwoRect);

	map.openFile();
	for (int i = 0; i < map.loadCounter.x; i++) {
		for (int j = 0; j < map.loadCounter.y; j++) {
			if (map.map[i][j].x != -1 && map.map[i][j].y != -1) {
				map.tiles.setPosition((float)i * 48, (float)j * 48);
				map.tiles.setTextureRect(sf::IntRect(map.map[i][j].x * 48, map.map[i][j].y * 48, 48, 48));
				if (playerOneSprite.getGlobalBounds().intersects(map.tiles.getGlobalBounds())) {
					if (DirOne == UpOne) {
						playerOneSpeedUp = 0;
					}
					if (DirOne == RightOne) {
						playerOneSpeedRight = 0;
					}
					if (DirOne == DownOne) {
						playerOneSpeedDown = 0;
					}
					if (DirOne == LeftOne) {
						playerOneSpeedLeft = 0;
					}

				}
				if (explosionSpriteLeft.getGlobalBounds().intersects(map.tiles.getGlobalBounds()) ||
					explosionSpriteRight.getGlobalBounds().intersects(map.tiles.getGlobalBounds()) ||
					explosionSpriteUp.getGlobalBounds().intersects(map.tiles.getGlobalBounds()) ||
					explosionSpriteDown.getGlobalBounds().intersects(map.tiles.getGlobalBounds())) {
					if (map.map[i][j].x == 1 && map.map[i][j].y == 0) {
						map.map[i][j].x = -1;
						map.map[i][j].y = -1;
						playerOneScore++;
					}
					map.saveFile();
				}
				if (explosionSpriteLeft.getGlobalBounds().intersects(playerOneSprite.getGlobalBounds()) ||
					explosionSpriteRight.getGlobalBounds().intersects(playerOneSprite.getGlobalBounds()) ||
					explosionSpriteUp.getGlobalBounds().intersects(playerOneSprite.getGlobalBounds()) ||
					explosionSpriteDown.getGlobalBounds().intersects(playerOneSprite.getGlobalBounds())){
					playerOneDMG = true;
				}
				if (explosionTwoSpriteLeft.getGlobalBounds().intersects(playerOneSprite.getGlobalBounds()) ||
					explosionTwoSpriteRight.getGlobalBounds().intersects(playerOneSprite.getGlobalBounds()) ||
					explosionTwoSpriteUp.getGlobalBounds().intersects(playerOneSprite.getGlobalBounds()) ||
					explosionTwoSpriteDown.getGlobalBounds().intersects(playerOneSprite.getGlobalBounds())) {
					playerOneDMG = true;
				}

				if (playerTwoSprite.getGlobalBounds().intersects(map.tiles.getGlobalBounds())) {
					if (DirTwo == UpTwo) {
						playerTwoSpeedUp = 0;
					}
					if (DirTwo == RightTwo) {
						playerTwoSpeedRight = 0;
					}
					if (DirTwo == DownTwo) {
						playerTwoSpeedDown = 0;
					}
					if (DirTwo == LeftTwo) {
						playerTwoSpeedLeft = 0;
					}

					if (map.map[i][j].x == 1 && map.map[i][j].y == 0) {
						playerTwoSpeedLeft = 0;
						playerTwoSpeedUp = 0;
						if (oneBombCol) {
							bombCol = true;
							oneBombCol = false;
						}
					}
				}
				if (explosionTwoSpriteLeft.getGlobalBounds().intersects(map.tiles.getGlobalBounds()) ||
					explosionTwoSpriteRight.getGlobalBounds().intersects(map.tiles.getGlobalBounds()) ||
					explosionTwoSpriteUp.getGlobalBounds().intersects(map.tiles.getGlobalBounds()) ||
					explosionTwoSpriteDown.getGlobalBounds().intersects(map.tiles.getGlobalBounds())) {
					if (map.map[i][j].x == 1 && map.map[i][j].y == 0) {
						map.map[i][j].x = -1;
						map.map[i][j].y = -1;
						playerTwoScore++;
					}
					map.saveFile();
				}
				if (vs == vsPlayerTwo) {
					if (explosionTwoSpriteLeft.getGlobalBounds().intersects(playerTwoSprite.getGlobalBounds()) ||
						explosionTwoSpriteRight.getGlobalBounds().intersects(playerTwoSprite.getGlobalBounds()) ||
						explosionTwoSpriteUp.getGlobalBounds().intersects(playerTwoSprite.getGlobalBounds()) ||
						explosionTwoSpriteDown.getGlobalBounds().intersects(playerTwoSprite.getGlobalBounds())) {

						playerTwoDMG = true;
					}
				}
				if (explosionSpriteLeft.getGlobalBounds().intersects(playerTwoSprite.getGlobalBounds()) ||
					explosionSpriteRight.getGlobalBounds().intersects(playerTwoSprite.getGlobalBounds()) ||
					explosionSpriteUp.getGlobalBounds().intersects(playerTwoSprite.getGlobalBounds()) ||
					explosionSpriteDown.getGlobalBounds().intersects(playerTwoSprite.getGlobalBounds())) {

					playerTwoDMG = true;

				}
			}
		}

		if (playerOneSprite.getGlobalBounds().intersects(bombTwoSprite.getGlobalBounds())) {
			if (DirOne == UpOne) {
				playerOneSpeedUp = 0;
			}
			if (DirOne == RightOne) {
				playerOneSpeedRight = 0;
			}
			if (DirOne == DownOne) {
				playerOneSpeedDown = 0;
			}
			if (DirOne == LeftOne) {
				playerOneSpeedLeft = 0;
			}
		}
		if (playerTwoSprite.getGlobalBounds().intersects(bombOneSprite.getGlobalBounds())) {
			if (DirTwo == UpTwo) {
				playerTwoSpeedUp = 0;
			}
			if (DirTwo == RightTwo) {
				playerTwoSpeedRight = 0;
			}
			if (DirTwo == DownTwo) {
				playerTwoSpeedDown = 0;
			}
			if (DirTwo == LeftTwo) {
				playerTwoSpeedLeft = 0;
			}
			if (vs == vsComputer) {
				playerTwoSpeedLeft = 0;
				playerTwoSpeedUp = 0;
			}
		}
	}

	window.draw(bckgrnd);

	if (playerOneDMG){
		playerOneDMG = false;
		playerOneDMGStop -= 1;
		if (playerOneDMGStop >= -1 && playerOneDMGStop < 3) {
			playerOneScore = playerOneScore - 1;
			playerTwoScore = playerTwoScore + 1;
			playerOneHP = 2;
		}
		else if(playerOneDMGStop < -1 && playerOneDMGStop >= -5){
			playerOneScore = playerOneScore - 1;
			playerTwoScore = playerTwoScore + 1;
			playerOneHP = 1;
		}
		else if (playerOneDMGStop < -5) {
			playerOneScore = playerOneScore - 1;
			playerTwoScore = playerTwoScore + 1;
			playerOneHP = 0;
		}
	}

	if (playerTwoDMG) {
		playerTwoDMG = false;
		playerTwoDMGStop -= 1;
		if (playerTwoDMGStop >= -1 && playerTwoDMGStop < 3) {
			playerTwoScore = playerTwoScore - 1;
			playerOneScore = playerOneScore + 1;
			playerTwoHP = 2;
		}
		else if (playerTwoDMGStop < -1 && playerTwoDMGStop >= -6) {
			playerTwoScore = playerTwoScore - 1;
			playerOneScore = playerOneScore + 1;
			playerTwoHP = 1;
		}
		else if(playerTwoDMGStop < -6){
			playerTwoScore = playerTwoScore - 1;
			playerOneScore = playerOneScore + 1;
			playerTwoHP = 0;
		}

	}

	emptyHeartOneSprite.setTexture(emptyHeart);
	playerOneHPSprite.setTexture(heart);
	emptyHeartOneSprite.setScale(sf::Vector2f(2.f, 2.f));
	playerOneHPSprite.setScale(sf::Vector2f(2.f, 2.f));

	emptyHeartTwoSprite.setTexture(emptyHeart);
	playerTwoHPSprite.setTexture(heart);
	emptyHeartTwoSprite.setScale(sf::Vector2f(2.f, 2.f));
	playerTwoHPSprite.setScale(sf::Vector2f(2.f, 2.f));

	endGame();

	if (placedBombPlayerOne == true) {
		window.draw(bombOneSprite);

		if (bombTime.getElapsedTime().asSeconds() >= 3.0f) {

			window.draw(explosionSpriteLeft);
			window.draw(explosionSpriteRight);
			window.draw(explosionSpriteUp);
			window.draw(explosionSpriteDown);

			placedBombPlayerOne = false;
			if (vs == vsComputer) {
				playerTwoSpeedLeft = 5;
				playerTwoSpeedUp = 5;
			}
			bombTime.restart();
			onePlayerBomb = 1;
			xBombPlayerOne = 0;
			yBombPlayerOne = 0;
		}
	}
	if (placedBombPlayerTwo == true) {
		window.draw(bombTwoSprite);

		if (bombTwoTime.getElapsedTime().asSeconds() >= 3.0f) {

			window.draw(explosionTwoSpriteLeft);
			window.draw(explosionTwoSpriteRight);
			window.draw(explosionTwoSpriteUp);
			window.draw(explosionTwoSpriteDown);

			placedBombPlayerTwo = false;
			bombTwoTime.restart();
			twoPlayerBomb = 1;
			xBombPlayerTwo = 0;
			yBombPlayerTwo = 0;
		}
	}

	map.drawMap(this->window);
	window.draw(playerOneSprite);
	window.draw(playerTwoSprite);
	for (int i = 1; i <= 3; i++) {
		emptyHeartOneSprite.setPosition(sf::Vector2f(i * 50 - 40.f, 10.f));
		window.draw(emptyHeartOneSprite);
		emptyHeartTwoSprite.setPosition(sf::Vector2f(i * 50 + 840.f, 630.f));
		window.draw(emptyHeartTwoSprite);
	}
	for (int i = 1; i <= playerOneHP; i++) {
		playerOneHPSprite.setPosition(sf::Vector2f(i*50 - 40.f, 10.f));
		window.draw(playerOneHPSprite);
	}
	for (int i = 1; i <= playerTwoHP; i++) {
		playerTwoHPSprite.setPosition(sf::Vector2f(i*50 + 840.f, 630.f));
		window.draw(playerTwoHPSprite);
	}
	showTimer();
}

void Game::showTimer(){
	if (mainTimer.getElapsedTime().asSeconds() >= 60.f) {
		mainTimer.restart();
		minute++;
	}
	stringTimer = std::to_string((int)mainTimer.getElapsedTime().asSeconds());
	
	stringMinute = std::to_string(minute);

	if (mainTimer.getElapsedTime().asSeconds() <= 10) {
		stringTimer = "0" + stringMinute + ":" + "0" + stringTimer;
	}
	else {
		stringTimer = "0" + stringMinute + ":" + stringTimer;
	}

	timer.setFont(font);
	timer.setCharacterSize(50);
	timer.setFillColor(sf::Color::White);
	timer.setPosition(sf::Vector2f(500.f, -15.f));
	timer.setString(stringTimer);

	window.draw(timer);
}
void Game::Display() {

	this->window.clear();

	if (this->state == menuState) {

		window.clear(sf::Color(238, 239, 225));
		window.draw(stripSprite);
		window.draw(menuSprite);
		window.draw(cursorSprite);
	}
	if (this->state == gameState) {
		StartGame();
	}
	if (this->state == optionState) {

		sf::Sprite playerOneSprite;
		sf::Sprite playerTwoSprite;

		if (selectPlayerOne == 1) {
			if (!playerOne.loadFromFile("Files/Images/Player1.png")) {
				std::cout << "ERROR::WITH::TXT::PLAYER" << std::endl;
			}
		}
		else if (selectPlayerOne == 2) {
			if (!playerOne.loadFromFile("Files/Images/Player2.png")) {
				std::cout << "ERROR::WITH::TXT::PLAYER2" << std::endl;
			}
		}
		else if (selectPlayerOne == 3) {
			if (!playerOne.loadFromFile("Files/Images/Player3.png")) {
				std::cout << "ERROR::WITH::TXT::PLAYER3" << std::endl;
			}
		}
		else if (selectPlayerOne == 4) {
			if (!playerOne.loadFromFile("Files/Images/Player4.png")) {
				std::cout << "ERROR::WITH::TXT::PLAYER3" << std::endl;
			}
		}

		if (selectPlayerTwo == 1) {
			if (!playerTwo.loadFromFile("Files/Images/Player1.png")) {
				std::cout << "ERROR::WITH::TXT::PLAYER" << std::endl;
			}
		}
		else if (selectPlayerTwo == 2) {
			if (!playerTwo.loadFromFile("Files/Images/Player2.png")) {
				std::cout << "ERROR::WITH::TXT::PLAYER2" << std::endl;
			}
		}
		else if (selectPlayerTwo == 3) {
			if (!playerTwo.loadFromFile("Files/Images/Player3.png")) {
				std::cout << "ERROR::WITH::TXT::PLAYER3" << std::endl;
			}
		}
		else if (selectPlayerTwo == 4) {
			if (!playerTwo.loadFromFile("Files/Images/Player4.png")) {
				std::cout << "ERROR::WITH::TXT::PLAYER3" << std::endl;
			}
		}

		optionSprite.setTexture(option);
		stripSprite.setTexture(strip);
		redSprite.setTexture(red);
		muteMusicSprite.setTexture(muteMusic);
		muteSoundSprite.setTexture(muteSound);
		playerOneSprite.setTexture(playerOne);
		playerTwoSprite.setTexture(playerTwo);
		checkSprite.setTexture(check);

		stringMusicVolume = std::to_string(musicVolume);
		stringSoundVolume = std::to_string(soundVolume);


		musicVol.setFont(font);
		musicVol.setCharacterSize(30);
		musicVol.setFillColor(sf::Color::Black);
		musicVol.setPosition(sf::Vector2f(690.f,200.f));
		musicVol.setString(stringMusicVolume);

		soundVol.setFont(font);
		soundVol.setCharacterSize(30);
		soundVol.setFillColor(sf::Color::Black);
		soundVol.setPosition(sf::Vector2f(690.f, 262.f));
		soundVol.setString(stringSoundVolume);

		stripSprite.setPosition(menuStrip.x, menuStrip.y);
		muteMusicSprite.setPosition(725, 205);
		muteSoundSprite.setPosition(725, 266);

		optionSprite.setScale(
			Resize.x / optionSprite.getLocalBounds().width,
			Resize.y / optionSprite.getLocalBounds().height
		);
		stripSprite.setScale(
			Resize.x / optionSprite.getLocalBounds().width,
			Resize.y / optionSprite.getLocalBounds().height
		);
		muteMusicSprite.setScale(
			Resize.x / optionSprite.getLocalBounds().width,
			Resize.y / optionSprite.getLocalBounds().height
		);
		muteSoundSprite.setScale(
			Resize.x / optionSprite.getLocalBounds().width,
			Resize.y / optionSprite.getLocalBounds().height
		);
		checkSprite.setScale(
			Resize.x / optionSprite.getLocalBounds().width,
			Resize.y / optionSprite.getLocalBounds().height
		);

		if (vs == vsComputer) {
			checkSprite.setPosition(sf::Vector2f(515.f, 349.f));
		}
		else if (vs == vsPlayerTwo) {
			checkSprite.setPosition(sf::Vector2f(697.f, 349.f));
		}
		window.clear(sf::Color(238, 239, 225));
		window.draw(optionSprite);
		window.draw(stripSprite);

		window.draw(optionSprite);

		playerTwoSprite.setTextureRect(playerTwoRect);
		playerTwoSprite.setScale(sf::Vector2f(5.0f, 5.0f));
		playerTwoSprite.setPosition(sf::Vector2f(630.0f, 470.0f));

		if (animationPlayerTwo.getElapsedTime().asSeconds() > 0.1f) {
			playerTwoRect.top = 0;
			if (playerTwoRect.left >= 72) {
				playerTwoRect.left = 0;
			}
			else {
				playerTwoRect.left += 24;
			}

			animationPlayerTwo.restart();
		}

		playerOneSprite.setTextureRect(playerOneRect);
		playerOneSprite.setScale(sf::Vector2f(5.0f, 5.0f));
		playerOneSprite.setPosition(sf::Vector2f(380.0f, 470.0f));

		if (animationPlayerOne.getElapsedTime().asSeconds() > 0.1f) {
			playerOneRect.top = 0;
			if (playerOneRect.left >= 72) {
				playerOneRect.left = 0;
			}
			else {
				playerOneRect.left += 24;
			}

			animationPlayerOne.restart();
		}
		if (mutedMusic == true) {
			window.draw(muteMusicSprite);
			music.pause();
			musicVolume = 0;
		}
		else if(oneTimeAudio == true && mutedMusic == false){
			music.play();
			oneTimeAudio = false;
		}
		if (mutedSound == true) {
			window.draw(muteSoundSprite);
			sound.pause();
			soundVolume = 0;
		}
		else if (oneTimeAudio == true && mutedSound == false) {
			sound.play();
			oneTimeAudio = false;
		}

		window.draw(playerOneSprite);
		window.draw(playerTwoSprite);
		window.draw(sliderMusicSprite);
		window.draw(sliderSoundSprite);
		window.draw(musicVol);
		window.draw(soundVol);
		window.draw(checkSprite);
		window.draw(cursorSprite);
	}
	if (this->state == helpState) {

		helpSprite.setTexture(help);
		helpSprite.setScale(
			Resize.x / helpSprite.getLocalBounds().width,
			Resize.y / helpSprite.getLocalBounds().height
		);

		stripSprite.setPosition(menuStrip.x, menuStrip.y);
		window.clear(sf::Color(238, 239, 225));
		window.draw(stripSprite);
		window.draw(helpSprite);
		window.draw(cursorSprite);
	}
	if (this->state == endState) {

		if (!end.loadFromFile("Files/Images/GameOver.png")) {
			std::cout << "ERROR::WITH::TXT::GV" << std::endl;
		}

		winnerText.setFont(font);
		winnerText.setCharacterSize(70);
		winnerText.setFillColor(sf::Color::Black);
		winnerText.setPosition(sf::Vector2f(330.f, 150.f));
		winnerText.setString(stringWinner);

		score.setFont(font);
		score.setCharacterSize(50);
		score.setFillColor(sf::Color::Black);
		score.setPosition(sf::Vector2f(380.f, 220.f));
		score.setString(stringScore);
		
		endSprite.setTexture(end);
		endSprite.setScale(
			Resize.x / endSprite.getLocalBounds().width,
			Resize.y / endSprite.getLocalBounds().height
		);
		stripSprite.setPosition(menuStrip.x, menuStrip.y);
		window.clear(sf::Color(238, 239, 225));

		window.draw(stripSprite);
		window.draw(endSprite);
		window.draw(winnerText);
		window.draw(score);
		if (isRemis) {
			remis.setFont(font);
			remis.setCharacterSize(50);
			remis.setFillColor(sf::Color::Black);
			remis.setPosition(sf::Vector2f(380.f, 270.f));
			remis.setString(stringRemis);
			window.draw(remis);
		}
		window.draw(cursorSprite);
	}
}
void Game::Input() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && state != menuState) {
		state = menuState;
		menuStrip.y = 220;
		choice = 0;
		sound.setBuffer(enter);
		sound.play();
		if (wasGame == true && mutedMusic == false) {
			music.play();
			wasGame = false;
		}
	}

	if (state == exitState) {
		this->window.close();

	}
	else if (state == gameState) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			DirOne = UpOne;
			yPlayerOne -= playerOneSpeedUp;
			if (wasRightPlayerOne) {
				if (playerOneRect.left >= 216) {
					playerOneRect.left = 96;
				}
				else {
					playerOneRect.left += 24;
				}
			}
			else if (wasLeftPlayerOne) {
				if (playerOneRect.left >= 168) {
					playerOneRect.left = 0;
				}
				else {
					playerOneRect.left += 24;
				}

			}

			playerOneSpeedDown = 5;
			playerOneSpeedRight = 5;
			playerOneSpeedLeft = 5;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			DirOne = LeftOne;
			xPlayerOne -= playerOneSpeedLeft;
			wasLeftPlayerOne = true;
			wasRightPlayerOne = false;
			playerOneRect.top = 19;
			if (playerOneRect.left >= 168) {
				playerOneRect.left = 0;
			}
			else {
				playerOneRect.left += 24;
			}
			playerOneSpeedUp = 5;
			playerOneSpeedDown = 5;
			playerOneSpeedRight = 5;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

			yPlayerOne += playerOneSpeedDown;
			DirOne = DownOne;
			if (wasRightPlayerOne) {
				if (playerOneRect.left >= 216) {
					playerOneRect.left = 96;
				}
				else {
					playerOneRect.left += 24;
				}
			}
			else if (wasLeftPlayerOne) {
				if (playerOneRect.left >= 168) {
					playerOneRect.left = 0;
				}
				else {
					playerOneRect.left += 24;
				}
			}
			playerOneSpeedUp = 5;
			playerOneSpeedRight = 5;
			playerOneSpeedLeft = 5;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			DirOne = RightOne;
			xPlayerOne += playerOneSpeedRight;
			wasLeftPlayerOne = false;
			wasRightPlayerOne = true;
			playerOneRect.top = 0;
			if (playerOneRect.left >= 216) {
				playerOneRect.left = 96;
			}
			else {
				playerOneRect.left += 24;
			}
			playerOneSpeedUp = 5;
			playerOneSpeedDown = 5;
			playerOneSpeedLeft = 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if ((oneKey == true) && onePlayerBomb == 1) {
				placedBombPlayerOne = true;
				bombTime.restart();
				oneKey = false;
				onePlayerBomb = 0;
				xBombPlayerOne = xPlayerOne;
				yBombPlayerOne = yPlayerOne + 8;
			}
		}
		if (vs == vsPlayerTwo) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				DirTwo = UpTwo;
				yPlayerTwo -= playerTwoSpeedUp;
				if (wasRightPlayerTwo) {
					if (playerTwoRect.left >= 216) {
						playerTwoRect.left = 96;
					}
					else {
						playerTwoRect.left += 24;
					}
				}
				else if (wasLeftPlayerTwo) {
					if (playerTwoRect.left >= 168) {
						playerTwoRect.left = 0;
					}
					else {
						playerTwoRect.left += 24;
					}

				}
				playerTwoSpeedDown = 5;
				playerTwoSpeedRight = 5;
				playerTwoSpeedLeft = 5;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				DirTwo = LeftTwo;
				xPlayerTwo -= playerTwoSpeedLeft;
				wasLeftPlayerTwo = true;
				wasRightPlayerTwo = false;
				playerTwoRect.top = 19;
				if (playerTwoRect.left >= 168) {
					playerTwoRect.left = 0;
				}
				else {
					playerTwoRect.left += 24;
				}
				playerTwoSpeedUp = 5;
				playerTwoSpeedDown = 5;
				playerTwoSpeedRight = 5;

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				DirTwo = DownTwo;
				yPlayerTwo += playerTwoSpeedDown;
				if (wasRightPlayerTwo) {
					if (playerTwoRect.left >= 216) {
						playerTwoRect.left = 96;
					}
					else {
						playerTwoRect.left += 24;
					}
				}
				else if (wasLeftPlayerTwo) {
					if (playerTwoRect.left >= 168) {
						playerTwoRect.left = 0;
					}
					else {
						playerTwoRect.left += 24;
					}
				}
				playerTwoSpeedUp = 5;
				playerTwoSpeedRight = 5;
				playerTwoSpeedLeft = 5;

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				DirTwo = RightTwo;
				xPlayerTwo += playerTwoSpeedRight;
				wasLeftPlayerTwo = false;
				wasRightPlayerTwo = true;
				playerTwoRect.top = 0;
				if (playerTwoRect.left >= 216) {
					playerTwoRect.left = 96;
				}
				else {
					playerTwoRect.left += 24;
				}
				playerTwoSpeedUp = 5;
				playerTwoSpeedDown = 5;
				playerTwoSpeedLeft = 5;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if ((oneKey == true) && twoPlayerBomb == 1) {
					placedBombPlayerTwo = true;
					bombTwoTime.restart();
					oneKey = false;
					twoPlayerBomb = 0;
					xBombPlayerTwo = xPlayerTwo;
					yBombPlayerTwo = yPlayerTwo + 8;
				}
			}
		}
	}else if (state == menuState) {

		if (sf::Mouse::getPosition(this->window).x > 100 &&
			sf::Mouse::getPosition(this->window).x < 360 &&
			sf::Mouse::getPosition(this->window).y > 220 &&
			sf::Mouse::getPosition(this->window).y < 300) {

			if (!hoverButtonOne) {
				sound.setBuffer(click);
				sound.play();
				hoverButtonOne = true;
			}
			this->menuStrip.y = 220.f;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				mainTimer.restart();
				sound.setBuffer(enter);
				sound.play();
				choice = 1;
			}
		}else { hoverButtonOne = false; }

		if (sf::Mouse::getPosition(this->window).x > 100 &&
			sf::Mouse::getPosition(this->window).x < 360 &&
			sf::Mouse::getPosition(this->window).y > 330 &&
			sf::Mouse::getPosition(this->window).y < 410) {

			if (!hoverButtonTwo) {
				sound.setBuffer(click);
				sound.play();
				hoverButtonTwo = true;
			}
			this->menuStrip.y = 322.f;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

				sound.setBuffer(enter);
				sound.play();
				choice = 2;
			}
		}else { hoverButtonTwo = false; }

		if (sf::Mouse::getPosition(this->window).x > 100 &&
			sf::Mouse::getPosition(this->window).x < 360 &&
			sf::Mouse::getPosition(this->window).y > 440 &&
			sf::Mouse::getPosition(this->window).y < 520) {

			if (!hoverButtonThree) {
				sound.setBuffer(click);
				sound.play();
				hoverButtonThree = true;
			}
			this->menuStrip.y = 442.f;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

				sound.setBuffer(enter);
				sound.play();
				choice = 3;
			}
		}else { hoverButtonThree = false; }

		if (sf::Mouse::getPosition(this->window).x > 100 &&
			sf::Mouse::getPosition(this->window).x < 360 &&
			sf::Mouse::getPosition(this->window).y > 550 &&
			sf::Mouse::getPosition(this->window).y < 630) {

			if (!hoverButtonFour) {
				sound.setBuffer(click);
				sound.play();
				hoverButtonFour = true;
			}
			this->menuStrip.y = 552.f;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

				sound.setBuffer(enter);
				sound.play();
				choice = 4;
			}
		}else { hoverButtonFour = false; }

	}else if (state == optionState) {

		MusicSlider();
		SoundSlider();

		if (sf::Mouse::getPosition(this->window).x > 885 &&
			sf::Mouse::getPosition(this->window).x < 1050 &&
			sf::Mouse::getPosition(this->window).y > 590 &&
			sf::Mouse::getPosition(this->window).y < 640) {

			if (!hoverButtonOne) {
				sound.setBuffer(click);
				sound.play();
				hoverButtonOne = true;
			}
			this->menuStrip.y = 590.f;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sound.setBuffer(enter);
				sound.play();
				state = menuState;
				choice = 0;
				this->menuStrip.y = 220;
			}

		}
		else {
			hoverButtonOne = false;
			this->menuStrip.y = 400.f;
		}
		if (sf::Mouse::getPosition(this->window).x > 690 &&
			sf::Mouse::getPosition(this->window).x < 730 &&
			sf::Mouse::getPosition(this->window).y > 343 &&
			sf::Mouse::getPosition(this->window).y < 383) {

			if (!hoverButtonTwo) {
				sound.setBuffer(click);
				sound.play();
				hoverButtonTwo = true;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sound.setBuffer(enter);
				sound.play();
				vs = vsPlayerTwo;
			}
		}
		else {
			hoverButtonTwo = false;
		}
		if (sf::Mouse::getPosition(this->window).x > 507 &&
			sf::Mouse::getPosition(this->window).x < 547 &&
			sf::Mouse::getPosition(this->window).y > 343 &&
			sf::Mouse::getPosition(this->window).y < 383) {

			if (!hoverButtonThree) {
				sound.setBuffer(click);
				sound.play();
				hoverButtonThree = true;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sound.setBuffer(enter);
				sound.play();
				vs = vsComputer;
			}
		}
		else {
			hoverButtonThree = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (oneKey == true) {
				sound.setBuffer(click);
				sound.play();
				if (selectPlayerOne == 1) {
					selectPlayerOne = 4;
				}
				else {
					selectPlayerOne--;
				}

				oneKey = false;
			}	
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (oneKey == true) {
				sound.setBuffer(click);
				sound.play();
				if (selectPlayerOne == 4) {
					selectPlayerOne = 1;
				}
				else {
					selectPlayerOne++;
				}

				oneKey = false;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (oneKey == true) {
				sound.setBuffer(click);
				sound.play();
				if (selectPlayerTwo == 1) {
					selectPlayerTwo = 4;
				}
				else {
					selectPlayerTwo--;
				}

				oneKey = false;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (oneKey == true) {
				sound.setBuffer(click);
				sound.play();
				if (selectPlayerTwo == 4) {
					selectPlayerTwo = 1;
				}
				else {
					selectPlayerTwo++;
				}

				oneKey = false;
			}
		}

	}else if (state == helpState) {

		if (sf::Mouse::getPosition(this->window).x > 885 &&
			sf::Mouse::getPosition(this->window).x < 1050 &&
			sf::Mouse::getPosition(this->window).y > 590 &&
			sf::Mouse::getPosition(this->window).y < 640) {

			if (!hoverButtonOne) {
				sound.setBuffer(click);
				sound.play();
				hoverButtonOne = true;
			}
			this->menuStrip.y = 590.f;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sound.setBuffer(enter);
				sound.play();
				state = menuState;
				choice = 0;
				this->menuStrip.y = 220;
			}

		}
		else {
			hoverButtonOne = false;
			this->menuStrip.y = 400.f;
		}
	}
	else if (state == endState) {

	if (sf::Mouse::getPosition(this->window).x > 885 &&
		sf::Mouse::getPosition(this->window).x < 1050 &&
		sf::Mouse::getPosition(this->window).y > 590 &&
		sf::Mouse::getPosition(this->window).y < 640) {

		if (!hoverButtonOne) {
			sound.setBuffer(click);
			sound.play();
			hoverButtonOne = true;
		}
		this->menuStrip.y = 590.f;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sound.setBuffer(enter);
			sound.play();
			music.play();
			state = menuState;
			choice = 0;
			this->menuStrip.y = 220;
			isRemis = false;
		}

	}
	else {
		hoverButtonOne = false;
		this->menuStrip.y = 400.f;
	}
	}
}

Game::~Game() {

}