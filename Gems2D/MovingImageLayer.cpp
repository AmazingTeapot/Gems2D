#include "stdafx.h"
#include "MovingImageLayer.h"


MovingImageLayer::MovingImageLayer() {
	m_image_size_x = 0;
	m_image_size_y = 0;
	m_scene_size_x = Camera::getInstance()->getLevelSize().first;
	m_scene_size_y = Camera::getInstance()->getLevelSize().second;
	m_window_size_x = Camera::getInstance()->getWindowSize().first;
	m_window_size_y = Camera::getInstance()->getWindowSize().second;
}

MovingImageLayer::MovingImageLayer(Image* i) {
	Sprite s(0, 0, i);
	m_background = s;
	m_image_size_x = s.getSize().first;
	m_image_size_y = s.getSize().second;
	m_scene_size_x = Camera::getInstance()->getLevelSize().first;
	m_scene_size_y = Camera::getInstance()->getLevelSize().second;
	m_window_size_x = Camera::getInstance()->getWindowSize().first;
	m_window_size_y = Camera::getInstance()->getWindowSize().second;
}

MovingImageLayer::~MovingImageLayer() { }

void MovingImageLayer::setLayer (std::string path) {
	m_background.setImage(ResourceManager::getInstance()->getImage(path));
	m_image_size_x = m_background.getSize().first;
	m_image_size_y = m_background.getSize().second;
}

void MovingImageLayer::update (float deltaTime) {
	int x_position=(double)((double)(Camera::getInstance()->getObsPoint().first-m_window_size_x/2)/(double)(m_scene_size_x-m_window_size_x))*(double)(m_image_size_x-m_window_size_x);
	int y_position=(double)((double)(Camera::getInstance()->getObsPoint().second-m_window_size_y/2)/(double)(m_scene_size_y-m_window_size_y))*(double)(m_image_size_y-m_window_size_y);
	m_background.setPos(-x_position, -y_position);
}
void MovingImageLayer::draw (sf::RenderWindow& App) {
	m_background.draw(App);
}

void MovingImageLayer::superDraw  (sf::RenderWindow& App, int element, float x_pos, float y_pos) { 
	m_background.draw(App);
}