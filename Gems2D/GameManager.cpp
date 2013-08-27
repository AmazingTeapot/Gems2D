#include "stdafx.h"
#include "GameManager.h"
#include <fstream>
#include <iostream>
#include <Windows.h>
GameManager::GameManager() { 
	up_pressed = false;
	down_pressed = false;
	left_pressed = false;
	right_pressed = false;
}

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

// DA MUSIC GOES HERE, PERO NO VA =D 
	/*	sf::Music Music1;        
	if (!Music1.openFromFile("/Resources/song.ogg"))
{
cout << "derp" ;
	}
	Music1.play();
*/
}

void GameManager::run(sf::RenderWindow& App) {
	
	sf::Clock c;
	while (App.isOpen()) {
		sf::Event Evento;
		float deltaTime = c.getElapsedTime().asSeconds();
		c.restart();

			if (App.pollEvent(Evento)) {	

			// Closing the Window
			if(Evento.type == sf::Event::Closed) {
			   App.close();
			}
			
			// Keyboard Events. Here we have to include a catcher for every key we want to use in the game.

			if ((Evento.type == sf::Event::KeyPressed) && (Evento.key.code == sf::Keyboard::Up)) m_levels[m_actualLevel].eventHandler(UP);
			if ((Evento.type == sf::Event::KeyPressed) && (Evento.key.code == sf::Keyboard::Down)) m_levels[m_actualLevel].eventHandler(DOWN);
			if ((Evento.type == sf::Event::KeyPressed) && (Evento.key.code == sf::Keyboard::Left)) m_levels[m_actualLevel].eventHandler(LEFT);
			if ((Evento.type == sf::Event::KeyPressed) && (Evento.key.code == sf::Keyboard::Right)) m_levels[m_actualLevel].eventHandler(RIGHT);
			if ((Evento.type == sf::Event::KeyPressed) && (Evento.key.code == sf::Keyboard::Return)) m_levels[m_actualLevel].eventHandler(PAUSE);
			if ((Evento.type == sf::Event::KeyPressed) && (Evento.key.code == sf::Keyboard::Back)) m_levels[m_actualLevel].eventHandler(SELECT);
			}
   

			// Joystick Events. Here we have to include a catcher for every button we want to use from the joystick.

			// TO - DO

			/*if(sf::Joystick::isConnected(0)) {
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
			}*/
		
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
