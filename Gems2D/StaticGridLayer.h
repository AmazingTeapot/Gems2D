#pragma once
#include "Layer.h"
#include "Camera.h"
#include "Tileset.h"

class StaticGridLayer : public Layer {

public:

StaticGridLayer();

StaticGridLayer(Image* tileset, int tiles_x, int tiles_y);

~StaticGridLayer();

void setTileset (Image* tileset);

virtual void setLayer (string level_map);

virtual void draw (sf::RenderWindow& App);

private:

Tileset m_tileset;
int m_tiles_x;
int m_tiles_y;     
int m_tile_size_x;
int m_tile_size_y;
vector<vector <int>> m_layer_map;

};
