#pragma once
#include <vector>

using namespace std;

/* Class: Animation
   Brief: This class provides the data needed to animate an action of an "Animated Sprite". It just stores
		  the coordinates of the sub-rectangles related to each step of the animation. It also stores the current
		  step of the animation so it can return at each iteration the current coordinates.
		  Each animation is applied to a group of animation sheets. When an Animated Sprite generates animations, it will
		  apply the Animation data to its animation sheets. Each animation will have an identifier that indicates which animation
		  sheet is it using. */

class Animation {

	public:

	/* CONSTRUCTORS */

	/* Empty constructor. It sets the animation at the first animation sheet. */
	Animation();

	/* This constructor allows you to set in which animation sheet is the animation placed */
	Animation(int sheet);


	/* DESTRUCTORS */

	/* Empty destructor */
	~Animation();


	/* DOMAIN FUNCTIONS */

	/* It adds a new step on the animation. Each step consist in a point mapped on the animation sheet 
	   and the size of the sub-rectangle */
	void addStep(int up, int left, int height, int width);

	/* It iterates trough the animation sequence and returns the coordinates of the actual animation step */
	vector<int> animate();

	private:

	int m_sheet;
	int m_step;
	vector<vector <int>> m_steps;

};