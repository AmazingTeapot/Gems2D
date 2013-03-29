#pragma once
#include <vector>

using namespace std;

class Camera {

	public:

	static Camera* getInstance() {
		static Camera instance;
		return &instance;
	}

	~Camera();

	void setWindowSize(int width, int height);

	void setLevelSize(int width, int height);

	pair<int, int> getWindowSize();

	pair<int, int> getLevelSize();

	pair<int, int> getObsPoint();

	void getDrawableArea(vector<int>& drawable);

	void updateCameraPos (int player_x, int player_y);

	private:
	Camera();
	Camera(Camera* const&);
	void operator=(Camera* const&);
	int m_window_width;
	int m_window_height;
	int m_map_width;
	int m_map_height;
	int m_obs_x;
	int m_obs_y;
};


