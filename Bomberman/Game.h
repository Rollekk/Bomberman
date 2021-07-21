#pragma once

#include "Libs.h"

class Game
{

public:
	Game(float width, float height, std::string title);
	~Game();

	enum State{ menuState = 0, optionState = 1, helpState = 2,  exitState = 3, gameState = 4, endState = 5 };
	enum Vs{ vsComputer = 0, vsPlayerTwo = 1};

	enum PlayerOneDir { IdleOne , LeftOne, RightOne, UpOne, DownOne};
	enum PlayerTwoDir { IdleTwo, LeftTwo , RightTwo, UpTwo, DownTwo};
	
	enum ComputerDir {Left, Right, Up, Down, Idle};

	PlayerOneDir DirOne;
	PlayerTwoDir DirTwo;

	State state;
	Vs vs;
	ComputerDir cmp;

	sf::RenderWindow window;
	sf::Vector2f menuStrip;
	sf::Music music;

	sf::Texture menu;
	sf::Texture strip;
	sf::Texture playerOne;
	sf::Texture playerTwo;
	sf::Texture background;
	sf::Texture bomb;
	sf::Texture bombTwo;
	sf::Texture explosion;
	sf::Texture explosionTwo;
	sf::Texture option;
	sf::Texture red;
	sf::Texture muteMusic;
	sf::Texture muteSound;
	sf::Texture help;
	sf::Texture cursor;
	sf::Texture sliderMusic;
	sf::Texture sliderSound;
	sf::Texture heart;
	sf::Texture emptyHeart;
	sf::Texture check;
	sf::Texture end;

	sf::Sprite emptyHeartOneSprite;
	sf::Sprite emptyHeartTwoSprite;
	sf::Sprite playerOneHPSprite;
	sf::Sprite playerTwoHPSprite;
	sf::Sprite sliderMusicSprite;
	sf::Sprite sliderSoundSprite;
	sf::Sprite cursorSprite;
	sf::Sprite helpSprite;
	sf::Sprite optionSprite;
	sf::Sprite redSprite;
	sf::Sprite muteMusicSprite;
	sf::Sprite muteSoundSprite;
	sf::Sprite bckgrnd;
	sf::Sprite bombOneSprite;
	sf::Sprite menuSprite;
	sf::Sprite stripSprite;
	sf::Sprite checkSprite;
	sf::Sprite endSprite;

	sf::Font font;

	sf::Text musicVol;
	sf::Text soundVol;
	sf::Text timer;
	sf::Text winnerText;
	sf::Text score;
	sf::Text remis;

	sf::IntRect playerOneRect;
	sf::IntRect playerTwoRect;

	sf::SoundBuffer click;
	sf::SoundBuffer enter;
	sf::Sound sound;

	sf::Clock animationPlayerOne;
	sf::Clock animationPlayerTwo;

	sf::Clock bombTime;
	sf::Clock bombTwoTime;
	sf::Clock compBombPlace;
	sf::Clock resetBombCol;
	sf::Clock mainTimer;

	sf::Vector2f Resize;

	std::string stringMusicVolume;
	std::string stringSoundVolume;
	std::string stringTimer;
	std::string stringMinute;
	std::string stringWinner;
	std::string stringScore;
	std::string stringRemis;

	float xBombPlayerOne, yBombPlayerOne;
	float width, height;
	float sliderMusicPosition;
	float sliderSoundPosition;
	float xBombPlayerTwo, yBombPlayerTwo;
	float playerOneSpeedUp;
	float playerOneSpeedRight;
	float playerOneSpeedDown;
	float playerOneSpeedLeft;
	float playerTwoSpeedUp;
	float playerTwoSpeedRight;
	float playerTwoSpeedDown;
	float playerTwoSpeedLeft;
	float xPlayerOne, yPlayerOne;
	float xPlayerTwo, yPlayerTwo;
	float xComputerDir, yComputerDir;
	float hypo;

	bool wasRightPlayerOne, wasLeftPlayerOne;
	bool wasRightPlayerTwo, wasLeftPlayerTwo;
	bool mutedSound;
	bool mutedMusic;
	bool oneKey;
	bool wasGame;
	bool stopAudio;
	bool placedBombPlayerOne;
	bool placedBombPlayerTwo;
	bool hoverButtonOne, hoverButtonTwo, hoverButtonThree, hoverButtonFour;
	bool sliderMusicClicked;
	bool sliderSoundClicked;
	bool oneTimeAudio;
	bool playerOneDMG, playerTwoDMG;
	bool bombCol, oneBombCol;
	bool isRemis;

	int choice;
	int playerOneDMGStop, playerTwoDMGStop;
	int onePlayerBomb, twoPlayerBomb;
	int playerOneHP, playerTwoHP;
	int selectPlayerOne, selectPlayerTwo;
	int musicVolume, soundVolume;
	int playerOneScore, playerTwoScore;
	int minute;

	void Input();
	void Audio();
	void Cursor();
	void endGame();
	void Display();
	void GameLoop();
	void StartGame();
	void showTimer();
	void MenuOptions();
	void MusicSlider();
	void SoundSlider();
	void LoadingFiles();
	void ComputerEnemy();
	void SliderCollision();
};