#include "stdafx.h"
#include "Animation.h"
#include <iostream>

Animation::Animation () {
	m_step = 0;
	m_sheet = 1;
}

Animation::Animation(int sheet) {
	m_step = 0;
	m_sheet = sheet;
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

vector<int> Animation::animate() {
	vector<int> area(5);
	area[0] = m_sheet;
	area[1] = m_steps[m_step][0];
	area[2] = m_steps[m_step][1];
	area[3] = m_steps[m_step][2];
	area[4] = m_steps[m_step][3];
	m_step += 1;
	m_step = m_step%m_steps.size();
	return area;
}