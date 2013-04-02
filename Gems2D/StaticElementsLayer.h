#pragma once
#include "Layer.h"
#include "Camera.h"
#include "Sprite.h"

/* Class: Static Elements Layer
   Brief: With this kind of layer it is possible to display image resources of any size to any point on the screen.
          All this objects, per se, will have no colliders, so the player will be able to trespass them.
		  If you draw this layer after the player layer is drawn, the objects will cover the player. */

class StaticElementsLayer : public Layer {

	public:
	
	/* CONSTRUCTORS */

	/* Empty constructor. */
	StaticElementsLayer();


	/* DESTRUCTORS */

	/* Empty destructor. */
	~StaticElementsLayer();

	
	/* SETTERS */

	/* Sets the layer presets, located on the file defined by path */
	virtual void setLayer (string path);


	/* DOMAIN FUNCTIONS */

	/* Updates the position of the static images according to the observer */
	virtual void update ();

	/* Draws the layer on the window. Concretely, draws all the elements of the subrectangle of the image visible by the player on the window.
	   It would be good to define an offset range to precharge the elements */
	virtual void draw (sf::RenderWindow& App);
	
	private:
	vector<Sprite> m_drawables;
	int m_elements;
	int m_diff_resources;
	string m_level_folder;
	vector<vector <int>> m_layer_elements;
	bool isDrawable(vector<int> element, vector<int> drawableArea);

};