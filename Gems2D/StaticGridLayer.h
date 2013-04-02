#pragma once
#include "Layer.h"
#include "Camera.h"
#include "Tileset.h"

/* Class: Static Grid Layer
   Brief: This kind of layer displays a group of tiles from a tileset. It can be used to draw backgrounds, big elements...
          It is also an easy way simplify the collisions. */

class StaticGridLayer : public Layer {

	public:

	/* CONSTRUCTORS */

	/* Empty constructor. */
	StaticGridLayer();

	/* This constructor loads the tileset. You have to provide the image source of the tileset and how much
	   tiles does it have (length and width) */
	StaticGridLayer(Image* tileset, int tiles_x, int tiles_y);


	/* DESTRUCTORS */

	/* Empty destructor. */
	~StaticGridLayer();

	/* SETTERS */
	
	/* It sets the tileset we're going to use the same way as we do in the constructor. We need the image source
	   and how many tiles does it have (length and width). */
	void setTileset (Image* tileset, int tiles_x, int tiles_y);

	/* Sets the layer presets, located on the file defined by path */
	virtual void setLayer (string level_map);
	
	/* DOMAIN FUNCTIONS */

	/* Updates the position of the background image according to the observer */
	virtual void update ();

	/* Draws the layer on the window. Concretely, draws the tiles visible by the player on the window. */
	virtual void draw (sf::RenderWindow& App);

	private:
	Tileset m_tileset;
	int m_tiles_x;
	int m_tiles_y;     
	int m_tile_size_x;
	int m_tile_size_y;
	vector<vector <int>> m_layer_map;

};
