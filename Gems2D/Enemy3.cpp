#include "stdafx.h"
#include "Enemy3.h"
#include "Camera.h"

Enemy3::Enemy3() {
}

Enemy3::Enemy3(int sheetNumber) {
	m_actualAnimation = 1;
	m_border_left = 0;
	m_border_right = 0;
	m_direction = -1;
	cont = 0;
	m_numberOfSheets = sheetNumber;
	m_animationSheets = std::vector<Sprite>(sheetNumber);
	m_position_x = 0;
	m_position_y = 0;
	m_size_x = 0;
	m_size_y = 0;
	alive = true;
}

Enemy3::Enemy3(int sheetNumber, int pos_x, int pos_y, int max_left, int max_right) {
	m_actualAnimation = 1;
	m_position_x = pos_x;
	m_position_y = pos_y;
	m_border_left = max_left;
	m_border_right = max_right;
	m_direction = -1;
	cont = 0;
	m_numberOfSheets = sheetNumber;
	m_animationSheets = std::vector<Sprite>(sheetNumber);
	m_position_x = 0;
	m_position_y = 0;
	m_size_x = 0;
	m_size_y = 0;
	alive = true;
}

Enemy3::~Enemy3() {
}

void Enemy3::setBorders(int x, int y) {
	m_border_left = x;
	m_border_right = y;
}

std::pair<int, int> Enemy3::getBorders() {
	std::pair<int, int> ret;
	ret.first = m_border_left;
	ret.second = m_border_right;
	return ret;
}

void Enemy3::update(float deltaTime) {
	float pos_player_x = Camera::getInstance()->getPlayerPoint().first;
	float pos_player_y = Camera::getInstance()->getPlayerPoint().second;
	if (alive) {
		if (m_position_x > pos_player_x) {
			m_actualAnimation = 1;
			if (m_position_x < m_border_left) {
				m_position_x = m_border_left;
				m_actualAnimation = 3;
			}
			if (m_position_x - pos_player_x < 450 && m_position_x - pos_player_x > 50 && m_position_y - pos_player_y < 80 && m_position_y - pos_player_y > 0 && m_position_x != m_border_left) {
				m_actualAnimation = 0;
				m_position_x -= 200 * deltaTime;
			}
		}
		else {
			m_actualAnimation = 3;
			if (m_position_x > m_border_right) {
				m_position_x = m_border_right;
				m_actualAnimation = 1;
			}
			if (m_position_x - pos_player_x > -450 && m_position_x - pos_player_x < -50 && m_position_y - pos_player_y < 80 && m_position_y - pos_player_y > 0 && m_position_x != m_border_right) {
				m_actualAnimation = 2;
				m_position_x += 200 * deltaTime;
			}
		}
	}
	else cont += deltaTime * 10;

	if (cont < 10) m_animations[m_actualAnimation].animate(deltaTime);
	else {
		m_position_x = -500;
		m_position_y = -500;
	}
}


void Enemy3::die() {
	alive = false;
	m_actualAnimation = 4;
}

