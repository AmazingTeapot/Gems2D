#pragma once
#include "stdafx.h"
#include "Layer.h"
#include "Camera.h"
#include "Sprite.h"
#include "StaticElementsLayer.h"
#include "ResourceManager.h"
#include <fstream>
#include <iostream>

using namespace std;

StaticElementsLayer::StaticElementsLayer() { 
	m_elements = 0;
	m_level_folder = "";
}

StaticElementsLayer::~StaticElementsLayer() { }

void StaticElementsLayer::setLayer (string path) {
	ifstream level (LEVEL_PATH + path + "/static_elem" + LEVEL_EXTENSION);
	if (level.is_open()) {
		if(level.good()) level >> m_level_folder >> m_elements >> m_diff_resources;
		string name;
		for(int i = 0; i < m_diff_resources; ++i) {
			level >> name;
			string resource = STATIC_ELEMENTS_LAYER_PATH + name;
			ResourceManager::getInstance()->loadImage(m_level_folder + "_" + resource, resource);
			m_drawables[name] = new Sprite(ResourceManager::getInstance()->getImage(m_level_folder + "_" + resource));
		}
		m_layer_elements = vector < vector <int>> (m_elements, vector <int> (4));
		m_layer_elements_type = vector<string>(m_elements);

		for (int i = 0; i < m_elements; ++i) {
			if(level.good()) {
				level >> m_layer_elements[i][0] >> m_layer_elements[i][1] >> m_layer_elements[i][2] 
				>> m_layer_elements[i][3] >> m_layer_elements_type[i]; 
				m_layer_elements[i][0] += 255;
				m_layer_elements[i][1] += 88;
			}
		}
	}
	level.close();
}

void StaticElementsLayer::update(float deltaTime) {
	/* No need of update because we're using the sprite array as a set of stamps. */
}

void StaticElementsLayer::draw (sf::RenderWindow& App) {
	vector<int> drawableArea;
	Camera::getInstance()->getDrawableArea(drawableArea);
	int window_size_x = Camera::getInstance()->getWindowSize().first;
	int window_size_y = Camera::getInstance()->getWindowSize().second;
	for(int i = 0; i < m_layer_elements.size(); ++i) { 
		if (isDrawable(m_layer_elements[i], drawableArea))	{
			(*m_drawables[m_layer_elements_type[i]]).setPos((float)m_layer_elements[i][0] - Camera::getInstance()->getObsPoint().first + Camera::getInstance()->getWindowSize().first/2, 
				(float)m_layer_elements[i][1] - Camera::getInstance()->getObsPoint().second + Camera::getInstance()->getWindowSize().second/2);
			(*m_drawables[m_layer_elements_type[i]]).setSize(m_layer_elements[i][2], m_layer_elements[i][3]);
			(*m_drawables[m_layer_elements_type[i]]).draw(App);
			(*m_drawables[m_layer_elements_type[i]]).setSize(m_layer_elements[i][2], m_layer_elements[i][3]);
		}
	}
}

void StaticElementsLayer::superDraw (sf::RenderWindow& App, vector<int> toDraw) {
	vector<int> drawableArea;
	Camera::getInstance()->getDrawableArea(drawableArea);
	int window_size_x = Camera::getInstance()->getWindowSize().first;
	int window_size_y = Camera::getInstance()->getWindowSize().second;
	for(int i = 0; i < toDraw.size(); ++i) { 
		if (isDrawable(m_layer_elements[toDraw[i]], drawableArea))	{
			(*m_drawables[m_layer_elements_type[toDraw[i]]]).setPos((float)m_layer_elements[toDraw[i]][0] - Camera::getInstance()->getObsPoint().first + Camera::getInstance()->getWindowSize().first/2, 
				(float)m_layer_elements[toDraw[i]][1] - Camera::getInstance()->getObsPoint().second + Camera::getInstance()->getWindowSize().second/2);
			(*m_drawables[m_layer_elements_type[toDraw[i]]]).setSize(m_layer_elements[toDraw[i]][2], m_layer_elements[toDraw[i]][3]);
			(*m_drawables[m_layer_elements_type[toDraw[i]]]).draw(App);
			(*m_drawables[m_layer_elements_type[toDraw[i]]]).setSize(m_layer_elements[toDraw[i]][2], m_layer_elements[toDraw[i]][3]);
		}
	}
}

bool StaticElementsLayer::isDrawable(vector<int> element, vector<int> drawableArea) {
	return(element[0]+element[2] > drawableArea[0] && element[1]+element[3] > drawableArea[1] && 
    element[0] < drawableArea[2] && element[1] < drawableArea[3]);
}