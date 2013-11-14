#include "stdafx.h"
#include <SFML\Window.hpp>
#include "GameManager.h"
#include "Constants.h"
#include <thread>
//#include <Windows.h>

int main() {
	//system("%SystemRoot%\\song.wav");
	sf::RenderWindow App(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32), "Vampire Killer Revamped", sf::Style::Fullscreen);
	GameManager::getInstance()->start();
	GameManager::getInstance()->run(App);
	GameManager::getInstance()->exit();
    return 0;
}