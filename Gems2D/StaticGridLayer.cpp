#include "stdafx.h"
#include "StaticGridLayer.h"
#include <fstream>
#include "ResourceManager.h"

using namespace std;

StaticGridLayer::StaticGridLayer() {
	m_tiles_x = 0;
	m_tiles_y = 0;  
	m_tile_size_x = 0;
	m_tile_size_y = 0;
}

StaticGridLayer::StaticGridLayer(Image* tileset, int tiles_x, int tiles_y) {
	m_tiles_x = tiles_x;
	m_tiles_y = tiles_y;  
	m_tile_size_x = (tileset->getResource().getSize().x)/tiles_x;
	m_tile_size_y = (tileset->getResource().getSize().y)/tiles_y;
	m_tileset.setImage(tileset);
}


StaticGridLayer::~StaticGridLayer() { }


void StaticGridLayer::setTileset(Image* tileset, int tiles_x, int tiles_y) {
	m_tiles_x = tiles_x;
	m_tiles_y = tiles_y;  
	m_tile_size_x = (tileset->getResource().getSize().x)/tiles_x;
	m_tile_size_y = (tileset->getResource().getSize().y)/tiles_y;
	m_tileset.setImage(tileset);
}

void StaticGridLayer::setLayer (string level_map) {
	Tileset background(16, 16, ResourceManager::getInstance()->getImage("level1_tileset"));
	background.scaleTiles(4);
	m_tileset = background;
	ifstream level (LEVEL_PATH + level_map + LEVEL_EXTENSION);
	string map_path;
	if (level.is_open()) {
		if(level.good()) level >> map_path >> m_tiles_x >> m_tiles_y >> m_tile_size_x >> m_tile_size_y;
		vector < vector <int>> aux (m_tiles_x, vector <int> (m_tiles_y));
		m_layer_map = aux;
		for (int i = 0; i < m_tiles_x; ++i) {
			for (int j = 0; j < m_tiles_y; ++j) {
				if(level.good()) level>>m_layer_map[i][j]; 
			}
		}
	}
	level.close();
}

void StaticGridLayer::update(float deltaTime) {
	/* No need of update because we're using the tileset as a set of stamps. */
}

void StaticGridLayer::draw(sf::RenderWindow& App) {
	vector<int> drawableArea;
	Camera::getInstance()->getDrawableArea(drawableArea);
	int tiles_x = Camera::getInstance()->getWindowSize().first/m_tile_size_x;
	int tiles_y = Camera::getInstance()->getWindowSize().second/m_tile_size_y;
	
	int starting_x = m_tiles_x*((float)drawableArea[0]/(float)(m_tiles_x*m_tile_size_x));
	int starting_y = m_tiles_y*((float)drawableArea[1]/(float)(m_tiles_y*m_tile_size_y));
	
	int offset_x = -drawableArea[0]%m_tile_size_x;
	int offset_y = -drawableArea[1]%m_tile_size_y;
	for(int i = 0; i < tiles_y+2; ++i) {
		for (int j = 0; j < tiles_x+2; ++j) {
			if (i+starting_y < m_layer_map.size() && j+starting_x < m_layer_map[0].size() && i+starting_y >= 0 && j+starting_x >= 0) {
				m_tileset.drawTile(m_layer_map[i+starting_y][j+starting_x], (j*m_tile_size_x)+offset_x, (i*m_tile_size_y)+offset_y, App);
			}
		}
	}
}