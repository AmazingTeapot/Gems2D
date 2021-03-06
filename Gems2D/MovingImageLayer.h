#pragma once
#include "Layer.h"
#include "Camera.h"
#include "Sprite.h"


/* Class: Moving Image Layer
   Brief: With this kind of layer it is possible to display an image of any size as background. The particularity of this layer is
		  that, if the image is bigger than the screen size, it will move progressively as the level advances, so the image "ends"
		  at the same time than the level.
		  It is possible to superpose two or more of this layers to create a profundity sensation. */

class MovingImageLayer : public Layer {

	public:

	/* CONSTRUCTORS */

	/* Empty constructor. Creates a void Moving Image Layer */
	MovingImageLayer();

	/* Creates a Moving Image Layer and sets it to display the Image i */
	MovingImageLayer(Image* i);


	/* DESTRUCTORS */

	/* Empty destructor */ 
	~MovingImageLayer();


	/* SETTERS */

	/* Sets the layer presets, located on the file defined by path */
	virtual void setLayer (std::string path);


	/* DOMAIN FUNCTIONS */

	/* Updates the position of the background image according to the observer */
	virtual void update (float deltaTime);

	/* Draws the layer on the window. Concretely, draws the subrectangle of the image visible by the player on the window. */
	virtual void draw (sf::RenderWindow& App);
	
	/* This method is used to write only some of the layers. It is used situationally, but I have to polish it. It was useful during
	   the Game&Bud development phase. */
	virtual void superDraw (sf::RenderWindow& App, int element, float x_pos, float y_pos);


	private:
	Sprite m_background;
	int m_image_size_x;
	int m_image_size_y;
	int m_scene_size_x;
	int m_scene_size_y;
	int m_window_size_x;
	int m_window_size_y;

};

