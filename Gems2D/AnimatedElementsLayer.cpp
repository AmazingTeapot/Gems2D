#include "stdafx.h"
#include "Layer.h"
#include "Camera.h"
#include "Sprite.h"
#include "AnimatedElementsLayer.h"
#include "ResourceManager.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include <fstream>
#include <iostream>

AnimatedElementsLayer::AnimatedElementsLayer() { 
	m_elements = 0;
	m_level_folder = "";
	m_layer_enemy1 = std::vector<Enemy*>(0);

}

AnimatedElementsLayer::~AnimatedElementsLayer() { }

void AnimatedElementsLayer::setLayer (std::string level_elements) {
	std::ifstream level (LEVEL_PATH + level_elements + "/animated_elem" + LEVEL_EXTENSION);
	if (level.is_open()) {
		if(level.good()) level >> m_elements;
		m_layer_elements = *new std::vector<AnimatedSprite>(m_elements);
		for(int i = 0; i < m_elements; ++i) {
			int sheets, x_pos, y_pos;
			std::string res_name, res_folder;
			if(level.good()) level >> sheets >> res_name >> res_folder;
			AnimatedSprite anim(sheets);
			for (int j = 0; j < sheets; ++j) {
				if(!ResourceManager::getInstance()->checkImage(res_name + "_sheet_" + std::to_string(j+1))) {
					ResourceManager::getInstance()->loadImage(res_name + "_sheet_" + std::to_string(j+1), ANIMATED_ELEMENTS_LAYER_PATH + res_name + "_sheet_" + std::to_string(j+1));
				}
				anim.loadSheet(j+1, res_name + "_sheet_" + std::to_string(j+1));
			}
			anim.loadAnimations(res_name);
			if(level.good()) level >> x_pos >> y_pos;
			anim.setPosition(x_pos, y_pos);
			m_layer_elements[i] = anim;
		}
		level.close();
	}
	std::ifstream level2(LEVEL_PATH + level_elements + "/animated_enemy1" + LEVEL_EXTENSION);
	if (level2.is_open()) {
		if (level2.good()) level2 >> m_elements;
		m_layer_enemy1 = std::vector<Enemy*>(m_elements);
		for (int i = 0; i < m_elements; ++i) {
			int sheets, x_pos, y_pos, max_left, max_right, max_height, type;
			std::string res_name, res_folder;
			Enemy* en;
			if (level2.good()) level2 >> sheets >> res_name >> type >> res_folder;
			switch (type) {
			case 1:
				if (level2.good()) level2 >> x_pos >> y_pos >> max_left >> max_right;
				en = new Enemy1(sheets);
				((Enemy1*)en)->setBorders(max_left, max_right);
				((Enemy1*)en)->setPosition(x_pos, y_pos);
				for (int j = 0; j < sheets; ++j) {
					if (!ResourceManager::getInstance()->checkImage(res_name + "_sheet_" + std::to_string(j + 1))) {
						ResourceManager::getInstance()->loadImage(res_name + "_sheet_" + std::to_string(j + 1), ANIMATED_ELEMENTS_LAYER_PATH + res_name + "_sheet_" + std::to_string(j + 1));
					}
					en->loadSheet(j + 1, res_name + "_sheet_" + std::to_string(j + 1));
				}
				en->loadAnimations(res_name);
				m_layer_enemy1[i] = en;
				break;
			case 2:
				en = new Enemy2(sheets);
				if (level2.good()) level2 >> x_pos >> y_pos >> max_height;
				((Enemy2*)en)->setMaxHeight(max_height);
				((Enemy2*)en)->setPosition(x_pos, y_pos);
				for (int j = 0; j < sheets; ++j) {
					if (!ResourceManager::getInstance()->checkImage(res_name + "_sheet_" + std::to_string(j + 1))) {
						ResourceManager::getInstance()->loadImage(res_name + "_sheet_" + std::to_string(j + 1), ANIMATED_ELEMENTS_LAYER_PATH + res_name + "_sheet_" + std::to_string(j + 1));
					}
					en->loadSheet(j + 1, res_name + "_sheet_" + std::to_string(j + 1));
				}
				en->loadAnimations(res_name);
				m_layer_enemy1[i] = en;
				break;
				
				break;
			case 3:
				if (level2.good()) level2 >> x_pos >> y_pos >> max_left >> max_right;
				en = new Enemy3(sheets);
				((Enemy3*)en)->setBorders(max_left, max_right);
				((Enemy3*)en)->setPosition(x_pos, y_pos);
				for (int j = 0; j < sheets; ++j) {
					if (!ResourceManager::getInstance()->checkImage(res_name + "_sheet_" + std::to_string(j + 1))) {
						ResourceManager::getInstance()->loadImage(res_name + "_sheet_" + std::to_string(j + 1), ANIMATED_ELEMENTS_LAYER_PATH + res_name + "_sheet_" + std::to_string(j + 1));
					}
					en->loadSheet(j + 1, res_name + "_sheet_" + std::to_string(j + 1));
				}
				en->loadAnimations(res_name);
				m_layer_enemy1[i] = en;
				break;
			}
		}
		level2.close();
	}
}

void AnimatedElementsLayer::update(float deltaTime) {
	for(int i = 0; i < m_layer_elements.size(); ++i) {
		m_layer_elements[i].update(deltaTime);
	}
	for (int i = 0; i < m_layer_enemy1.size(); ++i) {
		m_layer_enemy1[i]->update(deltaTime);
	}
}

void AnimatedElementsLayer::changeAnimation(int element, int animation) {
	m_layer_elements[element].setAnimation(animation);
}

void AnimatedElementsLayer::changePosition(int element, int x, int y) {
	m_layer_elements[element].setPosition(x, y);
}


std::vector<AnimatedSprite> AnimatedElementsLayer::getAnimatedSprites() {
	return m_layer_elements;
}

std::vector<Enemy*> AnimatedElementsLayer::getAnimatedEnemies() {
	return m_layer_enemy1;
}

int AnimatedElementsLayer::getActualAnimation(int element) {
	return m_layer_elements[element].getAnimation();
}

void AnimatedElementsLayer::kill(int i) {
	m_layer_enemy1[i]->die();
}

void AnimatedElementsLayer::draw (sf::RenderWindow& App) {
	std::vector<int> drawableArea;
	Camera::getInstance()->getDrawableArea(drawableArea);
	
	int window_size_x = Camera::getInstance()->getWindowSize().first;
	int window_size_y = Camera::getInstance()->getWindowSize().second;
	
	for(int i = 0; i < m_layer_elements.size(); ++i) {
		if (isDrawable(m_layer_elements[i], drawableArea)) {
			m_layer_elements[i].draw(App);
		}
	}
	for (int i = 0; i < m_layer_enemy1.size(); ++i) {
		if (isDrawable((AnimatedSprite)*m_layer_enemy1[i], drawableArea)) {
			m_layer_enemy1[i]->draw(App);
		}
	}
}

void AnimatedElementsLayer::superDraw (sf::RenderWindow& App, int element, float x_pos, float y_pos) { }

bool AnimatedElementsLayer::isDrawable(AnimatedSprite anim, std::vector<int> drawableArea) {
	int anim_x = anim.getPosition().first;	
	int anim_y = anim.getPosition().second;
	int anim_x_size = anim.getSize().first;
	int anim_y_size = anim.getSize().second;

	return(anim_x+anim_x_size > drawableArea[0] && anim_y+anim_y_size > drawableArea[1] && 
    anim_x < drawableArea[2] && anim_y < drawableArea[3]);
}
