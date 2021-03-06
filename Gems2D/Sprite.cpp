#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite () {
    m_xpos = 0.f;
    m_ypos = 0.f;
    m_xsize = 1;
    m_ysize = 1;
    m_xelements = 0;
    m_yelements = 0;
	m_imageSize_x = 0;
	m_imageSize_y = 0;
	m_anchor_x = 0;
	m_anchor_y = 0;
}

Sprite::Sprite (Image* image) {
    m_xpos = 0.f;
    m_ypos = 0.f;
	m_Image = image;
	m_Sprite.setTexture(m_Image->getResource());
	m_xsize = m_Image->getResource().getSize().x;
    m_ysize = m_Image->getResource().getSize().y;
	m_imageSize_x = m_xsize;
	m_imageSize_y = m_ysize;
	m_xelements = 0;
    m_yelements = 0;
	m_anchor_x = 0;
	m_anchor_y = 0;
}

Sprite::Sprite(float xpos, float ypos, Image* image) {
    m_xpos = xpos;
    m_ypos = ypos;
    m_Image = image;
	m_Sprite.setTexture(m_Image->getResource());
	m_xsize = m_Image->getResource().getSize().x;
    m_ysize = m_Image->getResource().getSize().y;
	m_imageSize_x = m_xsize;
	m_imageSize_y = m_ysize;
	m_xelements = 0;
    m_yelements = 0;
    m_Sprite.setPosition(m_xpos, m_ypos);
	m_anchor_x = 0;
	m_anchor_y = 0;
}

Sprite::Sprite(float xpos, float ypos, int xsize, int ysize, Image* imagen) {
    m_xpos = xpos;
    m_ypos = ypos;
	m_Image = imagen;
	m_Sprite.setTexture(m_Image->getResource());
    m_xsize = xsize;
    m_ysize = ysize;
    m_xelements = 0;
    m_yelements = 0;
	m_imageSize_x = m_Image->getResource().getSize().x;
	m_imageSize_y = m_Image->getResource().getSize().y;
	m_Sprite.setPosition(m_xpos, m_ypos);
	m_Sprite.setScale(xsize/(float)m_imageSize_x, ysize/(float)m_imageSize_y);
}

 Sprite::~Sprite() {

}

void Sprite::setPos(float xpos, float ypos) {
    m_Sprite.setPosition(xpos, ypos);
    m_xpos = xpos - m_xsize;
    m_ypos = ypos - m_ysize;
}

void Sprite::setSize(int xsize, int ysize) {
	if(xsize != 0 && ysize != 0) m_Sprite.setScale((float)xsize/(float)m_xsize, (float)ysize/(float)m_ysize);
}

void Sprite::setSubRect(int left, int up, int right, int down) {
    sf::IntRect P(left, up, right, down);
	m_Sprite.setTextureRect(P);
}

void Sprite::setImage(Image* imagen) {
    m_Image = imagen;
	m_Sprite.setTexture(m_Image->getResource());
	setSize(imagen->getResource().getSize().x, imagen->getResource().getSize().y);
	m_imageSize_x = m_xsize;
	m_imageSize_y = m_ysize;
}

void Sprite::setTileset(int xelem, int yelem, int pos) {
    m_xelements = xelem;
    m_yelements = yelem;
    int x_offset = pos%xelem;
    x_offset *= m_imageSize_x/xelem;
    int y_offset = pos/xelem;
    y_offset *= m_imageSize_y/yelem;
    this->setSubRect(x_offset, y_offset, m_imageSize_x/xelem, m_imageSize_x/yelem);
}

void Sprite::setFocus(int pos) {
    int x_offset = pos%m_xelements;
    x_offset *= m_Image->getResource().getSize().x/m_xelements;
    int y_offset = pos/m_xelements;
    y_offset *= m_Image->getResource().getSize().y/m_yelements;
    this->setSubRect(x_offset, y_offset, m_Image->getResource().getSize().x/m_xelements, m_Image->getResource().getSize().y/m_yelements);
}

void Sprite::setSprite(sf::Sprite sprite) {
	m_Sprite = sprite;
}

void Sprite::setAnchorPoint(float x, float y) {
	m_anchor_x = (int)x;
	m_anchor_y = (int)y;
	m_Sprite.setOrigin(x, y);
}

std::pair<float, float> Sprite::getPos() {
    std::pair<float, float> pos;
    pos.first = m_xpos + m_xsize;
    pos.second = m_ypos + m_ysize;
    return pos;
}

std::pair<int, int> Sprite::getSize() {
    std::pair <int, int> size;
    size.first = m_xsize;
    size.second = m_ysize;
    return size;
}

std::pair<float, float> Sprite::getAnchorPoint() {
    std::pair<float, float> anchor;
    anchor.first = (float)m_anchor_x;
    anchor.second = (float)m_anchor_y;
    return anchor;
}

void Sprite::move(float i, float j) {
    m_xpos = m_xpos + i;
    m_ypos = m_ypos + j;
    m_Sprite.setPosition(m_xpos, m_ypos);
}

void Sprite::rotate(float i) {
    m_Sprite.setRotation(i);
}

void Sprite::draw(sf::RenderWindow& App) {
    App.draw(m_Sprite);
}

bool Sprite::isPressed(float x, float y) {
    if (x > m_xpos && x < m_xpos + m_xsize) {
        if (y > m_ypos && y < m_ypos + m_ysize) return true;
        return false;
    }
    return false;
}