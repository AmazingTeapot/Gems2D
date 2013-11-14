#pragma once
#include "Box2D.h"
#include "Box2D\Dynamics\b2WorldCallbacks.h"
#include "Box2D\Dynamics\Contacts\b2Contact.h"

/* Class: MyContactListener
   Brief: A class to detect collisions with the physics. By now we're not using this. */

class MyContactListener : public b2ContactListener {
	
public:
	MyContactListener(void);
	~MyContactListener(void);

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
  
};