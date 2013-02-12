#pragma once
#include <string>
#include "ResourceManager.h"

class Layer
{
public:

	virtual void setLayer(string path) = 0;

	virtual void draw(sf::RenderWindow& App) = 0;

};

