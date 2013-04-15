#include "stdafx.h"
#include "Animation.h"
#include "Constants.h"
#include <iostream>

Animation::Animation () {
	m_step = 0;
	m_sheet = 1;
	m_animationSpeed = DEFAULT_ANIM_SPEED;
}

Animation::Animation(int sheet, float animSpeed) {
	m_step = 0;
	m_sheet = sheet;
	m_animationSpeed = animSpeed;
}

Animation::~Animation() { }

void Animation::addStep(int up, int left, int height, int width) {
	vector<int> step(4);
	step[0] = up;
	step[1] = left;
	step[2] = height;
	step[3] = width;
	m_steps.push_back(step);
}

void Animation::animate(float deltaTime) {
	m_step += deltaTime * m_animationSpeed;
	while (m_step >= m_steps.size()) m_step -= m_steps.size();
}

vector<int> Animation::getStep() {
	vector<int> area(5);
	area[0] = m_sheet;
	area[1] = m_steps[m_step][0];
	area[2] = m_steps[m_step][1];
	area[3] = m_steps[m_step][2];
	area[4] = m_steps[m_step][3];
	return area;
}