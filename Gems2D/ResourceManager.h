#pragma once

#include "Image.h"
#include "Constants.h"

/* Class: Resource Manager
   Brief: Singleton class. This class loads and stores all the resources used in the game. It have getters and setters
          for each type of resource. When a resource is stored, an unique name is required to identify it. */

class ResourceManager {
	
	public:

	static ResourceManager* getInstance() {
		static ResourceManager instance;
		return &instance;
	}

	/* DESTRUCTORS*/

	/* Empty destructor */
	~ResourceManager();


	/* LOADERS */

	/* Image loader. It loads image resources. */
	void loadImage(std::string name, std::string source_name);

	/* Music loader. It loads audio resources used as background music. */
	void loadMusic(std::string name, std::string source_name);

	/* Sound Effects loader. It loads audio resources used as sound effects. */
	void loadSFX(std::string name, std::string source_name);

	/* Font loader. It loads font templates */
	void loadFont(std::string name, std::string source_name);


	/* GETTERS */

	/* Image getter. It returns an image stored by the manager and identified by name */
	Image* getImage(std::string name);

	/* Music. It returns a song stored by the manager and identified by name */
	Image* getMusic(std::string name);
	
	/* SFX getter. It returns a sound effect stored by the manager and identified by name */
	Image* getSFX(std::string name);

	/* Font getter. It returns a font stored by the manager and identified by name */
	Image* getFont(std::string name);


	/* CHECKERS */

	/* Image checker. Returns true if the image identified by name is stored on the manager. */
	bool checkImage(std::string name);

	private:
	std::map<std::string, Resource*> m_resources;
	int m_resource_quantity;
	Image m;
	ResourceManager();
	ResourceManager(ResourceManager* const&);
	void operator=(ResourceManager* const&);
};

