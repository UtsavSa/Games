#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


using namespace sf;

//#ifndef GAME_H
//#define GAME_H


/*class that acts as the game engiene 

wrapper class
*/


class Game
{

private:

	//varuables
	//window
	RenderWindow * window;
	VideoMode videomode;
	Event ev;


	// Mouse positions
	Vector2i mousePosWindow;
	Vector2f mousePosView;


	//Resources
	Font font;

	//text
	Text uiText;

	//game logic
	unsigned points;
	
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	int health;
	bool endGame;


	// game objects
	std::vector<sf::RectangleShape> enemies;
	RectangleShape enemy;
	//std::vector<sf::String> enemies;


	// private function
	void initializeVariables();
	void initializeWindow();
	void initializeFonts();
	void initTexts();
	void initializeEnemies();


	


public:
	// constructors /destructors
	Game();
	virtual ~Game();


	// Accessors

	const bool running() const;
	const bool getEndGame() const;



	//Functions
	void spawnEnemy();
	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void renderEnemies(RenderTarget& target);

	void updateText();
	void renderText(RenderTarget& target);

	void update();
	void render();



};

