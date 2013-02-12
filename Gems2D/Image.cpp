#include "stdafx.h"
#include "Image.h"

Image::Image(void) { }

Image::Image(string path) {
	m_path = path;
}

Image::~Image(void) { }

sf::Texture& Image::getResource () {
	return m_image;
}

void Image::setResource (sf::Texture resource) {
	m_image = resource;
}

bool Image::load () {
	if (m_path != "") {
		if (!m_image.loadFromFile(m_path)) {
			return false;
		}
		m_sprite.setTexture(m_image);
		return true;
		
	}
	return false;
}

