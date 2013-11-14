#pragma once

#include "Structs.h"
#include "Sprite.h"

/* Class: Tile
   Brief: Tis class represents a tile of the game. */

class Piece {

public:

	/* CONSTRUCTORS */

	/* Empty constructor */
	Piece();

	Piece(int i);
	
	/* DESTRUCTORS */

	/* Empty destructor */
	~Piece();

	
	/* GETTERS */

	int getCityNumberGoingTo(int path);

	Farm getFarmGoingTo(int path);

	int getFarmNumberGoingTo(int path);

	std::vector<Abbey> getAbbeys();

	std::vector<Road> getRoads();

	std::vector<City> getCities();

	std::vector<Farm> getFarms();

	std::vector<int> getSides();

	int getOrientation();

	/* DOMAIN FUNCTIONS */
	
	/* Draws the layer on the window. Concretely, draws all the elements of the subrectangle of the image visible by the player on the window.
	   It would be good to define an offset range to precharge the elements */
	void draw(sf::RenderWindow& App);

private:
	
	std::vector<Abbey> abbeys;
	std::vector<Road> roads;
	std::vector<City> cities;
	std::vector<Farm> farms;
	std::vector<int> sides;
	sf::Sprite sprite;
	int orientation;
};
