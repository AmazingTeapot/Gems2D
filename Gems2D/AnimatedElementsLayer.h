#pragma once
#include "stdafx.h"
#include "Layer.h"
#include "Camera.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "AnimatedSprite.h"		
#include <fstream>
#include <iostream>

class AnimatedElementsLayer : public Layer {

public:

AnimatedElementsLayer();

~AnimatedElementsLayer();

virtual void setLayer(string path);

virtual void draw(sf::RenderWindow& App);

private:

int m_elements;
int m_diff_resources;
string m_level_folder;
vector<AnimatedSprite> m_layer_elements;
bool isDrawable(AnimatedSprite anim, vector<int> drawableArea);

};
