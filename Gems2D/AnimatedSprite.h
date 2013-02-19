#pragma once

#include <vector>
#include "Sprite.h"
#include "Animation.h"

using namespace std;

class AnimatedSprite {

public:

AnimatedSprite();

AnimatedSprite(int sheets);

~AnimatedSprite();

void loadSheet(int sheetNumber, string sheetName);

void loadAnimations(string file);

void setPosition(int x, int y);

pair<int, int> getPosition();

pair<int, int> getSize();

void setAnimation(int i);

int getAnimation();

void draw(sf::RenderWindow& App);

private:
vector<Animation> m_animations;
vector<Sprite> m_animationSheets;
int m_actualAnimation;
int m_numberOfSheets;
int m_position_x;
int m_position_y;
int m_size_x;
int m_size_y;
};

