#include "stdafx.h"
#include "Level.h"
#include <fstream>
#include <iostream>
#include "Image.h"
#include "ResourceManager.h"

using namespace std;

Level::Level() {
	m_size_x = 0;
	m_size_y = 0;
	center_x = WINDOW_SIZE_X/2;
	center_y = WINDOW_SIZE_Y/2;
	obs_x = center_x;
	obs_y = center_y;
	events = *new vector<int>(100, 0);
}

Level::~Level() {

}

void Level::setLayers (string levelName) {
	
	/* CODE */
	int layer_numb;
	ifstream levelconfig(LEVEL_CONFIGS + levelName + "_config" + LEVEL_EXTENSION);
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
				ResourceManager::getInstance()->loadImage(levelName + "_" + resourceName, levelName + "/" + resourceName);
				m_layers.push_back(new MovingImageLayer (ResourceManager::getInstance()->getImage(levelName + "_" + resourceName)));
				break;
			case 1:
				if (levelconfig.good()) levelconfig >> resourceName >> x_size >> y_size;
				ResourceManager::getInstance()->loadImage(levelName + "_" + resourceName, levelName + "/" + resourceName);
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
	}
}

void Level::update(float deltaTime) {
	float movement = (100*deltaTime);
		cout << movement << endl;
	if(events[UP]) {
		if (obs_y - movement <= 0) obs_y = 0;
		else obs_y -= movement;
	}

	if(events[DOWN]) {
		if (obs_y + movement >= Camera::getInstance()->getLevelSize().second) obs_y = Camera::getInstance()->getLevelSize().second;
		else obs_y += movement;
	}

	if(events[LEFT]) {
		if (obs_x - movement <= 0) obs_x = 0;
		else obs_x -= movement;
	}
	
	if(events[RIGHT]) {
		if (obs_x + movement >= Camera::getInstance()->getLevelSize().second) obs_x = Camera::getInstance()->getLevelSize().second;
		else obs_x += movement;
	}
	events = *new vector<int>(100, 0);
	for(int i = 0; i < m_layers.size(); ++i) m_layers[i]->update();
}

void Level::draw(sf::RenderWindow& App) {
	for(int i = 0; i < m_layers.size(); ++i) m_layers[i]->draw(App);
}


void Level::eventHandler(int x) {
	events[x] = 1;

	Camera::getInstance()->updateCameraPos(obs_x, obs_y);
}

