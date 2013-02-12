#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Sprite.h"

using namespace std;

class Tileset: public Sprite {

private:

public:
	
	/* CONSTRUCTORS */

	// Empty constructor
	Tileset();

	// Constructor with a base path for the resource
	Tileset(int tiles_x, int tiles_y, Image* image);

	/* DESTRUCTORS */

	// Empty destructor
	~Tileset();
	
	/* DOMAIN FUNCTIONS */

	/* Drawing function. It draws the selected tile onto the selected position */
	void drawTile(int tile, float x_pos, float y_pos, sf::RenderWindow& App);

	/* Scaling factor. It lets you scale the size of the tiles */
	void scaleTiles(float scaleFactor);

};