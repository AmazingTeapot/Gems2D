#pragma once
#include "stdafx.h"
#include "Level.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include "Image.h"
#include "Structs.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Constants.h"
#include "MyContactListener.h"
#include "Box2D.h"
#include "SFML\Audio.hpp"
//#include <Windows.h>

/* UTILITIES */

bool isDrawable(std::vector<int> element, std::vector<int> drawableArea) {
	return(element[0]+element[2] > drawableArea[0] && element[1]+element[3] > drawableArea[1] && 
    element[0] < drawableArea[2] && element[1] < drawableArea[3]);
}

Level::Level() : world(b2Vec2(0.0f, 9.5f)) {
	srand ((unsigned int)time(NULL));
	center_x = WINDOW_SIZE_X/2;
	center_y = WINDOW_SIZE_Y/2;
	obs_x = center_x;
	obs_y = center_y;
	events = std::vector<int>(100, 0);
	world.SetContactListener(new MyContactListener());
	Camera::getInstance()->setSteps(1);
	states = std::vector<bool>(9, false);
	states[ON_FLOOR] = true;
	states[RIGHT_INERTIA] = true;
	candle_time = 0;
	iter = 0;
	whip_counter = 0;
	breakable_broken = false;
	got_key = false;
	whipSensorFixtures = std::vector<b2Fixture*>(4);
	fixtured = false;
	whippitywhoop = -1;
	doorOpen = false;
	materials = std::vector<bool>(6, false);
	blueprints = std::vector<bool>(3, false);
	craftMode = false;
	spikedBoots = false;
	jumpingBoots = false;
	shield = false;
	arrowPosition = 0;
	life = 10;
	invulnerability_time = 0;
	drop = std::vector<int>(3, 12);
}

Level::Level(std::string levelName) : world(b2Vec2(0.0f, 9.5f)) {
	m_size_x = 32;
	m_size_y = 33;
	center_x = WINDOW_SIZE_X/2;
	center_y = WINDOW_SIZE_Y/2;
	obs_x = center_x;
	obs_y = center_y;
	events = std::vector<int>(100, 0);
	world.SetContactListener(new MyContactListener());
	Camera::getInstance()->setSteps(1);
	m_levelName = levelName;
	states = std::vector<bool>(9, false);
	candle_time = 0;
	iter = 0;
	whip_counter = 0;
	breakable_broken = false;
	got_key = false;
	whipSensorFixtures = std::vector<b2Fixture*>(4);
	fixtured = false;
	whippitywhoop = -1;
	doorOpen = false;
	craftMode = false;
	spikedBoots = false;
	jumpingBoots = false;
	shield = false;
	arrowPosition = 0;
	life = 10;
	invulnerability_time = 0;
	states[ON_FLOOR] = true;
	states[RIGHT_INERTIA] = true;
	blueprints = std::vector<bool>(3, false);
	materials = std::vector<bool>(6, false);
	drop = std::vector<int>(3, 12);
}

Level::~Level() {
	
}

void Level::setLayers() {
	m_levelName = GameManager::getInstance()->getLevelName();		
	m_size_x = Camera::getInstance()->getLevelSize().first/64;
	m_size_y = Camera::getInstance()->getLevelSize().second/64;	
	std::vector<int> saveData = GameManager::getInstance()->getSave();
	for(int i = 0; i < blueprints.size(); ++i) blueprints[i] = saveData[i];
	for(int i = 0; i < materials.size(); ++i) materials[i] = saveData[i + 3];
	spikedBoots = saveData[9];
	jumpingBoots = saveData[10];
	shield = saveData[11];
	life = saveData[12];

	/* CODE */
	int layer_numb;
	std::ifstream levelconfig(LEVEL_PATH + m_levelName + LEVEL_CONFIGS + LEVEL_EXTENSION);
	if (levelconfig.is_open()) {
		if (levelconfig.good()) levelconfig >> layer_numb;
		m_layers.clear();
		m_layers.reserve(layer_numb);
		for(int i = 0; i < layer_numb; ++i) {
			std::string loadPath, resourceName;
			int layerType, x_size, y_size;
			if (levelconfig.good()) levelconfig >> layerType;
			switch (layerType) {
			case 0:	
				if (levelconfig.good()) levelconfig >> resourceName;
				ResourceManager::getInstance()->loadImage(m_levelName + "_" + resourceName, MOVING_IMAGE_LAYER_PATH + resourceName);
				m_layers.push_back(new MovingImageLayer (ResourceManager::getInstance()->getImage(m_levelName + "_" + resourceName)));
				break;
			case 1:
				if (levelconfig.good()) levelconfig >> resourceName >> x_size >> y_size;
				ResourceManager::getInstance()->loadImage(m_levelName + "_" + resourceName, STATIC_GRID_LAYER_PATH + resourceName);
				m_layers.push_back(new StaticGridLayer (ResourceManager::getInstance()->getImage(m_levelName + "_" + resourceName), x_size, y_size));
				m_layers[i]->setLayer(m_levelName);
				break;
			case 2:
				m_layers.push_back(new StaticElementsLayer());
				m_layers[i]->setLayer(m_levelName);
				break;
			case 3:
				m_layers.push_back(new AnimatedElementsLayer());
				m_layers[i]->setLayer(m_levelName);
				break;
			case 4:
				m_layers.push_back(new HudLayer());
				m_layers[i]->setLayer(m_levelName);
				break;
			default:
				break;
			}
		}
		loadWorld();
	}
}

