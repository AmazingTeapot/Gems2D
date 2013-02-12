#include "stdafx.h"
#include <SFML\Window.hpp>
#include "GameManager.h"
using namespace std;

int main() {

	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Window Name");			
	GameManager::getInstance()->start();
	GameManager::getInstance()->run(App);
	GameManager::getInstance()->exit();
    return 0;
}