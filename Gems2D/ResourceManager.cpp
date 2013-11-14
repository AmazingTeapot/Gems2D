#include "stdafx.h"
#include <string>
#include <iostream>
#include <map>
#include "ResourceManager.h"
#include "Resource.h"
#include "Image.h"

ResourceManager::ResourceManager () {
	m_resource_quantity = 0;
}

ResourceManager::~ResourceManager() {}

void ResourceManager::loadImage(std::string name, std::string source_name) {
	Image* i = new Image(IMAGE_PATH + source_name + IMAGE_EXTENSION);
	if(i->load())
	m_resources[name + IMAGE_EXTENSION] = i;
}

void ResourceManager::loadMusic(std::string name, std::string source_name) {
	Image* m = new Image(MUSIC_PATH + source_name + MUSIC_EXTENSION);
	m->load();
	(*m).load();
	m_resources[name + MUSIC_EXTENSION] = m;
}

void ResourceManager::loadSFX(std::string name, std::string source_name) {
	Image* s = new Image(SFX_PATH + source_name + SFX_EXTENSION);
	s->load();
	m_resources[name + SFX_EXTENSION] = s;
}

void ResourceManager::loadFont(std::string name, std::string source_name) {
	Image* f = new Image(FONT_PATH + source_name + FONT_EXTENSION);
	f->load();
	m_resources[name + FONT_EXTENSION] = f;
}

Image* ResourceManager::getImage(std::string name) {
	return (Image*)m_resources[name + IMAGE_EXTENSION];
}

Image* ResourceManager::getMusic(std::string name) {
	return (Image*)m_resources[name + MUSIC_EXTENSION];
}

Image* ResourceManager::getSFX(std::string name) {
	return (Image*)m_resources[name + SFX_EXTENSION];
}

Image* ResourceManager::getFont(std::string name) {
	return (Image*)m_resources[name + FONT_EXTENSION];
}

bool ResourceManager::checkImage(std::string name) {
	std::map<std::string, Resource*>::const_iterator it = m_resources.find(name);
	return it!=m_resources.end();
}