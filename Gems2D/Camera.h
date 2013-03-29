#pragma once
#include <vector>
using namespace std;

/* Class: Camera
   Brief: Singleton class. It controls all the camera settings: The size of the window, level, etc. It can communicate with the game
          to tell what is the drawable area, it handles the updates...
		  It also manages the observer position. */

class Camera {

	public:

	static Camera* getInstance() {
		static Camera instance;
		return &instance;
	}

	/* DESTRUCTOR */

	/* Empty destructor */
	~Camera();


	/* SETTERS */

	/* It sets the size of the window in pixels */
	void setWindowSize(int width, int height);

	/* It sets the total size of the level in pixels */
	void setLevelSize(int width, int height);


	/* GETTERS */

	/* It gets the size of the window. */
	pair<int, int> getWindowSize();

	/* It gets the total size of the level. */
	pair<int, int> getLevelSize();

	/* It gets the coordinates of the observer. */
	pair<int, int> getObsPoint();

	
	/* DOMAIN FUNCTIONS */

	/* It returns the two points that limitates the drawable subrectangle of the level. */
	void getDrawableArea(vector<int>& drawable);

	/* It moves the observer position according to the following: If the coordinate provided exceeds the boundaries given
	   (25% of the screen, in future updates this value will be able to change) the observer moves on. */
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


