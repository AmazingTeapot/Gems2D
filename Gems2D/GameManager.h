#pragma once
#include "stdafx.h"
#include <vector>
#include "Level.h"
#include <map>
#include <set>
#include "Constants.h"

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
	~GameManager();

	/* GAME STRUCTURE */

	/* Initializations: It sets the camera, loads the firsts resources and other tasks. */
	void start();

	/* Gameloop: Here the game starts, and it keeps running. It handles all the level changes, all the external events... */
	void run(sf::RenderWindow& App);

	/* Exit: Here we enter when the game exists - TO DO */
	void exit();

	/* THIS IS DEFINITELY NOT GOING TO BE HERE ON A FUTURE. I'll build another Singleton class to manage game events
	like the collitions. So... by now we have this patch. */
	
	int getCollision(int i);

	void addCollision(int i);

	void deleteCollision(int i);

	void activeWhip(int i);

	int getActiveWhip();

	void victory(std::vector<int> saveData);

	void defeat();

	std::vector<int> getSave();

	std::string getLevelName();

private:

	int m_actualLevel;
	int m_levelNumb;
	int active_whip;
	std::string m_levelName;
	std::vector<int> m_saveData;
	std::vector<int> m_collided_element;
	std::vector<Level> m_levels;
	std::vector<int> m_levels2;
	Level Level1;
	Level Level2;
	GameManager();
	GameManager(GameManager* const&);
	void operator=(GameManager* const&);
	bool m_end;
	bool endgame;
};