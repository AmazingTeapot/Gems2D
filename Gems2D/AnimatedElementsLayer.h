#pragma once
#include "stdafx.h"
#include "Layer.h"
#include "Camera.h"
#include "Sprite.h"
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
	virtual void setLayer(string path);


	/* DOMAIN FUNCTIONS */

	/* Draws the layer on the window. Concretely, draws all the elements of the subrectangle of the image visible by the player on the window.
	   It would be good to define an offset range to precharge the elements */
	virtual void draw(sf::RenderWindow& App);

	private:
	int m_elements;
	int m_diff_resources;
	string m_level_folder;
	vector<AnimatedSprite> m_layer_elements;
	bool isDrawable(AnimatedSprite anim, vector<int> drawableArea);

};
