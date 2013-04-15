#include "stdafx.h"
#include "Tileset.h"

Tileset::Tileset() {
    m_xpos = 0.f;
    m_ypos = 0.f;
    m_xsize = 0;
    m_ysize = 0;
    m_xelements = 1;
    m_yelements = 1;
}

Tileset::Tileset(int tiles_x, int tiles_y, Image* image) {
    m_xpos = 0;
    m_ypos = 0;
    m_Image = image;
	m_Sprite.setTexture(m_Image->getResource());
	m_xsize = m_Image->getResource().getSize().x;
    m_ysize = m_Image->getResource().getSize().y;
    m_xelements = tiles_x;
    m_yelements = tiles_y;
    m_Sprite.setPosition(m_xpos, m_ypos);
}

 Tileset::~Tileset() {

}

void Tileset::drawTile(int tile, float x_pos, float y_pos, sf::RenderWindow& App){
	if (tile >= 0) {
		setPos(x_pos, y_pos);
		setFocus(tile);
		draw(App);
	}
}

void Tileset::scaleTiles(float scaleFactor) {
	setSize(m_xsize*scaleFactor, m_ysize*scaleFactor);
}

