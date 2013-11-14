#pragma once
#include "animatedsprite.h"

class Enemy : public AnimatedSprite {

public:

	virtual void die() = 0;

};

