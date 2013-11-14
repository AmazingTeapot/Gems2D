#pragma once

#include <string>
#include <vector>
#include "Tile.h"
#include "Camera.h"
#include "StaticGridLayer.h"
#include "MovingImageLayer.h"
#include "StaticElementsLayer.h"
#include "AnimatedElementsLayer.h"
#include "HudLayer.h"
#include "Box2D.h"
#include "SFML\Audio.hpp"

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

	/* On this constructor the level name is specified by the user */
	Level(std::string levelName);

	/* DESTRUCTORS */
	
	/* Empty destructor */
	~Level();


	/* SETTERS */

	/* Layer loader. This is used to load the various layers of the level. */
	void setLayers();

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

	/* GAME FUNCTIONS */

	private:
	std::vector<int> events;
	int m_size_x;
	int m_size_y;
	bool m_ifClicked;
	std::string m_levelName;
	std::vector<Layer*> m_layers;
	float center_x;
	float center_y;
	float obs_x;
	float obs_y;
	std::vector<int> m_toDraw;

	/* Game Variables */
	b2World world;
	std::vector<b2Fixture*> whipSensorFixtures;
	std::vector<b2Body*> groundBody;
	std::vector<b2Body*> enemyBody;
	b2PolygonShape groundBox;
	b2Body* body;
	b2PolygonShape dynamicBox;
	std::vector<bool> states;
	float candle_time;
	int iter;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	float whip_counter;
	std::vector<Sprite*> whip_sprites;
	bool breakable_broken;
	bool got_key;
	bool fixtured;
	int whippitywhoop;
	bool doorOpen;
	std::vector<bool> materials;
	std::vector<bool> blueprints;
	std::vector<int> drop;
	bool craftMode;
	int selection;
	bool spikedBoots;
	bool jumpingBoots;
	bool shield;
	int arrowPosition;
	int life;
	float invulnerability_time;
	std::vector<bool> dead;
};