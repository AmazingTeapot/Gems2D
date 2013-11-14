#include "stdafx.h"
#include "MyContactListener.h"
#include "Camera.h"
#include "GameManager.h"
#include "Box2D.h"
#include "Box2D\Dynamics\b2WorldCallbacks.h"
#include "Box2D\Dynamics\Contacts\b2Contact.h"
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
    void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
    void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();
	
	if ( (int)fixtureUserDataA == 5 || (int)fixtureUserDataB == 5 ) {
		Camera::getInstance()->setSteps(1);
	}


	if((int)fixtureUserDataA == 6 && (int)fixtureUserDataB == 1) {
		GameManager::getInstance()->addCollision(1+(int)fixtureUserDataA);
	}
	else if((int)fixtureUserDataA == 1 && (int)fixtureUserDataB == 6) {
		GameManager::getInstance()->addCollision(1+(int)fixtureUserDataB);
	}
	else if((int)fixtureUserDataA >= 7 && (int)fixtureUserDataA < 40  && (int) fixtureUserDataB == 1) {
		GameManager::getInstance()->addCollision(1+(int)fixtureUserDataA);
	}
 	else if((int) fixtureUserDataA == 1 && (int)fixtureUserDataB >= 7 && (int)fixtureUserDataB < 40) {
		GameManager::getInstance()->addCollision(1+(int)fixtureUserDataB);
	}
	else if((int)fixtureUserDataA == 0 && ((int)fixtureUserDataB >= 2  && (int)fixtureUserDataB <= 4)) {
		GameManager::getInstance()->addCollision(1+(int)fixtureUserDataB);
	}
 	else if(((int)fixtureUserDataA >= 2 && (int)fixtureUserDataA <= 4) && (int)fixtureUserDataB == 0) {
 		GameManager::getInstance()->addCollision(1+(int)fixtureUserDataA);
	}
	else if((int)fixtureUserDataA == 0 &&  (int)fixtureUserDataB < 40 && (int)fixtureUserDataB >= 7) {
		GameManager::getInstance()->addCollision(0);
	}
	else if((int)fixtureUserDataA == 0 &&  (int)fixtureUserDataB >= 99 ) {
		GameManager::getInstance()->addCollision(40 + (int)fixtureUserDataB - 99);
	}
	else if((int)fixtureUserDataB == 0 &&  (int)fixtureUserDataA >= 99 ) {
		GameManager::getInstance()->addCollision(40 + (int)fixtureUserDataA - 99);
	}
 	else if((int)fixtureUserDataA >= 7 && (int)fixtureUserDataA < 40 && (int)fixtureUserDataB == 0) {
		GameManager::getInstance()->addCollision(0);
	}
	else if((int)fixtureUserDataA == 0 && ((int)fixtureUserDataB >= 50  && (int)fixtureUserDataB <= 52)) {
		GameManager::getInstance()->addCollision((int)fixtureUserDataB);
	}
 	else if(((int)fixtureUserDataA >= 50 && (int)fixtureUserDataA <= 52) && (int)fixtureUserDataB == 0) {
 		GameManager::getInstance()->addCollision((int)fixtureUserDataA);
	}
}
  
void MyContactListener::EndContact(b2Contact* contact) {
          //check if fixture A was the foot sensor
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( (int)fixtureUserData == 5 )
              Camera::getInstance()->setSteps(Camera::getInstance()->getSteps() - 1);
          if ( (int)fixtureUserData >= 7 && (int)fixtureUserData < 99) {
			  GameManager::getInstance()->deleteCollision((int)fixtureUserData + 1);
			  GameManager::getInstance()->deleteCollision(0);
		  }
		  if ( (int)fixtureUserData == 4) {
			  GameManager::getInstance()->deleteCollision(5);
		  }
			//check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( (int)fixtureUserData == 5 )
              Camera::getInstance()->setSteps(0);
          if ( (int)fixtureUserData >= 7 && (int)fixtureUserData < 99) {
			  GameManager::getInstance()->deleteCollision((int)fixtureUserData + 1);
  			  GameManager::getInstance()->deleteCollision(0);
		  }        
		  if ( (int)fixtureUserData == 4) {
			  GameManager::getInstance()->deleteCollision(5);
		  }


}