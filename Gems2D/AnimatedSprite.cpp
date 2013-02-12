#include "stdafx.h"
#include <fstream>
#include "AnimatedSprite.h"
#include "ResourceManager.h"
#include "Camera.h"

const string ANIMATION_PATH = "./Resources/Graphics/AnimatedSprites/";
const string LEVEL_EXTENSION = ".txt";

AnimatedSprite::AnimatedSprite() { 
	m_actualAnimation = 0;
	m_numberOfSheets = 1;
 
	int force_x = 0;
	int force_y = -GRAVITY;
	int velocity_x = 0;
	int velocity_y = 0;
	int next_position_x = m_position_x;
	int next_position_y = m_position_y;
}

AnimatedSprite::AnimatedSprite(int sheetNumber) { 
	m_actualAnimation = 0;
	m_numberOfSheets = sheetNumber;
	vector<Sprite> aux (sheetNumber);
	m_animationSheets = aux;
	
	int force_x = 0;
	int force_y = -GRAVITY;
	int velocity_x = 0;
	int velocity_y = 0;
	int next_position_x = m_position_x;
	int next_position_y = m_position_y;

}

AnimatedSprite::~AnimatedSprite() { }

void AnimatedSprite::loadSheet(int sheetNumber, string sheetName) {
	Sprite s (ResourceManager::getInstance()->getImage(sheetName));	
	m_animationSheets[sheetNumber-1] = s;
}

void AnimatedSprite::loadAnimations(string file) {
	int num_anim;
	int left, up, height, width;
	ifstream animations (ANIMATION_PATH + file + "_anim" + LEVEL_EXTENSION);
	if (animations.is_open()) {
		if(animations.good()) animations >> num_anim;
		vector<Animation> anims(num_anim);
		for (int i = 0; i < num_anim; ++i) {
			int sheet, steps;
			if(animations.good()) animations >> sheet >> steps;
			Animation a(sheet);
			for(int j = 0; j < steps; ++j) {
				if(animations.good()) animations >> left >> up >> height >> width;
				a.addStep(left, up, height, width);
				m_size_x = height;
				m_size_y = width;
			}
			anims[i] = a;
		}
		m_animations = anims;
		animations.close();
	}
}

void AnimatedSprite::setPosition(int x, int y) {
	m_position_x = x;
	m_position_y = y;
}

pair<int, int> AnimatedSprite::getPosition() {
	pair<int, int> ret;
	ret.first = m_position_x;
	ret.second = m_position_y;
	return ret;
}

pair <int, int> AnimatedSprite::getSize() {
	pair<int, int> ret;
	ret.first = m_size_x;
	ret.second = m_size_y;
	return ret;	
}

void AnimatedSprite::setAnimation(int i) {
	m_actualAnimation = i;
}

int AnimatedSprite::getAnimation() {
	return m_actualAnimation;
}

void AnimatedSprite::draw(sf::RenderWindow& App) {
	int x_max = m_position_x + force_x; 
	int y_max = m_position_y + force_y;
	force_y -= GRAVITY;
	m_position_x = x_max;
	m_position_y = y_max;
	
	vector<int>paint_area = m_animations[0].animate();
	m_animationSheets[paint_area[0]-1].setPos(m_position_x - Camera::getInstance()->getObsPoint().first + Camera::getInstance()->getWindowSize().first/2, 
				m_position_y - Camera::getInstance()->getObsPoint().second + Camera::getInstance()->getWindowSize().second/2);
	m_animationSheets[paint_area[0]-1].setSubRect(paint_area[1], paint_area[2], paint_area[3], paint_area[4]);
	m_animationSheets[paint_area[0]-1].draw(App);
	m_size_x = paint_area[3];
	m_size_y = paint_area[4];
}