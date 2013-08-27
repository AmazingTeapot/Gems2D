#include "stdafx.h"
#include "Level.h"
#include <fstream>
#include <iostream>
#include "Image.h"
#include "ResourceManager.h"
#include "Constants.h"
#include <Windows.h>
using namespace std;

Level::Level() {
	srand (time(NULL));
	m_size_x = 0;
	m_size_y = 0;
	center_x = WINDOW_SIZE_X/2;
	center_y = WINDOW_SIZE_Y/2;
	obs_x = center_x;
	obs_y = center_y;
	events = vector<int>(100, 0);
	/* Physics thing. Nevermind now. */
	Camera::getInstance()->setSteps(1);
}

Level::~Level() {

}

void Level::setLayers (string levelName) {
	/* CODE */
	int layer_numb;
	cout << LEVEL_PATH + levelName + LEVEL_CONFIGS + LEVEL_EXTENSION;
	ifstream levelconfig(LEVEL_PATH + levelName + LEVEL_CONFIGS + LEVEL_EXTENSION);
	if (levelconfig.is_open()) {
		if (levelconfig.good()) levelconfig >> layer_numb;
		m_layers.clear();
		m_layers.reserve(layer_numb);
		for(int i = 0; i < layer_numb; ++i) {
			string loadPath, resourceName;
			int layerType, x_size, y_size;
			if (levelconfig.good()) levelconfig >> layerType;
			switch (layerType) {
			case 0:	
				if (levelconfig.good()) levelconfig >> resourceName;
				ResourceManager::getInstance()->loadImage(levelName + "_" + resourceName, MOVING_IMAGE_LAYER_PATH + resourceName);
				m_layers.push_back(new MovingImageLayer (ResourceManager::getInstance()->getImage(levelName + "_" + resourceName)));
				break;
			case 1:
				if (levelconfig.good()) levelconfig >> resourceName >> x_size >> y_size;
				ResourceManager::getInstance()->loadImage(levelName + "_" + resourceName, STATIC_GRID_LAYER_PATH + resourceName);
				m_layers.push_back(new StaticGridLayer (ResourceManager::getInstance()->getImage(levelName + "_" + resourceName), x_size, y_size));
				m_layers[i]->setLayer(levelName);
				break;
			case 2:
				m_layers.push_back(new StaticElementsLayer());
				m_layers[i]->setLayer(levelName);
				break;
			case 3:
				m_layers.push_back(new AnimatedElementsLayer());
				m_layers[i]->setLayer(levelName);
				break;
			default:
				break;
			}
		}
		loadWorld();
	}
}

void Level::loadWorld() {

}


void Level::update(float deltaTime) {
	
	/* PROCESSING EVENTS HERE */


	events = vector<int>(100, 0);
	Camera::getInstance()->updateCameraPos(obs_x, obs_y);
	for(int i = 0; i < m_layers.size(); ++i) m_layers[i]->update(deltaTime);

}

void Level::gameOver() {
	srand (time(NULL));
	m_size_x = 0;
	m_size_y = 0;
	center_x = WINDOW_SIZE_X/2;
	center_y = WINDOW_SIZE_Y/2;
	obs_x = center_x;
	obs_y = center_y;
	events = vector<int>(100, 0);

	/* Physics thing. Nevermind now. */
	Camera::getInstance()->setSteps(1);

}

void Level::draw(sf::RenderWindow& App) {
	
}

void Level::eventHandler(int x) {
	events[x] = 1;
}

