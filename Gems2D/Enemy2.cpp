#include "stdafx.h"
#include "Enemy2.h"
#include "Camera.h"


Enemy2::Enemy2() {
}

Enemy2::Enemy2(int sheetNumber) {
	m_actualAnimation = 1;
	max_height = 0;
	cont = 0;
	m_numberOfSheets = sheetNumber;
	m_animationSheets = std::vector<Sprite>(sheetNumber);
	m_position_x = 0;
	m_position_y = 0;
	m_size_x = 0;
	m_size_y = 0;
	alive = true;
	up = true;
}

Enemy2::Enemy2(int sheetNumber, int pos_x, int max_height) {
	m_actualAnimation = 1;
	m_position_x = pos_x;
	m_position_y = 1500;
	this->max_height = max_height;
	cont = 0;
	m_numberOfSheets = sheetNumber;
	m_animationSheets = std::vector<Sprite>(sheetNumber);
	m_position_x = 0;
	m_position_y = 0;
	m_size_x = 0;
	m_size_y = 0;
	alive = true;
	up = true;
}

Enemy2::~Enemy2() {
}

void Enemy2::setMaxHeight(int h) {
	max_height = h;
}

int Enemy2::getMaxHeight() {
	return max_height;
}

void Enemy2::update(float deltaTime) { 
	float pos_player = Camera::getInstance()->getPlayerPoint().first;
	if (alive) {
		if (m_position_x > pos_player) m_actualAnimation = 0;
		else m_actualAnimation = 1;
		if (up) m_position_y -= deltaTime * 300;
		else m_position_y += deltaTime * 300;
		if (m_position_y <= max_height) up = false;
		else if (m_position_y >= 2000) up = true;
	}

	else cont += deltaTime * 10;

	if (cont < 10) m_animations[m_actualAnimation].animate(deltaTime);
	else {
		m_position_x = -500;
		m_position_y = -500;
	}
}

void Enemy2::die() {
	alive = false;
	m_actualAnimation = 2;
}