void Level::loadWorld() {

		/* CREATING THE FLOOR */
		b2BodyDef groundBodyDef;
		b2PolygonShape groundBox;
	
		/* CREATING THE COLLISIONABLE SPACE */

		int collnumb = 0;
		int sensnumb = 0;
		int senscolnumb = 0;
		float x, y = 0;
		float xsize = 0;
		float ysize = 0;
		float xsize2 = 0;
		float ysize2 = 0;
		int number;
		std::ifstream levelcolls(LEVEL_PATH + m_levelName + "/collisions" + LEVEL_EXTENSION);
		if (levelcolls.is_open()) {
			if (levelcolls.good()) levelcolls >> collnumb;
			for(int i = 0; i < collnumb; ++i) {
				levelcolls >> x >> y >> xsize >> ysize;
				groundBodyDef.position.Set(x, y);
				groundBody.push_back(world.CreateBody(&groundBodyDef));
				groundBox.SetAsBox(xsize, ysize);
				groundBody[groundBody.size() - 1]->CreateFixture(&groundBox, 0.0f);
			}
		}
		std::ifstream levelsensors(LEVEL_PATH + m_levelName + "/sensorCollisions" + LEVEL_EXTENSION);
		if (levelsensors.is_open()) {
			if(levelsensors.good()) levelsensors >> senscolnumb >> sensnumb;
				b2FixtureDef fixtureDef;
				fixtureDef.shape = &groundBox;
				fixtureDef.density = 1.0f;
				fixtureDef.friction = 0.0f;
				for(int i = 0; i < senscolnumb; ++i) {
					levelsensors >> x >> y >> xsize >> ysize >> xsize2 >> ysize2 >> number;
					fixtureDef.isSensor = false;
					groundBodyDef.position.Set(x, y);
					groundBody.push_back(world.CreateBody(&groundBodyDef));
					groundBox.SetAsBox(xsize, ysize);
					groundBody[groundBody.size() - 1]->CreateFixture(&groundBox, 0.0f);	
					fixtureDef.isSensor = true;
					groundBox.SetAsBox(xsize2, ysize2);
					b2Fixture* footSensorFixture = groundBody[groundBody.size() - 1]->CreateFixture(&fixtureDef);
					footSensorFixture->SetUserData( (void*)number);
				}
				for(int i = 0; i < sensnumb; ++i) {
					levelsensors >> x >> y >> xsize >> ysize >> number;
					groundBodyDef.position.Set(x, y);
					groundBody.push_back(world.CreateBody(&groundBodyDef));
					groundBox.SetAsBox(xsize, ysize);
					fixtureDef.isSensor = true;
					b2Fixture* footSensorFixture = groundBody[groundBody.size() - 1]->CreateFixture(&fixtureDef);
					footSensorFixture->SetUserData( (void*)number);
				}
		}
					

		/* UNFORTUNATELY, THIS DOES NOT WORK BY NOW :( 
		/* AixÅEÈs un intent d'autogenerar els espais col∑lisionables fent petites static boxes a tots
		aquells tiles on hi ha un element col∑lisionable. El problema Ès que les petites vibracions que
		es generen a la dynamic box del player provoquen que de vegades el personatge es trabi en espais que
		son plans. Un intent per arreclar-ho es el de crear les caixes amb les vores arrodonides (octagons irregulars)
		perÅEaleshores es crea un altre problem amb els punts de contacte y provoca que el personatge faci petits
		salts quan camina.
		TO-DO: Ha d'existir ALGUNA forma de poder autogenerar els espais col∑lisionables sense donar les coordenades a ma,
		potser amb un algoritme de generaciÅEde pol˙Ñons o algun altre cosa.
		Segurament no pugui trobar-ho durant aquest projecte, perÅEho deixo com a reminder per treballar-hi desprÈs.

		for(int i = 0; i < 62*22; ++i) {
			if(((StaticGridLayer*)m_layers[1])->getTile(i) == 0 ||
				((StaticGridLayer*)m_layers[1])->getTile(i) == 1 ||
				((StaticGridLayer*)m_layers[1])->getTile(i) == 2) {
				std::cout << ((StaticGridLayer*)m_layers[1])->getTile(i) << std::endl;
				groundBodyDef.position.Set((i%62)*0.5 + 0.25, (i/62)*0.5 + 0.25);
				groundBody.push_back(world.CreateBody(&groundBodyDef));

				groundBox.SetAsBox(0.25, 0.25);
				groundBody[groundBody.size() - 1]->CreateFixture(&groundBox, 0.0f);		
			}
		}*/

		/* CREATING THE BODY OF THE PLAYER */
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		if(m_levelName == "level1") bodyDef.position.Set(0.5f, 10.5f);
		else bodyDef.position.Set(0.5f, 3.0f);
		bodyDef.fixedRotation = true;

		b2PolygonShape dynamicBox;
		b2Vec2 vertices3[4];
		vertices3[0].Set(0.0f, 0.0f);
		vertices3[1].Set(0.5f, 0.0f);
		vertices3[2].Set(0.5f, 0.8f);
		vertices3[3].Set(0.0f, 0.8f);
		dynamicBox.Set(vertices3, 4);
		b2FixtureDef fDef;
		fDef.shape = &dynamicBox;
		fDef.density = 1.0f;
		fDef.friction = 0.0f;
		body = world.CreateBody(&bodyDef);
		body->CreateFixture(&fDef);
		fDef.isSensor = true;
		b2Fixture* footSensorFixtureplayer = body->CreateFixture(&fDef);
		footSensorFixtureplayer->SetUserData( (void*)0 );


		// Adding foot sensor fixture
		dynamicBox.SetAsBox(0.1, 0.1, b2Vec2(0.25, 1), 0);
		footSensorFixtureplayer = body->CreateFixture(&fDef);
		footSensorFixtureplayer->SetUserData( (void*)5 );

		/* Adding whip sensor fixture
		   Notice we're using different collision identifier for each whip collider.
		   This is because we're only polling the right identifiers when the first frame of one
		   of the whip animations is on. */

		b2FixtureDef enemyFixtureDef;
		b2PolygonShape enemyBox;
		b2Vec2 verticesEnemy[4];
		verticesEnemy[0].Set(0.0f, 0.0f);
		verticesEnemy[1].Set(0.5f, 0.0f);
		verticesEnemy[2].Set(0.5f, 1.0f);
		verticesEnemy[3].Set(0.0f, 1.0f);
		int count = 4;
		enemyBox.Set(verticesEnemy, count);
	
		enemyFixtureDef.shape = &enemyBox;
		enemyFixtureDef.density = 0.0f;
		enemyFixtureDef.friction = 0.0f;
		enemyFixtureDef.isSensor = true;
		b2Fixture* enemySensorFixture;
		std::vector<Enemy*> enemies = ((AnimatedElementsLayer*)m_layers[2])->getAnimatedEnemies();
		dead = std::vector<bool>(enemies.size(), false);
		for(int i = 0; i < enemies.size(); ++i) {
			if(enemies[i]->getSize().second <= 20) {
				verticesEnemy[0].Set(0.0f, 0.5f);
				verticesEnemy[1].Set(0.5f, 0.5f);
			}
			else {
				verticesEnemy[0].Set(0.0f, 0.0f);
				verticesEnemy[1].Set(0.5f, 0.0f);
			}
			enemyBox.Set(verticesEnemy, count);
			groundBodyDef.position.Set(((float)enemies[i]->getPosition().first)/128, ((float)enemies[i]->getPosition().second)/128);
			enemyBody.push_back(world.CreateBody(&groundBodyDef));
			enemySensorFixture = enemyBody[enemyBody.size() - 1]->CreateFixture(&enemyFixtureDef);
			enemySensorFixture->SetUserData((void*)(7+i));		
		}
}

