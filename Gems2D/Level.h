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
   Brief: This class will be used as an utility to implement every level. It has some basic methods and, for some levels, an inherited
          class with more specific code can be used (for example, underwater themed levels). This functions are orientative, and the developer
		  must use it as he or she wants. */

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

	/* Layer loader. This is used to load the various layers of the level. */
	void setLayers (string path);

	/* This function can be useful to load the world parameters, or other initializations. */
	void loadWorld();

	/* This is the function that handles the game over event. */
	void gameOver();

	/* DOMAIN FUNCTIONS */

	/* This function updates all the elements */
	void update(float deltaTime);

	/* This function draws all the layers on the scene */
	void draw(sf::RenderWindow& App);

	/* This function acts as a handler. It handles all the events sent by the manager and acts consequently. */
	void eventHandler (int x);


	private:
	vector<int> events;
	int m_size_x;
	int m_size_y;
	vector<Layer*> m_layers;
	float center_x;
	float center_y;
	float obs_x;
	float obs_y;

	/* Game Variables */


};