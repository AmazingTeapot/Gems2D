#pragma once
#include <string>
#include "ResourceManager.h"

/* Class: Layer
   Brief: This is an abstract class used to define the concept of "Layer". With this class you can use some abstract methods
          like the layer settings and the drawing. Useful for defining layer arrays or other abstract containers, for example. */

class Layer {

	public:

	/* ABSTRACT METHODS */

	/* Sets the layer presets, located on the file defined by path */
	virtual void setLayer(string path) = 0;

	/* Updates the layer according to the changes done on the current iteration of the game loop. */
	virtual void update(float deltaTime) = 0;

	/* Draws the layer on the window. Concretely, draws the subrectangle of the layer visible by the player on the window. */
	virtual void draw(sf::RenderWindow& App) = 0;

};

