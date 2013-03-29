#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Resource.h"

/* Class: Image
   Brief: This class wraps the SFML concept of texture and gives a group of functions for working with them. */

class Image: public Resource {

	public:
	
	/* CONSTRUCTORS */

	/* Empty constructor. */
	Image();

	/* Constructor with a base path for the resource. */
	Image(string path);


	/* DESTRUCTORS */

	/* Empty destructor. */
	~Image();


	/* GETTERS */

	/* Image getter. It returns a reference to the resource. */
	sf::Texture& getResource();
	

	/* SETTERS */

	/* Image setter. It sets the resource to the given image. */
	void setResource (sf::Texture res);


	/* DOMAIN FUNCTIONS */

	/* Load function. It loads the resource into the system. The resource is loaded 
	   from the path "m_path". "m_path" has to point to an image source.  If the resource is correctly
	   loaded it returns true. Otherwise it returns false. */
	virtual bool load();

	private:
	sf::Texture m_image;
	sf::Sprite m_sprite;

};
