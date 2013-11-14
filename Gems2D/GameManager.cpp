#include "stdafx.h"
#include "GameManager.h"
#include <fstream>
#include <iostream>
//#include <Windows.h>
#include <SFML\Audio.hpp>
#include <set>

GameManager::GameManager() { 
	m_actualLevel = 0;
	m_collided_element = std::vector<int>(61, false);
	m_saveData = std::vector<int>(13, 0);
	m_saveData[12] = 10;
	m_levelName = "level1";
	m_end = false;
	endgame = false;
}

GameManager::~GameManager(void) { }

void GameManager::start() {
	std::ifstream config ("./Resources/gameconfig.txt");
	if (config.is_open()) {
		if (config.good()) {
			config >> m_levelNumb;
		}
	}
	m_actualLevel = 0;
	
	std::ifstream config2 ("./Resources/level1.txt");
		int window_x, window_y, size_x, size_y;
		if (config2.is_open()) {
			if (config2.good()) {
				config2 >> window_x >> window_y >> size_x >> size_y;
			}
		}
		Camera::getInstance()->setWindowSize(window_x, window_y);
		Camera::getInstance()->setLevelSize(size_x, size_y);
		m_levels = std::vector<Level>(2);
		//std::string levelConfig = "level1";
		m_levelName = "level1";
		m_levels[0].setLayers();
}

void GameManager::run(sf::RenderWindow& App) {
	
	bool intro = true;
	bool goingUp = false;
	bool goingDown = false;
	int slide = 0;
	StaticElementsLayer howto;
	howto.setLayer("howto");
	sf::Clock c;
	sf::SoundBuffer buffer;
	sf::SoundBuffer backbuffer;
 //   if (!backbuffer.loadFromFile("./Resources/Music/maintheme.wav")) std::cout << "error";
	sf::Sound sound;
	sf::Sound backsound;
	backsound.resetBuffer();
	backsound.setBuffer(backbuffer);
	backsound.play();
	backsound.setLoop(true);
	while (App.isOpen()) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) m_levels[m_actualLevel].eventHandler(UP);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) m_levels[m_actualLevel].eventHandler(DOWN);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) m_levels[m_actualLevel].eventHandler(LEFT);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) m_levels[m_actualLevel].eventHandler(RIGHT);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) m_levels[m_actualLevel].eventHandler(ACTION_JUMP);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) m_levels[m_actualLevel].eventHandler(ACTION_JUMP);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) m_levels[m_actualLevel].eventHandler(ATTACK_1);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) m_levels[m_actualLevel].eventHandler(ATTACK_2);
			sf::Event Evento;

			if(sf::Joystick::isConnected(0)) {
				if(sf::Joystick::isButtonPressed(0,0))m_levels[m_actualLevel].eventHandler(ACTION_JUMP);
				if(sf::Joystick::isButtonPressed(0,3))m_levels[m_actualLevel].eventHandler(ATTACK_2);
				if(sf::Joystick::isButtonPressed(0,7))m_levels[m_actualLevel].eventHandler(ATTACK_2);
				if(sf::Joystick::isButtonPressed(0,2))m_levels[m_actualLevel].eventHandler(ATTACK_1);
				if(sf::Joystick::getAxisPosition(0,sf::Joystick::Y) > 30) m_levels[m_actualLevel].eventHandler(DOWN);
				if(sf::Joystick::getAxisPosition(0,sf::Joystick::Y) < -30) m_levels[m_actualLevel].eventHandler(UP);
				if(sf::Joystick::getAxisPosition(0,sf::Joystick::X) > 30) m_levels[m_actualLevel].eventHandler(RIGHT);
				if(sf::Joystick::getAxisPosition(0,sf::Joystick::X) < -30) m_levels[m_actualLevel].eventHandler(LEFT);
			}
		float deltaTime = c.getElapsedTime().asSeconds();
		c.restart();

			if (App.pollEvent(Evento)) {	

				// Closing the Window
				if(Evento.type == sf::Event::Closed) {
				   App.close();
				}
			
				// Keyboard Events. Here we have to include a catcher for every key we want to use in the game.

				if (Evento.type == sf::Event::KeyPressed && Evento.key.code == sf::Keyboard::Up) m_levels[m_actualLevel].eventHandler(ROTATE_LEFT);
				if (Evento.type == sf::Event::KeyPressed && Evento.key.code == sf::Keyboard::Down) m_levels[m_actualLevel].eventHandler(ROTATE_RIGHT);
				if (Evento.type == sf::Event::KeyPressed && (Evento.key.code == sf::Keyboard::Z || Evento.key.code == sf::Keyboard::Return)) {
					m_levels[m_actualLevel].eventHandler(SELECT);
					if(intro) {
						if(slide == 0) {
							sound.resetBuffer();
							if (!buffer.loadFromFile("./Resources/Music/select.wav")) std::cout << "error";
							sound.setBuffer(buffer);
							sound.play();
							intro = false;
						}
						else ++slide;
					}
				}

				if (Evento.type == sf::Event::KeyPressed && (Evento.key.code == sf::Keyboard::X || Evento.key.code == sf::Keyboard::Escape)) {
					m_levels[m_actualLevel].eventHandler(QUIT);
					if(intro && slide == 0) {
						++slide;
						sound.resetBuffer();
						if (!buffer.loadFromFile("./Resources/Music/select.wav")) std::cout << "error";
						sound.setBuffer(buffer);
						sound.play();
					}
					else if(endgame) GameManager::exit();
				}

				if (Evento.type == sf::Event::JoystickButtonPressed && (Evento.joystickButton.button == 0)) {
					m_levels[m_actualLevel].eventHandler(SELECT);
					if(intro) {
						if(slide == 0) intro = false;
						else ++slide;
					}
				}
				if (Evento.type == sf::Event::JoystickButtonPressed && Evento.joystickButton.button == 4)  m_levels[m_actualLevel].eventHandler(ROTATE_LEFT);
				if (Evento.type == sf::Event::JoystickButtonPressed && Evento.joystickButton.button == 5)  m_levels[m_actualLevel].eventHandler(ROTATE_RIGHT);
			}
			if(slide == 14) intro = false;
   
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
	

		if(intro) {
		howto.drawOnScreen(App, slide);
		App.display();
		App.clear();
		}
		else if (endgame) {
			App.clear();
			howto.drawOnScreen(App, 14);
			App.display();
		}
		else {
		
		/* Draw */
		m_levels[m_actualLevel].draw(App);
		App.display();
		m_levels[m_actualLevel].update(deltaTime);
		
	   // Clear the screen
		App.clear();
		}
	   if(m_end) App.close();
	}
}

