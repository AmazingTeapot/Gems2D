#pragma once
#include <vector>

using namespace std;

class Animation {

public:

Animation();

Animation(int sheet);

~Animation();

void addStep(int up, int left, int height, int width);

vector<int> animate();

private:

int m_sheet;
int m_step;
vector<vector <int>> m_steps;

};