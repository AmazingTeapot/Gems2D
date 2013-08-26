#include "stdafx.h"
#include "Level.h"
#include <fstream>
#include <iostream>
#include "Image.h"
#include "ResourceManager.h"
#include "MyContactListener.h"

using namespace std;

Level::Level() : world(b2Vec2(0.0f, 95.0f)) {
	m_size_x = 0;
	m_size_y = 0;
	center_x = WINDOW_SIZE_X/2;
	center_y = WINDOW_SIZE_Y/2;
	obs_x = center_x;
	obs_y = center_y;
	events = *new vector<int>(100, 0);
	world.SetContactListener(new MyContactListener());
	Camera::getInstance()->setSteps(0);
}

Level::~Level() {

}

void Level::setLayers (string levelName) {
	
	/* CODE */
	int layer_numb;
	ifstream levelconfig(LEVEL_PATH + levelName + LEVEL_CONFIGS + LEVEL_EXTENSION);
	if (levelconfig.is_open()) {
		if (levelconfig.good()) levelconfig >> layer_numb;
		m_layers.clear();
		m_layers.reserve(layer_numb);
		for(int i = 0; i < layer_numb; ++i) {
			string loadPath, resourceName;
			int layerType, x_size, y_size;
			if (levelconfig.good()) levelconfig >> layerType;
			switch (layerType) {
			case 0:	
				if (levelconfig.good()) levelconfig >> resourceName;
				ResourceManager::getInstance()->loadImage(levelName + "_" + resourceName, MOVING_IMAGE_LAYER_PATH + resourceName);
				m_layers.push_back(new MovingImageLayer (ResourceManager::getInstance()->getImage(levelName + "_" + resourceName)));
				break;
			case 1:
				if (levelconfig.good()) levelconfig >> resourceName >> x_size >> y_size;
				ResourceManager::getInstance()->loadImage(levelName + "_" + resourceName, STATIC_GRID_LAYER_PATH + resourceName);
				m_layers.push_back(new StaticGridLayer (ResourceManager::getInstance()->getImage(levelName + "_" + resourceName), x_size, y_size));
				m_layers[i]->setLayer(levelName);
				break;
			case 2:
				m_layers.push_back(new StaticElementsLayer());
				m_layers[i]->setLayer(levelName);
				break;
			case 3:
				m_layers.push_back(new AnimatedElementsLayer());
				m_layers[i]->setLayer(levelName);
				break;
			default:
				break;
			}
		}
		m_player = AnimatedSprite(1);
		m_player.loadSheet(1, "mario_sheet_1");
		m_player.loadAnimations("mario");
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, 50.0f);
		groundBody = world.CreateBody(&groundBodyDef);
		b2PolygonShape groundBox;
		groundBox.SetAsBox(50.0f, 10.0f);
		groundBody->CreateFixture(&groundBox, 0.0f);
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(0.0f, 4.0f);
		body = world.CreateBody(&bodyDef);
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(1.0f, 1.0f);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.2f;
		body->CreateFixture(&fixtureDef);
		 //add foot sensor fixture
		dynamicBox.SetAsBox(0.3, 0.3, b2Vec2(0,2), 0);
		fixtureDef.isSensor = true;
		b2Fixture* footSensorFixture = body->CreateFixture(&fixtureDef);
		footSensorFixture->SetUserData( (void*)3 );
	}
}

void Level::update(float deltaTime) {
    b2Vec2 vel = body->GetLinearVelocity();
    float forcex = 0;
    float forcey = 0;
	if(events[UP]) {
	//	if (obs_y - movement <= 0) obs_y = 0;
	//	else obs_y -= movement;
	}

	if(events[DOWN]) {
	//	if (obs_y + movement >= Camera::getInstance()->getLevelSize().second) obs_y = Camera::getInstance()->getLevelSize().second;
//		else obs_y += movement;
	}

	if(events[LEFT]) {
	//	if (obs_x - movement <= 0) obs_x = 0;
	//	else obs_x -= movement;
		m_player.setAnimation(0);
	int mult = 2;
	if(events[ACTION_RUN]) mult = 3; 
		/* Changing velocity directly */// vel.x = b2Max(vel.x - 20.0f*deltaTime, -20.0f );
		/* Using Forces */ if ( vel.x > -10*mult ) forcex = -100*mult;
	}
	
	if(events[RIGHT]) {
	//	if (obs_x + movement >= Camera::getInstance()->getLevelSize().second) obs_x = Camera::getInstance()->getLevelSize().second;
	//	else obs_x += movement;

	m_player.setAnimation(1);
	int mult = 2;
	if(events[ACTION_RUN]) mult = 4; 
	/* Changing velocity directly */ //vel.x = b2Min(vel.x + 20.0f*deltaTime, +20.0f );
	/* Using Forces */ if ( vel.x < 10*mult ) forcex = 100*mult;
	}

	if(events[ACTION_JUMP] && Camera::getInstance()->getSteps() != 0) {
	//	body->ApplyLinearImpulse(b2Vec2(0.0f,-3000.0f*deltaTime), body->GetWorldCenter());
		/*if(body->GetLinearVelocity().y <= -40) */body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -40));
		cout << body->GetLinearVelocity().y << endl;
	}

	else if (Camera::getInstance()->getSteps() == 0) {
		if(!events[ACTION_JUMP]) forcey = 200;
		else forcey = 0;
	}
	if(!events[LEFT] && !events[RIGHT]) {
		/* Changing velocity directly */// vel.x *= (1-deltaTime);
		/* Using Forces */ forcex = vel.x*-10;
	}
	//body->SetLinearVelocity( vel );	
	body->ApplyForce( b2Vec2(forcex,forcey), body->GetWorldCenter() );
	events = vector<int>(100, 0);
	obs_x = body->GetPosition().x*9.1;
	obs_y = body->GetPosition().y*9.1;
	Camera::getInstance()->updateCameraPos(obs_x, obs_y);
	for(int i = 0; i < m_layers.size(); ++i) m_layers[i]->update(deltaTime);
	m_player.setPosition(obs_x, obs_y);
	m_player.update(deltaTime);
	world.Step(deltaTime, 8, 3);

}

void Level::draw(sf::RenderWindow& App) {
	for(int i = 0; i < m_layers.size(); ++i) m_layers[i]->draw(App);
	m_player.draw(App);
}


void Level::eventHandler(int x) {
	events[x] = 1;
}

