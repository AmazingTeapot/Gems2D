#pragma once
#include "stdafx.h"
#include "Layer.h"
#include "Camera.h"
#include "Sprite.h"
#include "HudLayer.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include <fstream>
#include <iostream>
#include <iterator>

HudLayer::HudLayer() {
	m_elements = 0;
	m_level_folder = "";
}

HudLayer::~HudLayer() { }

void HudLayer::setLayer(std::string path) {
	std::ifstream level(LEVEL_PATH + path + "/hud_elem" + LEVEL_EXTENSION);
	if (level.is_open()) {
		if (level.good()) level >> m_level_folder >> m_elements >> m_diff_resources;
		std::string name;
		for (int i = 0; i < m_diff_resources; ++i) {
			level >> name;
			std::string resource = STATIC_ELEMENTS_LAYER_PATH + name;
			ResourceManager::getInstance()->loadImage(m_level_folder + "_" + resource, resource);
			m_drawables[name] = new Sprite(ResourceManager::getInstance()->getImage(m_level_folder + "_" + resource));
		}
		m_layer_elements = std::vector < std::vector <int>> (m_elements, std::vector <int> (4));
		m_layer_elements_type = std::vector<std::string>(m_elements);

		for (int i = 0; i < m_elements; ++i) {
			if (level.good()) {
				level >> m_layer_elements[i][0] >> m_layer_elements[i][1] >> m_layer_elements[i][2]
					>> m_layer_elements[i][3] >> m_layer_elements_type[i];
				//	m_layer_elements[i][0] += 128;
			}
		}
	}
	level.close();
}

void HudLayer::update(float deltaTime) {
	/* No need of update because we're using the sprite array as a set of stamps. */
}

void HudLayer::draw(sf::RenderWindow& App) {
	for(int i = 0; i < m_layer_elements_type.size(); ++i) {

			(*m_drawables[m_layer_elements_type[i]]).setPos(m_layer_elements[i][0], m_layer_elements[i][1]);
			(*m_drawables[m_layer_elements_type[i]]).setSize(m_layer_elements[i][2], m_layer_elements[i][3]);
			(*m_drawables[m_layer_elements_type[i]]).draw(App);	
	}
	//Falta agafar la informacio de quantes vides te el jugador
}

void HudLayer::superDraw(sf::RenderWindow& App, int element, float x_pos, float y_pos) {
	(*m_drawables[m_layer_elements_type[element]]).setPos(m_layer_elements[element][0], m_layer_elements[element][1]);
	(*m_drawables[m_layer_elements_type[element]]).setSize(m_layer_elements[element][2], m_layer_elements[element][3]);
	(*m_drawables[m_layer_elements_type[element]]).draw(App);	
}

