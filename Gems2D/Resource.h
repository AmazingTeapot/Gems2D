#pragma once

#include <vector>
using namespace std;

/* Class: Resource
   Brief: This abstract class is used to wrap all the resource types defined on the SFML library. */

class Resource {

	public:

	/* CONSTRUCTORS */

	/* Empty constructor. */
	Resource ();

	/* Constructor with a base path for the resource. */
	Resource (string Path);


	/* DESTRUCTORS */

	/* Empty destructor. */
	~Resource();


	/* GETTERS */

	/* Path getter. It returns the path of the resource. */
	string getPath ();
	

	/* SETTERS */

	/* Path setter. It sets the path of the resource. The path is a string. */
	void setPath (string Path);


	/* DOMAIN FUNCTIONS */

	/* Load function. It loads the resource into the system. This function has to be redefined on the
	   subsequent child classes. The resource is loaded from the path "m_path". If the resource is correctly
	   loaded it returns true. Otherwise it returns false. */
	virtual bool load() = 0;

	protected:
	string m_path;

};