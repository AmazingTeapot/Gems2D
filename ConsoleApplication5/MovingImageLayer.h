#pragma once
#include "Layer.h"
#include "Camera.h"
#include "Sprite.h"

class MovingImageLayer : public Layer {

public:

MovingImageLayer();

MovingImageLayer(Image* i);

~MovingImageLayer();

virtual void setLayer (string path);

virtual void draw (sf::RenderWindow& App);

private:

Sprite m_background;
int m_image_size_x;
int m_image_size_y;
int m_scene_size_x;
int m_scene_size_y;
int m_window_size_x;
int m_window_size_y;

};

