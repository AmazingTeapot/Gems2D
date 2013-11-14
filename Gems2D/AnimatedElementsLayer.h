#pragma once
#include "stdafx.h"
#include "Layer.h"
#include "Camera.h"
#include "Sprite.h"
#include "Enemy1.h"
#include "ResourceManager.h"
#include "AnimatedSprite.h"		
#include <fstream>
#include <iostream>

/* Class: Animated Elements Layer
   Brief: With this kind of layer it is possible to display image resources. This resources can have some animations
		  defined. They will have animation sheets with all the "steps".
		  On one layer of this kind we'll draw the player.
		  If you draw this layer after the player layer is drawn, the objects will cover the player. */

class AnimatedElementsLayer : public Layer {

	public:

	/* CONSTRUCTORS */

	/* Empty constructor */
	AnimatedElementsLayer();

	
	/* DESTRUCTORS */

	/* Empty destructor */
	~AnimatedElementsLayer();

	
	/* SETTERS */

	/* Sets the layer presets, located on the file defined by path */
	virtual void setLayer(std::string path);

	/* Changes the current animation of the element "element" to "animation" */
	void changeAnimation(int element, int animation);

	/* Changes the position of the element "element" to "x" and "y" */
	void changePosition(int element, int x, int y);

	/* Returns the actual animation of the element "element" */
	int getActualAnimation(int element);


	/* GETTERS */ 
	
	/* Gets the animated elements of the layer */
	std::vector<AnimatedSprite> getAnimatedSprites();

	/* Gets the animated enemies -> WE NEED A NEW MODULE FOR THIS */
	std::vector<Enemy*> getAnimatedEnemies();

	void kill(int i);

	/* DOMAIN FUNCTIONS */
	
	/* Updates the position of the background image according to the observer */
	virtual void update (float deltaTime);

	/* Draws the layer on the window. Concretely, draws all the elements of the subrectangle of the image visible by the player on the window.
	   It would be good to define an offset range to precharge the elements */
	virtual void draw(sf::RenderWindow& App);

	/* This method is used to write only some of the layers. It is used situationally, but I have to polish it. It was useful during
	   the Game&Bud development phase. */
	virtual void superDraw (sf::RenderWindow& App, int element, float x_pos, float y_pos);

	private:
	int m_elements;
	int m_diff_resources;
	std::string m_level_folder;
	std::vector<AnimatedSprite> m_layer_elements;
	std::vector<Enemy*> m_layer_enemy1;
	bool isDrawable(AnimatedSprite anim, std::vector<int> drawableArea);

};
