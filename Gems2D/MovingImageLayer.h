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

	/* Creates a void Moving Image Layer */
	MovingImageLayer();

	/* Creates a Moving Image Layer an
	MovingImageLayer(Image* i);

	~MovingImageLayer();

	virtual void setLayer (string path);

	virtual void draw (sf::RenderWindow& App);

private:

Sprite m_background;
int m_image_size_x;
int m_image_size_y;
int m_scene_size_x;
int m_scene_size_y;
int m_window_size_x;
int m_window_size_y;

};

