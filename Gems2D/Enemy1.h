#pragma once
#include "AnimatedSprite.h"
#include "ResourceManager.h"
#include "Animation.h"
#include "Enemy.h"

class Enemy1 : public Enemy {

public:

	Enemy1();
	
	~Enemy1();
	
	Enemy1(int sheetNumber);
	
	Enemy1(int sheetNumber, float pos_x, float pos_y, int max_left, int max_right);
	
	void setBorders(int x, int y);
	
	std::pair<int, int> getBorders();

	virtual void update(float deltaTime);

	virtual void die();

private:
	int m_border_left;
	int m_border_right;
	int m_direction;
	bool alive;
	float cont;
};

