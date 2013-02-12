#pragma once

#include "Image.h"

using namespace std;

class ResourceManager {
	
private:

map<string, Resource*> m_resources;
int m_resource_quantity;
Image m;
ResourceManager();
ResourceManager(ResourceManager* const&);
void operator=(ResourceManager* const&);

public:

static ResourceManager* getInstance() {
	static ResourceManager instance;
	return &instance;
}

~ResourceManager();

void loadImage(string name, string source_name);

void loadMusic(string name, string source_name);

void loadSFX(string name, string source_name);

void loadFont(string name, string source_name);

Image* getImage(string name);

Image* getMusic(string name);

Image* getSFX(string name);

Image* getFont(string name);

bool checkImage(string name);

};