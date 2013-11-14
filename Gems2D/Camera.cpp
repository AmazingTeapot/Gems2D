#include "stdafx.h"
#include "Camera.h"
#include <iostream>

Camera::Camera(void) { }

Camera::~Camera(void) { }

void Camera::setWindowSize(int width, int height) {
	m_window_width = width;
	m_window_height = height;
	m_obs_x = (float)width/2;
	m_obs_y = (float)height/2;
}

void Camera::setLevelSize(int width, int height) {
	m_map_width = width;
	m_map_height = height;
}

std::pair<int, int> Camera::getWindowSize() {
	std::pair<int, int> p;
	p.first = m_window_width;
	p.second = m_window_height;
	return p;
}

std::pair<int, int> Camera::getLevelSize() {
	std::pair<int, int> p;
	p.first = m_map_width;
	p.second = m_map_height;
	return p;
}

std::pair<int, int> Camera::getObsPoint() {
	std::pair<int, int> p;
	p.first = (int)m_obs_x;
	p.second = (int)m_obs_y;
	return p;
}

std::pair<float, float> Camera::getPlayerPoint() {
	std::pair<float, float> p;
	p.first = m_player_x;
	p.second = m_player_y;
	return p;
}

void Camera::getDrawableArea(std::vector<int>& drawable) {
	drawable = *new std::vector<int>(4, 0);
	drawable[0] = (int)m_obs_x - m_window_width/2;
	drawable[1] = (int)m_obs_y - m_window_height/2;
	drawable[2] = (int)m_obs_x + m_window_width/2;
	drawable[3] = (int)m_obs_y + m_window_height/2;
}

void Camera::updateCameraPos (int player_x, int player_y) {
	if(player_x - m_obs_x >= m_window_width/4 && m_obs_x < m_map_width - m_window_width/2) m_obs_x += (player_x - m_obs_x - m_window_width/4);
	if(player_x - m_obs_x <= -m_window_width/4 && m_obs_x > m_window_width/2) m_obs_x += (player_x - m_obs_x + m_window_width/4);
	if(player_y - m_obs_y >= m_window_height/4 && m_obs_y < m_map_height - m_window_height/2) m_obs_y += (player_y - m_obs_y - m_window_height/4);
	if(player_y - m_obs_y <= -m_window_height/4 && m_obs_y > m_window_height/2) m_obs_y += (player_y - m_obs_y + m_window_height/4);
	m_player_x = player_x;
	m_player_y = player_y;
}


sf::Vector2<int> Camera::getMouseLevelPos() {
	sf::Vector2<int> position = sf::Mouse::getPosition();
	position.x = position.x + (int)m_obs_x - m_window_width/2;
	position.y = position.y + (int)m_obs_y - m_window_height/2;
	return position;
}

/* ESTO HAY QUE BORRARLO */

int Camera::getSteps() {
	return m_numSteps;
}

void Camera::setSteps(int i) {
	m_numSteps = i;
}
