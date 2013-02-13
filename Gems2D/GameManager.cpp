#include "stdafx.h"
#include "GameManager.h"
#include <fstream>
#include <iostream>

const int WINDOW_SIZE_X = 800;
const int WINDOW_SIZE_Y = 600;

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
			m_levels[i].setLayer1(levelConfig);
		}
	}
	m_actualLevel = 0;
}

void GameManager::run(sf::RenderWindow& App) {
	
	while (App.isOpen()) {

		sf::Event Evento;
		if (App.pollEvent(Evento)) {	

			// Closing the Window
			if(Evento.type == sf::Event::Closed) {
			   App.close();
			}

			// Keyboard Events
			if (Evento.type == sf::Event::KeyPressed) {				
				if (Evento.key.code == sf::Keyboard::Right || Evento.key.code == sf::Keyboard::D) m_levels[m_actualLevel].eventHandler(0);
				else if (Evento.key.code == sf::Keyboard::Left || Evento.key.code == sf::Keyboard::A) m_levels[m_actualLevel].eventHandler(1);
				else if (Evento.key.code == sf::Keyboard::Down || Evento.key.code == sf::Keyboard::S) m_levels[m_actualLevel].eventHandler(2);
				else if (Evento.key.code == sf::Keyboard::Up || Evento.key.code == sf::Keyboard::Space || Evento.key.code == sf::Keyboard::W) m_levels[m_actualLevel].eventHandler(3);
				else if (Evento.key.code == sf::Keyboard::Tab) m_levels[m_actualLevel].eventHandler(4);
				else if (Evento.key.code == sf::Keyboard::Num1) m_levels[m_actualLevel].eventHandler(5);
				else if (Evento.key.code == sf::Keyboard::Num2) m_levels[m_actualLevel].eventHandler(6);
				else if(Evento.key.code == sf::Keyboard::Num3) m_levels[m_actualLevel].eventHandler(7);
				else if(Evento.key.code == sf::Keyboard::Num4) m_levels[m_actualLevel].eventHandler(8);
				else if(Evento.key.code == sf::Keyboard::Num5) m_levels[m_actualLevel].eventHandler(9);
				else if(Evento.key.code == sf::Keyboard::Num6) m_levels[m_actualLevel].eventHandler(10);
				else if(Evento.key.code == sf::Keyboard::Num7) m_levels[m_actualLevel].eventHandler(11);
				else if(Evento.key.code == sf::Keyboard::Num8) m_levels[m_actualLevel].eventHandler(12);
				else if(Evento.key.code == sf::Keyboard::Num9) m_levels[m_actualLevel].eventHandler(13);
				else if(Evento.key.code == sf::Keyboard::Return) m_levels[m_actualLevel].eventHandler(14);
				else if(Evento.key.code == sf::Keyboard::Escape) m_levels[m_actualLevel].eventHandler(15);
				else if(Evento.key.code == sf::Keyboard::Down && Evento.key.code == sf::Keyboard:: Right) m_levels[m_actualLevel].eventHandler(16);
				else if(Evento.key.code == sf::Keyboard::Down && Evento.key.code == sf::Keyboard:: Left) m_levels[m_actualLevel].eventHandler(17);
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
				if(sf::Joystick::isButtonPressed(0,0))m_levels[m_actualLevel].eventHandler(555);
				if(sf::Joystick::isButtonPressed(0,1))m_levels[m_actualLevel].eventHandler(556);
				if(sf::Joystick::isButtonPressed(0,3))m_levels[m_actualLevel].eventHandler(557);
				if(sf::Joystick::isButtonPressed(0,2))m_levels[m_actualLevel].eventHandler(558);
				if(sf::Joystick::isButtonPressed(0,4))m_levels[m_actualLevel].eventHandler(559);
				if(sf::Joystick::getAxisPosition(0,sf::Joystick::Y) > 10) m_levels[m_actualLevel].eventHandler(560);
				if(sf::Joystick::getAxisPosition(0,sf::Joystick::Y) < 10) m_levels[m_actualLevel].eventHandler(561);
				if(sf::Joystick::getAxisPosition(0,sf::Joystick::X) > 10) m_levels[m_actualLevel].eventHandler(562);
				if(sf::Joystick::getAxisPosition(0,sf::Joystick::X) < 10) m_levels[m_actualLevel].eventHandler(563);
				//pasar de trampa (tabulador).
				if(sf::Joystick::getAxisPosition(0,sf::Joystick::PovX) > 10) m_levels[m_actualLevel].eventHandler(564);
				
			}
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

		m_levels[m_actualLevel].draw(App);
		App.display();

	   // Clear the screen
	   App.clear();
	}
}

void GameManager::exit() {

}
