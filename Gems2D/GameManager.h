#pragma once
#include "stdafx.h"
#include <vector>
#include "Level.h"

/* Class: Game Manager
   Brief: Singleton class. This class handles the classical game structure. The initialization, where the camera is setted, some 
          resources are loaded, etc, the gameloop, where the game runs, the levels are changed, the external events are captured... and the exit */

class GameManager {

	public:

	static GameManager* getInstance() {
		static GameManager instance;
		return &instance;
	}

	/* DESTRUCTORS */

	/* Empty destructor */
	GameManager::~GameManager();

	/* GAME STRUCTURE */

	/* Initializations: It sets the camera, loads the firsts resources and other tasks. */
	void GameManager::start();

	/* Gameloop: Here the game starts, and it keeps running. It handles all the level changes, all the external events... */
	void GameManager::run(sf::RenderWindow& App);

	/* Exit: Here we enter when the game exists - TO DO */
	void GameManager::exit();

	private:
	int m_actualLevel;
	vector<Level> m_levels;
	GameManager();
	GameManager(GameManager* const&);
	void operator=(GameManager* const&);
	bool up_pressed;
	bool down_pressed;
	bool left_pressed;
	bool right_pressed;
};