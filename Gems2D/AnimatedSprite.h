#pragma once

#include <vector>
#include "Sprite.h"
#include "Animation.h"

using namespace std;

/* Class: Animated Sprite
   Brief: This class extends the concept of Sprite. It adapts an sprite to work with animations.
		  It has some animation sheets as resources (that are, in fact, SFML Textures) and has a bunch
		  of "Animation" objects mapped to all the Animated Sprite 'actions' */

class AnimatedSprite {

	public:

	/* CONSTRUCTORS */

	/* Empty constructor. It sets the number of animation sheets to 1 by default */
	AnimatedSprite();

	/* With this constructor you can set the number of animation sheets the animated sprite will have */
	AnimatedSprite(int sheets);


	/* DESTRUCTORS */

	/* Empty destructor */
	~AnimatedSprite();


	/* DOMAIN FUNCTIONS */

	/* This function matches the associated resource "sheetName" to the sheet number indicated. 
	   SheetName is the name of an image. */
	void loadSheet(int sheetNumber, string sheetName);

	/* This function takes the name of a file that has all the animation coordinates of all the actions 
	   of the Animated Sprite stored, and it creates and initializes an "Animation" object for every action on the file. */
	void loadAnimations(string file);

	/* SETTERS */

	/* Sets the position of the animated sprite to (x, y) */
	void setPosition(int x, int y);

	/* Sets the actual animation to i */
	void setAnimation(int i);


	/* GETTERS */

	/* This functions returns the position of the animated sprite, related to the level. */
	pair<int, int> getPosition();

	/* This functions returns the size of the animated sprite */
	pair <int, int> getSize();

	/* This functions returns the id of the actual animation */
	int getAnimation();


	/* DOMAIN FUNCTIONS */

	/* It draws the animated sprite on the screen. */
	void draw(sf::RenderWindow& App);

	private:
	vector<Animation> m_animations;
	vector<Sprite> m_animationSheets;
	int m_actualAnimation;
	int m_numberOfSheets;
	int m_position_x;
	int m_position_y;
	int m_size_x;
	int m_size_y;
};