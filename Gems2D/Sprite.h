#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>
#include <vector>
#include "Image.h"

using namespace std;

/* Class: Sprite
   Brief: This class treat an Image resource, providing a large amount of tools designed to wrap all
		  the SFML Texture operations. We can also set anchor points to the Image, cut them into sub-rectangles,
		  etc... */

class Sprite {

public:

	/* CONSTRUCTORS*/

    /* Creates a void sprite */
    Sprite();

    /* Creates a sprite with an associated image */
    Sprite(Image* image);

    /* Creates a new sprite with the (x,y) pos defined by xpos and ypos and an associated Image. 
	   The size of the sprite is defined by the original size of the image. */
    Sprite(float xpos, float ypos, Image* image);

    /* Creates a new sprite with the (x,y) pos defined by xpos and ypos, and the size defined by
       xsize and ysize. The image used in the sprite is defined by the string path */
    Sprite(float xpos, float ypos, int xsize, int ysize, Image* imagen);


	/* DESTRUCTORS */

	/* Empty destructor */
	~Sprite();

    
	/* SETTERS */

	/* Sets the position of the sprite (and the anchor point offset applied to the sprite) */
	void setPos(float xpos, float ypos);

    /* Sets the size of the sprite */
	void setSize(int xsize, int ysize);

    /* Sets the subrectangle in the sprite that is going to be showed */
    void setSubRect(int left, int up, int right, int down);

    /* Sets the sprite source image */
    void setImage(Image* imagen);

    /* Sets the number of elements of the tileset and the position of the focus */
    void setTileset(int xelem, int yelem, int pos);

	/* Changes the sprite source to "sprite" */
	void setSprite(sf::Sprite sprite);

	/* Changes the focus position of the tileset onto "pos" */
	void setFocus(int pos);
	 
	/* Changes the anchor point of the tileset onto (x, y), where x and y are coordinates relatives to the sprite */
	void setAnchorPoint(float x, float y);
	

	/* GETTERS */

    /* Returns the position of the sprite plus the offset of the anchor point */
    pair<float, float> getPos();

    /* Returns the size of the sprite */
    pair<int, int> getSize();

    /* Returns the anchor point of the sprite */
    pair<float, float> getAnchorPoint();


	/* DOMAIN FUNCTIONS */

    /* Moves the sprite position "i" pixels on the x axis and "j" pixels on the y axis */
    void move(float i, float j);

    /* Draws the sprite */
    void draw(sf::RenderWindow& App);

    /* Tells if the sprite has been clicked */
    bool isPressed(float x, float y);


protected:

    float m_xpos;
    float m_ypos;
    int m_xsize;
    int m_ysize;
    int m_xelements;
    int m_yelements;
    int m_position;
	int m_imageSize_x;
	int m_imageSize_y;
	int m_anchor_x;
	int m_anchor_y;
    sf::Sprite m_Sprite;
    Image* m_Image;
};


