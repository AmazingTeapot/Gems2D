#pragma once
#include "stdafx.h"
#include <vector>
#include "Level.h"

using namespace std;

class GameManager {

private:

int m_actualLevel;
vector<Level> m_levels;
GameManager();
GameManager(GameManager* const&);
void operator=(GameManager* const&);

public:

static GameManager* getInstance() {
	static GameManager instance;
	return &instance;
}

GameManager::~GameManager();

void GameManager::start();

void GameManager::run(sf::RenderWindow& App);

void GameManager::exit();

};