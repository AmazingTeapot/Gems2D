#pragma once
#include "stdafx.h"
#include "Layer.h"
#include "Camera.h"
#include "Sprite.h"
#include "StaticElementsLayer.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include <fstream>
#include <iostream>
#include <iterator>

StaticElementsLayer::StaticElementsLayer() { 
	m_elements = 0;
	m_level_folder = "";
}

StaticElementsLayer::~StaticElementsLayer() { }

void StaticElementsLayer::setLayer (std::string path) {
	std::ifstream level (LEVEL_PATH + path + "/static_elem" + LEVEL_EXTENSION);
	if (level.is_open()) {
		if(level.good()) level >> m_level_folder >> m_elements >> m_diff_resources;
		std::string name;
		for(int i = 0; i < m_diff_resources; ++i) {
			level >> name;
			std::string resource = STATIC_ELEMENTS_LAYER_PATH + name;
			ResourceManager::getInstance()->loadImage(m_level_folder + "_" + resource, resource);
			m_drawables[name] = new Sprite(ResourceManager::getInstance()->getImage(m_level_folder + "_" + resource));
		}
		m_layer_elements = std::vector < std::vector <int>> (m_elements, std::vector <int> (4));
		m_layer_elements_type = std::vector<std::string>(m_elements);

		for (int i = 0; i < m_elements; ++i) {
			if(level.good()) {
				level >> m_layer_elements[i][0] >> m_layer_elements[i][1] >> m_layer_elements[i][2] 
				>> m_layer_elements[i][3] >> m_layer_elements_type[i]; 
			//	m_layer_elements[i][0] += 128;
			}
		}
	}
	level.close();
}

void StaticElementsLayer::update(float deltaTime) {
	/* No need of update because we're using the sprite array as a set of stamps. */
}

void StaticElementsLayer::draw (sf::RenderWindow& App) {
	std::vector<int> drawableArea;
	Camera::getInstance()->getDrawableArea(drawableArea);
	int window_size_x = Camera::getInstance()->getWindowSize().first;
	int window_size_y = Camera::getInstance()->getWindowSize().second;
	for(int i = 0; i < m_layer_elements.size(); ++i) { 
		if (isDrawable(m_layer_elements[i], drawableArea))	{
			(*m_drawables[m_layer_elements_type[i]]).setPos((float)m_layer_elements[i][0] - Camera::getInstance()->getObsPoint().first + Camera::getInstance()->getWindowSize().first/2, 
				(float)m_layer_elements[i][1] - Camera::getInstance()->getObsPoint().second + Camera::getInstance()->getWindowSize().second/2);
			(*m_drawables[m_layer_elements_type[i]]).setSize(m_layer_elements[i][2], m_layer_elements[i][3]);
			(*m_drawables[m_layer_elements_type[i]]).draw(App);
		}
	}
}

void StaticElementsLayer::superDraw (sf::RenderWindow& App, int element, float x_pos, float y_pos) {
	if(x_pos >= 0) {
		(*m_drawables[m_layer_elements_type[element]]).setPos(x_pos - Camera::getInstance()->getObsPoint().first + Camera::getInstance()->getWindowSize().first/2, 
				y_pos - Camera::getInstance()->getObsPoint().second + Camera::getInstance()->getWindowSize().second/2);
	} 
	else {	
		(*m_drawables[m_layer_elements_type[element]]).setPos(m_layer_elements[element][0] - Camera::getInstance()->getObsPoint().first + Camera::getInstance()->getWindowSize().first/2, 
				m_layer_elements[element][1] - Camera::getInstance()->getObsPoint().second + Camera::getInstance()->getWindowSize().second/2);
	}
	(*m_drawables[m_layer_elements_type[element]]).setSize(m_layer_elements[element][2], m_layer_elements[element][3]);
	(*m_drawables[m_layer_elements_type[element]]).draw(App);

}

bool StaticElementsLayer::isDrawable(std::vector<int> element, std::vector<int> drawableArea) {
	return(element[0]+element[2] > drawableArea[0] && element[1]+element[3] > drawableArea[1] && 
    element[0] < drawableArea[2] && element[1] < drawableArea[3]);
}

void StaticElementsLayer::drawOnScreen (sf::RenderWindow& App, int element) {
			(*m_drawables[m_layer_elements_type[element]]).setPos(m_layer_elements[element][0], m_layer_elements[element][1]);
			(*m_drawables[m_layer_elements_type[element]]).setSize(m_layer_elements[element][2], m_layer_elements[element][3]);
			(*m_drawables[m_layer_elements_type[element]]).draw(App);	
}
