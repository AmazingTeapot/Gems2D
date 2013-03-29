#pragma once
#include <string>
#include <vector>
#include "Tileset.h"
#include "Camera.h"
#include "StaticGridLayer.h"
#include "MovingImageLayer.h"
#include "StaticElementsLayer.h"
#include "AnimatedElementsLayer.h"

/* Class: Level
   Brief: This class will be used as an utility to implement every level. It has some basic methods and, for every level, an inherited
          class with specific code will be needed.. */

/* THIS CLASS IS UNDER CONSTRUCTION */

class Level {

	public:

	/* CONSTRUCTORS */

	/* Empty constructor */
	Level();


	/* DESTRUCTORS */
	
	/* Empty destructor */
	~Level();


	/* SETTERS */

	/* Layer setter - to be implemented. */
	void setLayer1 (string path);


	/* DOMAIN FUNCTIONS */

	/* This function draws all the layers on the scene */
	void draw(sf::RenderWindow& App);

	/* This function acts as a handler. It handles all the events sent by the manager and acts consequently. */
	void eventHandler (int x);


	private:
	int m_size_x;
	int m_size_y;
	vector<Layer*> m_layers;
	float center_x;
	float center_y;
	float obs_x;
	float obs_y;
};