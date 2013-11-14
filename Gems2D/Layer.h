#pragma once
#include <string>
#include "Constants.h"
#include "ResourceManager.h"

/* Class: Layer
   Brief: This is an abstract class used to define the concept of "Layer". With this class you can use some abstract methods
          like the layer settings and the drawing. Useful for defining layer arrays or other abstract containers, for example. */

class Layer {

	public:

	/* ABSTRACT METHODS */

	/* Sets the layer presets, located on the file defined by path */
	virtual void setLayer(std::string path) = 0;

	/* Updates the layer according to the changes done on the current iteration of the game loop. */
	virtual void update(float deltaTime) = 0;

	/* Draws the layer on the window. Concretely, draws the subrectangle of the layer visible by the player on the window. */
	virtual void draw(sf::RenderWindow& App) = 0;

	/* This method is used to draw the layers using special rules. It is used situationally, but I have to polish it. 
	   It was first used during the Game&Bud development phase, to draw only some elements of the static layer, but i
	   thought it could be good to standarize a rewrittable drawing function. */
	virtual void superDraw (sf::RenderWindow& App, int element, float x_pos, float y_pos) = 0;

};

