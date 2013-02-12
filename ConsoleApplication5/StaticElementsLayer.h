#pragma once
#include "Layer.h"
#include "Camera.h"
#include "Sprite.h"

class StaticElementsLayer : public Layer {

public:

StaticElementsLayer();

~StaticElementsLayer();

virtual void setLayer (string path);

virtual void draw (sf::RenderWindow& App);
		
private:

Sprite m_drawable;
int m_elements;
int m_diff_resources;
string m_level_folder;
vector<vector <int>> m_layer_elements;
bool isDrawable(vector<int> element, vector<int> drawableArea);

};