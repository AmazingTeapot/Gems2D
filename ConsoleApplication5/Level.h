#pragma once
#include <string>
#include <vector>
#include "Tileset.h"
#include "Camera.h"
#include "StaticGridLayer.h"
#include "MovingImageLayer.h"
#include "StaticElementsLayer.h"
#include "AnimatedElementsLayer.h"

using namespace std;

class Level {

public:

Level();

~Level();

void setLayer1 (string path);

void draw(sf::RenderWindow& App);

void eventHandler (int x);

private:

int m_size_x;
int m_size_y;
vector<Layer*> m_layers;

// The scene center, relative to the map.
float center_x;
float center_y;

/* The player coordinates, relative to the viewport. We can get the map relative player coordinates by doing
   (center_x + obs_x, center_y + obs_y). */

float obs_x;
float obs_y;

};