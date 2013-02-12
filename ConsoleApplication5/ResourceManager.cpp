#include "stdafx.h"
#include <string>
#include <iostream>
#include <map>
#include "ResourceManager.h"
#include "Resource.h"
#include "Image.h"

const string IMAGE_PATH = "./Resources/Graphics/";
const string IMAGE_EXTENSION = ".png";

const string MUSIC_PATH = "./Resources/Audio/Music/";
const string MUSIC_EXTENSION = ".ogg";

const string SFX_PATH = "./Resources/Audio/SFX/";
const string SFX_EXTENSION = ".ogg";

const string FONT_PATH = "./Resources/Fonts/";
const string FONT_EXTENSION = ".ttf";

using namespace std;
ResourceManager::ResourceManager () {
	m_resource_quantity = 0;
}

ResourceManager::~ResourceManager() {}

void ResourceManager::loadImage(string name, string source_name) {
	Image* i = new Image(IMAGE_PATH + source_name + IMAGE_EXTENSION);
	if(i->load())
	m_resources[name + IMAGE_EXTENSION] = i;
}

void ResourceManager::loadMusic(string name, string source_name) {
	Image* m = new Image(MUSIC_PATH + source_name + MUSIC_EXTENSION);
	m->load();
	(*m).load();
	m_resources[name + MUSIC_EXTENSION] = m;
}

void ResourceManager::loadSFX(string name, string source_name) {
	Image* s = new Image(SFX_PATH + source_name + SFX_EXTENSION);
	s->load();
	m_resources[name + SFX_EXTENSION] = s;
}

void ResourceManager::loadFont(string name, string source_name) {
	Image* f = new Image(FONT_PATH + source_name + FONT_EXTENSION);
	f->load();
	m_resources[name + FONT_EXTENSION] = f;
}

Image* ResourceManager::getImage(string name) {
	return (Image*)m_resources[name + IMAGE_EXTENSION];
}

Image* ResourceManager::getMusic(string name) {
	return (Image*)m_resources[name + MUSIC_EXTENSION];
}

Image* ResourceManager::getSFX(string name) {
	return (Image*)m_resources[name + SFX_EXTENSION];
}

Image* ResourceManager::getFont(string name) {
	return (Image*)m_resources[name + FONT_EXTENSION];
}

bool ResourceManager::checkImage(string name) {
	map<string, Resource*>::const_iterator it = m_resources.find(name);
	return it!=m_resources.end();
}