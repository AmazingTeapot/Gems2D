#pragma once
#include "AnimatedSprite.h"
#include "ResourceManager.h"
#include "Animation.h"
#include "Enemy.h"

class Enemy2 :	public Enemy {

public:
	
	Enemy2();
	
	~Enemy2();
	
	Enemy2(int sheetNumber);
	
	Enemy2(int sheetNumber, int pos_x, int max_height);
	
	void Enemy2::setMaxHeight(int h);
	
	int Enemy2::getMaxHeight();
	
	virtual void update(float deltaTime);
	
	virtual void die();

private:
	int max_height;
	float cont;
	bool alive;
	bool up;
};