void GameManager::exit() {
	m_end = true;
}


int GameManager::getCollision(int i) {
	return m_collided_element[i];
}

void GameManager::addCollision(int i) {
	m_collided_element[i] = true;
}

void GameManager::deleteCollision(int i) {
	m_collided_element[i] = false;
}

void GameManager::activeWhip(int i) {
	active_whip = i;
}

int GameManager::getActiveWhip() {
	return active_whip;
}

void GameManager::victory(std::vector<int> saveData) {
	m_saveData = saveData;
	if(m_actualLevel == 0) {
		m_actualLevel = 1;
		m_levelName = "level2";
			std::ifstream config ("./Resources/level" + std::to_string(m_actualLevel + 1) + ".txt");
		int window_x, window_y, size_x, size_y;
		if (config.is_open()) {
			if (config.good()) {
				config >> window_x >> window_y >> size_x >> size_y;
			}
		}
		Camera::getInstance()->setWindowSize(window_x, window_y);
		Camera::getInstance()->setLevelSize(size_x, size_y);
		m_collided_element = std::vector<int>(61, false);
		m_levels[1].setLayers();
	}
	else {
		endgame = true;
		sf::SoundBuffer buffer2;
		sf::Sound sound2;
		if (!buffer2.loadFromFile("./Resources/Music/victory.wav")) std::cout << "error";
		sound2.setBuffer(buffer2);
		sound2.play();
	}
}

void GameManager::defeat() {
		std::ifstream config ("./Resources/level" + std::to_string(m_actualLevel + 1) + ".txt");
	int window_x, window_y, size_x, size_y;
	if (config.is_open()) {
		if (config.good()) {
			config >> window_x >> window_y >> size_x >> size_y;
		}
	}
	m_levels.clear();
	m_levels = std::vector<Level>(2);
	Camera::getInstance()->setWindowSize(window_x, window_y);
	Camera::getInstance()->setLevelSize(size_x, size_y);
	m_collided_element = std::vector<int>(60, false);
	m_levels[m_actualLevel].setLayers();
}

std::vector<int> GameManager::getSave() {
	return m_saveData;
}

std::string GameManager::getLevelName() {
	return m_levelName;
}