void Level::update(float deltaTime) {
    
	if(life > 0) {
	if(events[ATTACK_2]) {
		craftMode = true;
		arrowPosition = 0;
	}

	if(!craftMode) {
	/* Basically on this function we're reading all the external inputs (stored in our events vector) and
	   processing it. Then we update all the animations and phyisics but this is done on an external module. */
	if(GameManager::getInstance()->getCollision(0)) {
		if(invulnerability_time == 0) {
			invulnerability_time = 1.5;
			if(!shield) life -= 2;
			else life -= 1;
			if(life <= 0) {
				sound.resetBuffer();
				if (!buffer.loadFromFile("./Resources/Music/gameOver.wav")) std::cout << "error";
				sound.setBuffer(buffer);
				sound.play();
			}
		}
	}
	if(invulnerability_time > 0) {
		invulnerability_time -= deltaTime;
		if(invulnerability_time < 0) invulnerability_time = 0;
	}

	b2Vec2 vel = body->GetLinearVelocity();
    float forcex = 0;
    float forcey = 0;

	/* PROCESSING EVENTS HERE */

	if(!states[LEFT_STAIRS] && !states[RIGHT_STAIRS]) {
		if(events[RIGHT] && !states[CROUCHING] && !states[ATTACKING]) {
			if (((AnimatedElementsLayer*)m_layers[2])->getActualAnimation(0) != WALKING_RIGHT)
				((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, WALKING_RIGHT);
			int mult = 3;
			if(events[ACTION_RUN]) mult = 4; 
			if(!spikedBoots)/* Changing velocity directly */ vel.x = b2Min(vel.x + 6.0f*deltaTime, +2.0f );
			else vel.x = b2Min(vel.x + 6.0f*deltaTime, +3.0f);
			/* Using Forces */ //if ( vel.x < 1.4 ) forcex = 10000*mult*deltaTime;
			states[LEFT_INERTIA] = false;
			states[RIGHT_INERTIA] = true;
		}

		else if(events[LEFT] && !states[CROUCHING] && !states[ATTACKING]) {
			if (((AnimatedElementsLayer*)m_layers[2])->getActualAnimation(0) != WALKING_LEFT)
				((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, WALKING_LEFT);
			int mult = 3;
			if(events[ACTION_RUN]) mult = 3; 
			if(!spikedBoots) /* Changing velocity directly */ vel.x = b2Max(vel.x - 6.0f*deltaTime, -2.0f );
			else  vel.x = b2Max(vel.x - 6.0f*deltaTime, -3.0f);
			/* Using Forces */// 	if ( vel.x > -1.4 ) forcex = -10*mult;
			states[LEFT_INERTIA] = true;
			states[RIGHT_INERTIA] = false;
 		}
		else if (!states[ATTACKING]) {

			if(states[LEFT_INERTIA])((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, STANDBY_LEFT);
			else ((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, STANDBY_RIGHT);
		}


		if(events[DOWN] && !states[ATTACKING]) { //obs_y += 150*deltaTime;
			if(states[LEFT_INERTIA] && !states[ATTACKING])((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, CROUCH_LEFT);
			else ((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, CROUCH_RIGHT);

			states[CROUCHING] = true;
		}
		else if(!states[ATTACKING]) states[CROUCHING] = false;

		//Camera::getInstance()->updateCameraPos((int)obs_x, (int)obs_y);
		//for(int i = 0; i < m_layers.size(); ++i) m_layers[i]->update(deltaTime);

		if(events[ACTION_JUMP] && states[ON_FLOOR] && body->GetLinearVelocity().y <= 0 && !states[ATTACKING]) {
		//	body->ApplyLinearImpulse(b2Vec2(0.0f,-3000.0f*deltaTime), body->GetWorldCenter());
	 		/*if(body->GetLinearVelocity().y <= -40) */
			if(!jumpingBoots) body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -4.8));
			else body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -6.5));
			states[ON_FLOOR] = false;
			states[JUMPING] = true;
		}

		if((!events[LEFT] && !events[RIGHT]) || events[DOWN]) {
			/* Changing velocity directly */// vel.x *= (1-deltaTime);
			/* Using Forces */  
			if(body->GetLinearVelocity().y == 0) {

			/* THIS IS PROVOKING VIBRATIONS. IT SHOULDN'T, so we're pausing it for now and
			   simplifying all the inertia (/.__.)/ But inertia is cool, i'd like to fix it \(o__o)z */

			/*	float decrease = (deltaTime);
				if (vel.x > 0) {
					if(decrease > vel.x) vel.x = 0;
					else vel.x -= decrease;
				}
				else if (vel.x < 0) {
					if(decrease < vel.x) vel.x = 0;
					else vel.x += decrease;
				}
			}*/
		
				// THIS IS, BY THE WAY, A VERY BAD PATCH. AUTOREMINDER: CHANGE THIS PLS, THIS SUCKS
				vel.x = vel.x*(1-(10.0*deltaTime));
			}
			else vel.x = vel.x*(1.0-deltaTime);	
		}
		/* We process the states, controlling the animations: This way the character always looks at the right side,
		   and the jumping/falling/whipping animations are correctly displayed too. */
		if (body->GetLinearVelocity().y > 0.1) {
			states[FALLING] = true;
			states[JUMPING] = false;
		}
		if (body->GetLinearVelocity().y < 0.1 && states[FALLING] && !states[ATTACKING]) {
			states[ON_FLOOR] = true;
			states[FALLING] = false;
		}

		if ((events[DOWN] || states[JUMPING] || states[FALLING]) && !states[ATTACKING]) {
			if(states[LEFT_INERTIA])((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, CROUCH_LEFT);
			else ((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, CROUCH_RIGHT);
		}

		if (events[ATTACK_1] && !states[ATTACKING]) {
			states[ATTACKING] = true;
			if(states[LEFT_INERTIA] && (!states[CROUCHING] && !states[JUMPING] && !states[FALLING])) ((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, WHIP_LEFT);
			else if(states[RIGHT_INERTIA] && (!states[CROUCHING] && !states[JUMPING] && !states[FALLING])) ((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, WHIP_RIGHT);
			else if(states[LEFT_INERTIA]) ((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, WHIP_CROUCHING_LEFT);
			else if(states[RIGHT_INERTIA]) ((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, WHIP_CROUCHING_RIGHT);

			sound.resetBuffer();
			if (!buffer.loadFromFile("./Resources/Music/whip.wav")) std::cout << "error";
			sound.setBuffer(buffer);
			sound.play();
		}
		

		/*	For now we're not aplying forces because this messes up with all the delta time features, and the program
		gets a bit crazy. We need to find a way to apply forces scaled to deltaTime */
		//body->ApplyForce( b2Vec2(forcex,forcey), body->GetWorldCenter() );
		if(!states[ATTACKING] && states[ON_FLOOR]) {
			if(events[UP]) {
				if((((StaticGridLayer*)m_layers[0])->getTile(obs_x*2 + 1 + ((int)((obs_y+0.8)*2)*m_size_x)) == 38 ||
					((StaticGridLayer*)m_layers[0])->getTile(obs_x*2 + 1 + ((int)((obs_y+0.8)*2)*m_size_x)) == 65)
					&& (int)(obs_x*128)%64 >= 40 && (int)(obs_x*128)%64 <= 50) {
	 				states[RIGHT_STAIRS] = true;
					((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, STAIRS_RIGHT_UP);
					world.SetGravity(b2Vec2(0.0f, 0.0f));
					body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
					body->SetActive(false);
				}
				else if ((((StaticGridLayer*)m_layers[0])->getTile(obs_x*2 - 1 + ((int)((obs_y+0.8)*2)*m_size_x)) == 4 ||
					((StaticGridLayer*)m_layers[0])->getTile(obs_x*2 + ((int)((obs_y+0.8)*2)*m_size_x)) == 64) &&
					(int)(obs_x*128)%64 >= 16 && (int)(obs_x*128)%64 <= 24) {
	 				states[LEFT_STAIRS] = true;
					((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, STAIRS_LEFT_UP);
					world.SetGravity(b2Vec2(0.0f, 0.0f));
					body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
					body->SetActive(false);
				}
			}
			else if(events[DOWN]) {

				if ((((StaticGridLayer*)m_layers[0])->getTile(obs_x*2 + 61 + ((int)((obs_y+1.3)*2)*m_size_x)) == 38 ||
					((StaticGridLayer*)m_layers[0])->getTile(obs_x*2 + 61 + ((int)((obs_y+1.3)*2)*m_size_x)) == 65)
					&&	(int)(obs_x*128)%64 >= 16 && (int)(obs_x*128)%64 <= 24) {
	 				states[RIGHT_STAIRS] = true;
					((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, STAIRS_LEFT_DOWN);
					world.SetGravity(b2Vec2(0.0f, 0.0f));
					body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
					body->SetActive(false);
				}
				else if ((((StaticGridLayer*)m_layers[0])->getTile(obs_x*2 + 63 + ((int)((obs_y+1.3)*2)*m_size_x)) == 4 ||
					((StaticGridLayer*)m_layers[0])->getTile(obs_x*2 + 66 + ((int)((obs_y+0.8)*2)*m_size_x)) == 64)
					&& (int)(obs_x*128)%64 >= 16 && (int)(obs_x*128)%64 <= 24) {
	 				states[LEFT_STAIRS] = true;
					((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, STAIRS_RIGHT_DOWN);
					world.SetGravity(b2Vec2(0.0f, 0.0f));
					body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
					body->SetActive(false);
				}
			}
		}

		if((states[ON_FLOOR] || body->GetLinearVelocity().y < 0.1 && states[FALLING]) && states[ATTACKING]) vel.x = 0;
		/*if (body->GetLinearVelocity().x > 0.5) */body->SetLinearVelocity(b2Vec2(vel.x, body->GetLinearVelocity().y));
	}

	else if (states[RIGHT_STAIRS]) {
		if(events[RIGHT] || events[UP]) {
		body->SetTransform(b2Vec2(body->GetPosition().x + deltaTime, body->GetPosition().y - deltaTime), 0);
			if(states[LEFT_INERTIA]) {
				states[LEFT_INERTIA] = false;
				states[RIGHT_INERTIA] = true;
				((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, STAIRS_RIGHT_UP);
			}
			int tile = ((StaticGridLayer*)m_layers[0])->getTile(obs_x*2 + 1 + ((int)((obs_y+1.500)*2)*m_size_x));
			if(tile == 2) {
				states[RIGHT_STAIRS] = false;
				world.SetGravity(b2Vec2(0.0f, 9.5f));
				body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));			
				body->SetActive(true);
			}
		}
		else if(events[LEFT] || events[DOWN]) {
		body->SetTransform(b2Vec2(body->GetPosition().x - deltaTime, body->GetPosition().y + deltaTime), 0);
			if(states[RIGHT_INERTIA]) {
				states[RIGHT_INERTIA] = false;
				states[LEFT_INERTIA] = true;
				((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, STAIRS_LEFT_DOWN);
			}
			int tile = ((StaticGridLayer*)m_layers[0])->getTile(obs_x*2 + 0.25 + ((int)((obs_y+1.00)*2)*m_size_x));
			if(tile == 0 || tile == 1) {
				states[RIGHT_STAIRS] = false;
				world.SetGravity(b2Vec2(0.0f, 9.5f));
				body->SetActive(true);
				body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));			
			}
		}
		else body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));	
	}
	else {
		if(events[LEFT] || events[UP]) {
		body->SetTransform(b2Vec2(body->GetPosition().x - deltaTime, body->GetPosition().y - deltaTime), 0);
			if(states[RIGHT_INERTIA]) {
				states[RIGHT_INERTIA] = false;
				states[LEFT_INERTIA] = true;
				((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, STAIRS_LEFT_UP);
			}
			int tile = ((StaticGridLayer*)m_layers[0])->getTile(obs_x*2 + ((int)((obs_y+1.500)*2)*m_size_x));
			if(tile == 2) {
				states[LEFT_STAIRS] = false;
				world.SetGravity(b2Vec2(0.0f, 9.5f));
				body->SetActive(true);
				body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));			
			}
		}
		else if(events[RIGHT] || events[DOWN]) {
		body->SetTransform(b2Vec2(body->GetPosition().x + deltaTime, body->GetPosition().y + deltaTime), 0);
			if(states[LEFT_INERTIA]) {
				states[LEFT_INERTIA] = false;
				states[RIGHT_INERTIA] = true;
				((AnimatedElementsLayer*)m_layers[2])->changeAnimation(0, STAIRS_RIGHT_DOWN);
			}
			int tile = ((StaticGridLayer*)m_layers[0])->getTile(obs_x*2 + 0.25 + ((int)((obs_y+1.00)*2)*m_size_x));
			if(tile == 0 || tile == 1) {
				states[LEFT_STAIRS] = false;
				world.SetGravity(b2Vec2(0.0f, 9.5f));
				body->SetActive(true);
				body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));			
			}
		}
		else body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));	
	}
	/* Animating the candles hardcoded */
	candle_time += deltaTime;
	if(candle_time > 0.6) {
		for(int i = 0; i < m_size_x*m_size_y; ++i) {
			if(((StaticGridLayer*)m_layers[0])->getTile(i) == 6)
				((StaticGridLayer*)m_layers[0])->setTile(i, 21);
			else if(((StaticGridLayer*)m_layers[0])->getTile(i) == 21)
				((StaticGridLayer*)m_layers[0])->setTile(i, 6);
		}
	}
	while(candle_time > 0.6) candle_time -= 0.6;
	

	obs_x = body->GetPosition().x;
	obs_y = body->GetPosition().y - 0.2;
	Camera::getInstance()->updateCameraPos(obs_x*128, obs_y*128);
	if(obs_y * 128 > Camera::getInstance()->getLevelSize().second) life = 0;
 	m_layers[0]->update(deltaTime);
	m_layers[1]->update(deltaTime);
	m_layers[2]->update(deltaTime);

	((AnimatedElementsLayer*)m_layers[2])->changePosition(0, obs_x*128, obs_y*128 + 2);
	
	
	if(states[ATTACKING]) {
		whip_counter += deltaTime;
		/* HERE WE HANDLE THE COLLISIONS AND THE WHIP THINGS */
		if(whip_counter >= (3/DEFAULT_ANIM_SPEED)) {
			whip_counter = 0;
			states[ATTACKING] = false;
		}
		//	whip_sprites
	}

	/* HERE WE HANDLE THE COLLISIONS WITH THE WHIP */

	std::vector<Enemy*> enemies = ((AnimatedElementsLayer*)m_layers[2])->getAnimatedEnemies();

	// BREAKING (bad) THE WALL
	if(states[ATTACKING] && whip_counter >= (2/DEFAULT_ANIM_SPEED)) {
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.0f;
		fixtureDef.isSensor = true;
		if(!fixtured) {	
			if(states[LEFT_INERTIA] && !states[CROUCHING]) { 
				dynamicBox.SetAsBox(0.375, 0.125, b2Vec2(-0.375, 0.375), 0);
				whipSensorFixtures[0] = body->CreateFixture(&fixtureDef);
				whipSensorFixtures[0]->SetUserData( (void*)1 );
				whippitywhoop = 0;
			}	
	
			else if(states[LEFT_INERTIA] && states[CROUCHING]) {
				dynamicBox.SetAsBox(0.375, 0.125, b2Vec2(-0.375, 0.625), 0);
				whipSensorFixtures[1] = body->CreateFixture(&fixtureDef);
				whipSensorFixtures[1]->SetUserData( (void*)1 );
				whippitywhoop = 1;
			}
		
			else if(states[RIGHT_INERTIA] && !states[CROUCHING]) {
				dynamicBox.SetAsBox(0.375, 0.125, b2Vec2(0.625, 0.375), 0);
				whipSensorFixtures[2] = body->CreateFixture(&fixtureDef);
				whipSensorFixtures[2]->SetUserData( (void*)1 );
				whippitywhoop = 2;
			}
		
			else if(states[RIGHT_INERTIA] && states[CROUCHING]) {
				dynamicBox.SetAsBox(0.375, 0.125, b2Vec2(0.625, 0.625), 0);
				whipSensorFixtures[3] = body->CreateFixture(&fixtureDef);
				whipSensorFixtures[3]->SetUserData( (void*)1 );			
				whippitywhoop = 3;
			}

			fixtured = true;
		}
		if(GameManager::getInstance()->getCollision(7) &&!breakable_broken) {
				if(m_levelName == "level1") groundBody[22]->SetActive(false);
				else groundBody[29]->SetActive(false);
				breakable_broken = true;
		}
		for(int i = 0; i < enemies.size(); ++i) {
		   if(GameManager::getInstance()->getCollision(i+8) && !dead[i]) {
				if(drop[0] >= 6) {
					drop[0] = rand()%6;
					drop[1] = ((AnimatedElementsLayer*)m_layers[2])->getAnimatedEnemies()[i]->getPosition().first;
					drop[2] = ((AnimatedElementsLayer*)m_layers[2])->getAnimatedEnemies()[i]->getPosition().second;
					b2BodyDef groundBodyDef;
					b2FixtureDef fixtureDef;
					fixtureDef.shape = &groundBox;
					fixtureDef.isSensor = true;
					groundBodyDef.position.Set(((float)drop[1])/128 + 0.25f, ((float)drop[2]/128 + 0.25f));
					groundBody.push_back(world.CreateBody(&groundBodyDef));
					groundBox.SetAsBox(0.25f, 0.25f);
					b2Fixture* itemFixture = groundBody[groundBody.size() - 1]->CreateFixture(&fixtureDef);
					itemFixture->SetUserData( (void*)(99 + drop[0]) );
				}
				((AnimatedElementsLayer*)m_layers[2])->kill(i);
				enemyBody[i]->SetActive(false);
				sound.resetBuffer();
				if (!buffer.loadFromFile("./Resources/Music/enemy.wav")) std::cout << "error";
				sound.setBuffer(buffer);
				sound.play();
				dead[i] = true;
			 }
		}
	}
	else if(fixtured) {
		fixtured = false;
		body->DestroyFixture(whipSensorFixtures[whippitywhoop]);
		GameManager::getInstance()->activeWhip(0);
		whippitywhoop = -1;
	}	
	
	for(int i = 0; i < enemies.size(); ++i) {
		enemyBody[i]->SetTransform(b2Vec2(((float)enemies[i]->getPosition().first)/(float)128, 
			((float)enemies[i]->getPosition().second)/(float)128), 0.0f);
	}

	if(GameManager::getInstance()->getCollision(3) && !got_key) {
		got_key = true;
		sound.resetBuffer();
		if (!buffer.loadFromFile("./Resources/Music/pickup.wav")) std::cout << "error";
		sound.setBuffer(buffer);
		sound.play();
	}

	for(int i = 0; i < 6; ++i) {
		if(GameManager::getInstance()->getCollision(40 + i)) {
			materials[i] = true;
			GameManager::getInstance()->deleteCollision(40 + i);
			drop[0] = 10;
			groundBody[groundBody.size()-1]->SetActive(false);			
			sound.resetBuffer();
			if (!buffer.loadFromFile("./Resources/Music/pickup.wav")) std::cout << "error";
			sound.setBuffer(buffer);
			sound.play();
		}
	}

	for(int i = 0; i < 3; ++i) {
		if(GameManager::getInstance()->getCollision(50 + i) && !blueprints[i]) {
			blueprints[i] = true;
			GameManager::getInstance()->deleteCollision(50 + i);
			sound.resetBuffer();
			if (!buffer.loadFromFile("./Resources/Music/pickup.wav")) std::cout << "error";
			sound.setBuffer(buffer);
			sound.play();
		}
	}

	// We add a step on the physics world
	events = std::vector<int>(100, 0);
	world.Step(deltaTime, 8, 3);
	}

	else {
		if(events[SELECT]) {
			switch(arrowPosition) {
			case 0:
				if(materials[1] && materials[3] && materials[4] && !spikedBoots && blueprints[0]) {
					materials[1] = false;
					materials[3] = false;
					materials[4] = false;
					spikedBoots = true;
					sound.resetBuffer();
					if (!buffer.loadFromFile("./Resources/Music/select.wav")) std::cout << "error";
					sound.setBuffer(buffer);
					sound.play();
				}
				else {
					sound.resetBuffer();
					if (!buffer.loadFromFile("./Resources/Music/error.wav")) std::cout << "error";
					sound.setBuffer(buffer);
					sound.play();
				}
				break;
			case 1:
				if(materials[0] && materials[3] && materials[4] && !jumpingBoots && blueprints[1]) {
					materials[0] = false;
					materials[3] = false;
					materials[4] = false;
					jumpingBoots = true;
					sound.resetBuffer();
					if (!buffer.loadFromFile("./Resources/Music/select.wav")) std::cout << "error";
					sound.setBuffer(buffer);
					sound.play();
				}
				else {
					sound.resetBuffer();
					if (!buffer.loadFromFile("./Resources/Music/error.wav")) std::cout << "error";
					sound.setBuffer(buffer);
					sound.play();
				}
				break;
			case 2:
				if(materials[2] && materials[3] && materials[4] && materials[5] && !shield && blueprints[2]) {
					materials[2] = false;
					materials[3] = false;
					materials[4] = false;
					materials[5] = false;
					shield = true;
					sound.resetBuffer();			
					if (!buffer.loadFromFile("./Resources/Music/select.wav")) std::cout << "error";
					sound.setBuffer(buffer);
					sound.play();
				}
				else {
					sound.resetBuffer();
					if (!buffer.loadFromFile("./Resources/Music/error.wav")) std::cout << "error";
					sound.setBuffer(buffer);
					sound.play();
				}
				break;
			case 3:
				craftMode = false;
				break;
			}
		}
		else if (events[ROTATE_LEFT]) arrowPosition = (arrowPosition-1)%4;
		else if (events[ROTATE_RIGHT]) arrowPosition = (arrowPosition+1)%4;
		if(arrowPosition < 0) arrowPosition += 4;
		events = std::vector<int>(100, 0);
	}
	}
	else if (events[SELECT]) GameManager::getInstance()->defeat();
	else if (events[QUIT]) GameManager::getInstance()->exit();
}

void Level::gameOver() {
	m_size_x = 32;
	m_size_y = 33;
	center_x = WINDOW_SIZE_X/2;
	center_y = WINDOW_SIZE_Y/2;
	obs_x = center_x;
	obs_y = center_y;
	events = std::vector<int>(100, 0);
	world.SetContactListener(new MyContactListener());
	Camera::getInstance()->setSteps(1);
	m_levelName = "";
	states = std::vector<bool>(9, false);
	candle_time = 0;
	iter = 0;
	whip_counter = 0;
	breakable_broken = false;
	got_key = false;
	whipSensorFixtures = std::vector<b2Fixture*>(4);
	fixtured = false;
	whippitywhoop = -1;
	doorOpen = false;
	craftMode = false;
	spikedBoots = false;
	jumpingBoots = false;
	shield = false;
	arrowPosition = 0;
	life = 10;
	invulnerability_time = 0;
	states[ON_FLOOR] = true;
	states[RIGHT_INERTIA] = true;
	blueprints = std::vector<bool>(3, false);
	materials = std::vector<bool>(6, false);
	drop = std::vector<int>(3, 12);
	for(int i = 0; i < 60; ++i) GameManager::getInstance()->deleteCollision(i);
	setLayers();
}

void Level::draw(sf::RenderWindow& App) {
	m_layers[0]->draw(App);
	if(!got_key) m_layers[1]->superDraw(App, 13, -1, -1);
	if(!doorOpen) {
		m_layers[1]->superDraw(App, 14, -1, -1); 
		if(GameManager::getInstance()->getCollision(4) && got_key) {
			doorOpen = true;
			if(m_levelName == "level1") groundBody[23]->SetActive(false);
			else groundBody[30]->SetActive(false);
		}
	}
	else if(GameManager::getInstance()->getCollision(5)) {
		std::vector<int> saveData(13, 0);
		for(int i = 0; i < blueprints.size(); ++i) saveData[i] = blueprints[i];
		for(int i = 0; i < materials.size(); ++i) saveData[i+3] = materials[i];
		if(spikedBoots) saveData[9] = true;
		if(jumpingBoots) saveData[10] = true;
		if(shield) saveData[11] = true;
		saveData[12] = life;
		GameManager::getInstance()->victory(saveData);
	//	world.~b2World();
	}
	if(!breakable_broken) m_layers[1]->superDraw(App, 12, -1, -1);
	
	if(states[ATTACKING]) {
		if(whip_counter*DEFAULT_ANIM_SPEED < 2) {
			if(states[LEFT_INERTIA]) {
				if(states[CROUCHING] || states[JUMPING] || states[FALLING]) m_layers[1]->superDraw(App, 9 + whip_counter*DEFAULT_ANIM_SPEED, obs_x*128 + 63, obs_y*128 + 2);
				else m_layers[1]->superDraw(App, 3 + whip_counter*DEFAULT_ANIM_SPEED, obs_x*128 + 63, obs_y*128 + 2);
			}
			else {
				if(states[CROUCHING] || states[JUMPING] || states[FALLING]) m_layers[1]->superDraw(App, 6 + whip_counter*DEFAULT_ANIM_SPEED, obs_x*128 - 64, obs_y*128 + 2);
				else m_layers[1]->superDraw(App, whip_counter*DEFAULT_ANIM_SPEED, obs_x*128 - 64, obs_y*128 + 2);
			}
		}
		else {
			if(states[LEFT_INERTIA]) {
				if (states[CROUCHING] || states[JUMPING] || states[FALLING]) m_layers[1]->superDraw(App, 9 + whip_counter*DEFAULT_ANIM_SPEED, obs_x*128 - 100, obs_y*128 + 2); 
				else m_layers[1]->superDraw(App, 3 + whip_counter*DEFAULT_ANIM_SPEED, obs_x*128 - 100, obs_y*128 + 2);
			}	
			else {
				if (states[CROUCHING] || states[JUMPING] || states[FALLING]) m_layers[1]->superDraw(App, 6 + whip_counter*DEFAULT_ANIM_SPEED, obs_x*128 + 63, obs_y*128 + 2);
				else m_layers[1]->superDraw(App, whip_counter*DEFAULT_ANIM_SPEED, obs_x*128 + 63, obs_y*128 + 2);
			}
		}
	}

	if(invulnerability_time != 0) {
		if(((int)(invulnerability_time*6)/2)%2 == 0) {
			((AnimatedElementsLayer*)m_layers[2])->changePosition(0, 9999, 9999);
		}
	}
	
	if(drop[0] < 6) {
		m_layers[1]->superDraw(App, 26 + drop[0], drop[1], drop[2]);	
	}
	
	m_layers[2]->draw(App);

	if(!blueprints[0]) m_layers[1]->superDraw(App, 32, -1, -1);
	if(!blueprints[1]) m_layers[1]->superDraw(App, 33, -1, -1);
	if(!blueprints[2]) m_layers[1]->superDraw(App, 34, -1, -1);

	/* DRAWING THE HUD */
	m_layers[3]->superDraw(App, 0, 0, 0);
	if(got_key) m_layers[3]->superDraw(App, 1, 0, 0);
	if(spikedBoots) m_layers[3]->superDraw(App, 2, 0, 0);
	if(jumpingBoots) m_layers[3]->superDraw(App, 3, 0, 0);
	if(shield) m_layers[3]->superDraw(App, 4, 0, 0);
	for(int i = 0; i < 6; ++i) if(materials[i]) 
		m_layers[3]->superDraw(App, 5 + i, 0, 0);
	for(int i = life; i > 0; --i) m_layers[3]->superDraw(App, 10 + i, 0, 0);		

	if(craftMode) {
		((StaticElementsLayer*)m_layers[1])->drawOnScreen(App, 15);
		if(blueprints[0]) ((StaticElementsLayer*)m_layers[1])->drawOnScreen(App, 19);
		else ((StaticElementsLayer*)m_layers[1])->drawOnScreen(App, 16);
		if(blueprints[1]) ((StaticElementsLayer*)m_layers[1])->drawOnScreen(App, 20);
		else ((StaticElementsLayer*)m_layers[1])->drawOnScreen(App, 17);
		if(blueprints[2]) ((StaticElementsLayer*)m_layers[1])->drawOnScreen(App, 21);
		else ((StaticElementsLayer*)m_layers[1])->drawOnScreen(App, 18);
		((StaticElementsLayer*)m_layers[1])->drawOnScreen(App, 22 + arrowPosition);
	}
	if(life <= 0) ((StaticElementsLayer*)m_layers[1])->drawOnScreen(App, 35);
}

void Level::eventHandler(int x) {
	events[x] = 1;
}
