#include "stdafx.h"
#include "Enemy1.h"
#include "GameManager.h"

Enemy1::Enemy1() { }

Enemy1::Enemy1(int sheetNumber) {
	m_actualAnimation = 1;
	m_border_left = 0;
	m_border_right = 0;
	m_direction = 1;
	alive = true;
	cont = 0;
	m_numberOfSheets = sheetNumber;
	m_animationSheets = std::vector<Sprite>(sheetNumber);
	m_position_x = 0;
	m_position_y = 0;
	m_size_x = 0;
	m_size_y = 0;
}

Enemy1::Enemy1(int sheetNumber, float pos_x, float pos_y, int max_left, int max_right) {
	m_actualAnimation = 1;
	m_position_x = pos_x;
	m_position_y = pos_y;
	m_border_left = max_left;
	m_border_right = max_right;
	m_direction = 1;
	alive = true;
	cont = 0;
	m_numberOfSheets = sheetNumber;
	m_animationSheets = std::vector<Sprite>(sheetNumber);
	m_position_x = 0;
	m_position_y = 0;
	m_size_x = 0;
	m_size_y = 0;
}

Enemy1::~Enemy1() {
}

void Enemy1::setBorders(int x, int y) {
	m_border_left = x;
	m_border_right = y;
}

std::pair<int, int> Enemy1::getBorders() {
	std::pair<int, int> ret;
	ret.first = m_border_left;
	ret.second = m_border_right;
	return ret;
}

void Enemy1::update(float deltaTime) {
	if (alive) {
		if (m_direction == 1) m_position_x += 300 * deltaTime;
		else m_position_x -= 300 * deltaTime;
		if (m_position_x >= m_border_right) {
			m_direction = -1;
			m_actualAnimation = 0;
		}
		else if (m_position_x <= m_border_left) {
			m_direction = 1;
			m_actualAnimation = 1;
		}
	}
	else cont += deltaTime * 10;

	if(cont < 10) m_animations[m_actualAnimation].animate(deltaTime);
	else {
		m_position_x = -500;
		m_position_y = -500;
	}
}

void Enemy1::die() {
	alive = false;
	m_actualAnimation = 2;
	/* Per deixar l'objecte Random, crear un Static element i posarlo a la Static Layer i que el pinti tot el rato fins que
	el personatge l'agafi, que llavors l'eliminem de la capa*/
}
