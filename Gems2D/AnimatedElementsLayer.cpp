#include "stdafx.h"
#include "Layer.h"
#include "Camera.h"
#include "Sprite.h"
#include "AnimatedElementsLayer.h"
#include "ResourceManager.h"
#include <fstream>
#include <iostream>

using namespace std;

AnimatedElementsLayer::AnimatedElementsLayer() { 
	m_elements = 0;
	m_level_folder = "";
}

AnimatedElementsLayer::~AnimatedElementsLayer() { }

void AnimatedElementsLayer::setLayer (string level_elements) {
	ifstream level (LEVEL_PATH + level_elements + "/animated_elem" + LEVEL_EXTENSION);
	if (level.is_open()) {
		if(level.good()) level >> m_elements;
		vector<AnimatedSprite> aux(m_elements);
		for(int i = 0; i < m_elements; ++i) {
			int sheets, x_pos, y_pos;
			string res_name, res_folder;
			if(level.good()) level >> sheets >> res_name >> res_folder;
			AnimatedSprite anim(sheets);
			for (int j = 0; j < sheets; ++j) {
				if(!ResourceManager::getInstance()->checkImage(res_name + "_sheet_" + to_string(j+1))) {
					ResourceManager::getInstance()->loadImage(res_name + "_sheet_" + to_string(j+1), res_folder + "/" + res_name + "_sheet_" + to_string(j+1));
				}
				anim.loadSheet(j+1, res_name + "_sheet_" + to_string(j+1));
			}
			anim.loadAnimations(res_name);
			if(level.good()) level >> x_pos >> y_pos;
			anim.setPosition(x_pos, y_pos);
			aux[i] = anim;
		}
		m_layer_elements = aux;
		level.close();
	}
}

void AnimatedElementsLayer::draw (sf::RenderWindow& App) {
	vector<int> drawableArea;
	Camera::getInstance()->getDrawableArea(drawableArea);
	
	int window_size_x = Camera::getInstance()->getWindowSize().first;
	int window_size_y = Camera::getInstance()->getWindowSize().second;
	
	for(int i = 0; i < m_layer_elements.size(); ++i) {
		if (isDrawable(m_layer_elements[i], drawableArea)) {
			m_layer_elements[i].draw(App);
		}
	}
}

bool AnimatedElementsLayer::isDrawable(AnimatedSprite anim, vector<int> drawableArea) {
	int anim_x = anim.getPosition().first;	
	int anim_y = anim.getPosition().second;
	int anim_x_size = anim.getSize().first;
	int anim_y_size = anim.getSize().second;

	return(anim_x+anim_x_size > drawableArea[0] && anim_y+anim_y_size > drawableArea[1] && 
    anim_x < drawableArea[2] && anim_y < drawableArea[3]);
}
