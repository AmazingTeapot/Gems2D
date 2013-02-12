#pragma once

#include <vector>
#include "Sprite.h"
#include "Animation.h"

using namespace std;

const int GRAVITY = 9.8;

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

/*Genis*/
void jump ();

void move_left();

void move_right();

void move_duck_left();

void move_duck_right();

//void change_velocitys();

void fins_on_em_puc_moure(int& x_max, int& y_max);

void dona_valor_Ps();

//void change_position();

//bool colision();

//void calcule_next_pos();

//void rearrange_position();

private:
	int force_x;
	int force_y;
	//int velocity_x;
	//int velocity_y;
	int next_position_x;
	int next_position_y;
	int x_colision;
	int y_colision;
	int p1_x;
	int p1_y;
	int p2_x;
	int p2_y;
	int p3_x;
	int p3_y;
	int p4_x;
	int p4_y;
	int p5_x;
	int p5_y;
	int p6_x;
	int p6_y;
	int p7_x;
	int p7_y;
	int p8_x;
	int p8_y;

vector<Animation> m_animations;
vector<Sprite> m_animationSheets;
int m_actualAnimation;
int m_numberOfSheets;
int m_position_x;
int m_position_y;
int m_size_x;
int m_size_y;
};

