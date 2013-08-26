#include "stdafx.h"
#include "MyContactListener.h"
#include "Camera.h"
#include <iostream>
using namespace std;

MyContactListener::MyContactListener(void)
{
}


MyContactListener::~MyContactListener(void)
{
}

 
void MyContactListener::BeginContact(b2Contact* contact) {
          //check if fixture A was the foot sensor
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
		  if ( (int)fixtureUserData == 3 )
              Camera::getInstance()->setSteps(Camera::getInstance()->getSteps() + 1);
          //check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( (int)fixtureUserData == 3 )
              Camera::getInstance()->setSteps(Camera::getInstance()->getSteps() + 1);
}
  
void MyContactListener::EndContact(b2Contact* contact) {
          //check if fixture A was the foot sensor
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( (int)fixtureUserData == 3 )
              Camera::getInstance()->setSteps(Camera::getInstance()->getSteps() - 1);
          //check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( (int)fixtureUserData == 3 )
              Camera::getInstance()->setSteps(Camera::getInstance()->getSteps() - 1);
}