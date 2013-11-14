#pragma once
#include "Structs.h"
#include "Sprite.h"

/* Class: Tile
   Brief: Tis class represents a tile of the game. */

class Tile  {

public:

	/* CONSTRUCTORS */

	/* Empty constructor */
	Tile();

	Tile(int i);
	
	/* DESTRUCTORS */

	/* Empty destructor */
	~Tile();

	
	/* GETTERS */


	/* DOMAIN FUNCTIONS */
	
	/* Draws the layer on the window. Concretely, draws all the elements of the subrectangle of the image visible by the player on the window.
	   It would be good to define an offset range to precharge the elements */
	void draw(sf::RenderWindow& App);

private:
	

};
