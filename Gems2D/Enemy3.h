#pragma once
#include "AnimatedSprite.h"
#include "ResourceManager.h"
#include "Animation.h"
#include "Enemy.h"

class Enemy3 : public Enemy {

public:

	Enemy3();

	~Enemy3();

	Enemy3(int sheetNumber);

	Enemy3(int sheetNumber, int pos_x, int pos_y, int max_left, int max_right);

	void Enemy3::setBorders(int x, int y);

	std::pair<int, int> Enemy3::getBorders();

	void update(float deltaTime);

	virtual void die();

private:
	int m_border_left;
	int m_border_right;
	int m_direction;
	bool alive;
	bool stopped;
	float cont;
};

