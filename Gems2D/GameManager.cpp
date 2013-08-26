#include "stdafx.h"
#include "GameManager.h"
#include <fstream>
#include <iostream>

GameManager::GameManager() { }

GameManager::~GameManager(void) { }

void GameManager::start() {
	int level_numb, window_x, window_y, size_x, size_y;
	ifstream config ("./Resources/gameconfig.txt");
	if (config.is_open()) {
		if (config.good()) {
			config >> window_x >> window_y >> size_x >> size_y >> level_numb;
			Camera::getInstance()->setWindowSize(window_x, window_y);
			Camera::getInstance()->setLevelSize(size_x, size_y);
			m_levels = *new vector<Level>(level_numb);
		}
		for(int i = 0; i < level_numb; ++i) {
			string levelConfig;
			if (config.good()) config >> levelConfig;
			m_levels[i].setLayers(levelConfig);
		}
	}
	m_actualLevel = 0;
}

void GameManager::run(sf::RenderWindow& App) {
	
	sf::Clock c;
	while (App.isOpen()) {
		sf::Event Evento;
		float deltaTime = c.getElapsedTime().asSeconds();
		c.restart();

		/*	if (App.pollEvent(Evento)) {	

			// Closing the Window
			if(Evento.type == sf::Event::Closed) {
			   App.close();
			}
			*/
			// Keyboard Events. Here we have to include a catcher for every key we want to use in the game.
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) m_levels[m_actualLevel].eventHandler(LEFT);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) m_levels[m_actualLevel].eventHandler(DOWN);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) m_levels[m_actualLevel].eventHandler(UP);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) m_levels[m_actualLevel].eventHandler(RIGHT);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) m_levels[m_actualLevel].eventHandler(ACTION_RUN);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) m_levels[m_actualLevel].eventHandler(ACTION_JUMP);
			
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)) m_levels[m_actualLevel].eventHandler(ATTACK_1);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)) m_levels[m_actualLevel].eventHandler(ATTACK_2);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) m_levels[m_actualLevel].eventHandler(MAGIC_1);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) m_levels[m_actualLevel].eventHandler(MAGIC_2);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) m_levels[m_actualLevel].eventHandler(PAUSE);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) m_levels[m_actualLevel].eventHandler(QUIT);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) m_levels[m_actualLevel].eventHandler(FULLSCREEN);

			// Joystick Events. Here we have to include a catcher for every button we want to use from the joystick.

			if(sf::Joystick::isConnected(0)) {
				if(sf::Joystick::isButtonPressed(0,0))m_levels[m_actualLevel].eventHandler(ACTION_JUMP);
				if(sf::Joystick::isButtonPressed(0,1))m_levels[m_actualLevel].eventHandler(MAGIC_1);
				if(sf::Joystick::isButtonPressed(0,3))m_levels[m_actualLevel].eventHandler(ATTACK_2);
				if(sf::Joystick::isButtonPressed(0,2))m_levels[m_actualLevel].eventHandler(ATTACK_1);
				if(sf::Joystick::isButtonPressed(0,4))m_levels[m_actualLevel].eventHandler(ACTION_RUN);

				if(sf::Joystick::getAxisPosition(0,sf::Joystick::Y) > 10) m_levels[m_actualLevel].eventHandler(UP);
				if(sf::Joystick::getAxisPosition(0,sf::Joystick::Y) < 10) m_levels[m_actualLevel].eventHandler(DOWN);
				if(sf::Joystick::getAxisPosition(0,sf::Joystick::X) > 10) m_levels[m_actualLevel].eventHandler(RIGHT);
				if(sf::Joystick::getAxisPosition(0,sf::Joystick::X) < 10) m_levels[m_actualLevel].eventHandler(LEFT);
				if(sf::Joystick::getAxisPosition(0,sf::Joystick::PovX) > 10) m_levels[m_actualLevel].eventHandler(ACTION_RUN);
			}
		
		/* Get Level Status*/

	//	if (m_levels[m_actualLevel].isFinished()) {
	//		
	//		/* Set New Level Status*/
	//
	//		vector<int> stats = m_levels[m_actualLevel].getStats();
	//		m_actualLevel = stats[0];
	//
	//		/* Stats actualisation */
	//	
	//	}
	
		/* Draw */
		m_levels[m_actualLevel].update(deltaTime);
		m_levels[m_actualLevel].draw(App);
		App.display();

	   // Clear the screen
	   App.clear();

	}
}

void GameManager::exit() {

}
