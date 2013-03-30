#include "stdafx.h"
#include "Level.h"
#include <fstream>
#include <iostream>
#include "Image.h"
#include "ResourceManager.h"

using namespace std;

Level::Level() {
	m_size_x = 0;
	m_size_y = 0;
	center_x = WINDOW_SIZE_X/2;
	center_y = WINDOW_SIZE_Y/2;
	obs_x = center_x;
	obs_y = center_y;
}

Level::~Level() {

}

void Level::setLayer1 (string levelName) {
	
	/* CODE */
	int layer_numb;
	ifstream levelconfig(LEVEL_CONFIGS + levelName + "_config" + LEVEL_EXTENSION);
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
				ResourceManager::getInstance()->loadImage(levelName + "_" + resourceName, levelName + "/" + resourceName);
				m_layers.push_back(new MovingImageLayer (ResourceManager::getInstance()->getImage(levelName + "_" + resourceName)));
				break;
			case 1:
				if (levelconfig.good()) levelconfig >> resourceName >> x_size >> y_size;
				ResourceManager::getInstance()->loadImage(levelName + "_" + resourceName, levelName + "/" + resourceName);
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
	}
}

void Level::draw(sf::RenderWindow& App, float deltaTime) {
	for(int i = 0; i < m_layers.size(); ++i) {
		if(i != 3) m_layers[i]->draw(App);
		else {
			AnimatedElementsLayer* aux = (AnimatedElementsLayer*)m_layers[i];
	//		aux->draw_pj(App, deltaTime, obs_x, obs_y);
		}
	}
}


void Level::eventHandler(int x) {
	AnimatedElementsLayer* a = (AnimatedElementsLayer*)m_layers[3];
	switch (x) {
	case UP:
		//cridem la funcio que fa que el pj es mogui cap a la dreta
		//void right();
	//	m_status = "running";
	//	a->getPlayer()->setAnimation(3);
		if (obs_y - 2 <= 0) obs_y = 0;
		else obs_y -= 2;
		break;
	case DOWN:
		//cridem la funcio que fa que el pj es mogui cap a l'esquerra
//		void left (int pos_x, int pos_y);
	//	m_status = "running";
		if (obs_y + 2 >= Camera::getInstance()->getLevelSize().second) obs_y = Camera::getInstance()->getLevelSize().second;
		else obs_y += 2;
		break;
	case LEFT:
		//cridem a la funcio que fa que el personatge s'ajupi
//		void duck (int pos_x, int pos_y);
//		m_status = "crouch";
//		a->getPlayer()->setAnimation(1);
		if (obs_x - 2 <= 0) obs_x = 0;
		else obs_x -= 2;
		break;
	case RIGHT:
		//cridem a la funcio que fa que el personatge salti
		//void jump (int force_x, int force_y, vector<int> matrix_collision);
	//	a->getPlayer()->setAnimation(2);
		obs_x += (deltaTime/(1/60))*0.1;
		break;
	case ACTION_JUMP:
		//es van recorrent totes les trampes que hi ha al mapa 
		//(++trap_id)%total_traps;
		break;
	case ACTION_RUN:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 13:
	//	if(start_up == false//estem assignant les trampes(l'enemic està escollint les trampes)) {
			//cridem a la funcio que posa la trampa X al numero 1
	//		void assign_trap(int x-5, int trap_id);
	//	else {
			//cridem la funcio que dispara la trampa x 
	//		void shoot_trap(int x-5);
	//	}
		break;
	case 14:		
	//	void final_selection();//cridem a la funcio que fa la selecció final de les trampes escollides
	//	a->getPlayer()->setAnimation(4);
		break;
	case 15:
		//cridem a la funcio que fa la pausa
	//	void pause();
//		a->getPlayer()->setAnimation(0);
		break;	
	case 555:
		cout << "estas pulsando la A";
		break;
	case 556:
		cout << "estas pulsando la B";
		break;
	case 557:
		cout << "estas pulsando la Y";
		break;
	case 558:
		cout << "estas pulsando la X";
		break;
	case 559:
		cout << "estas pulsando la tecla LB";
		break;
	case 560:
		cout << "estas pulsando la flecha pa arriba";
		break;
	case 561:
		cout << "estas pulsando la flecha pa abajo";
		break;
	case 562:
		cout << "estas pulsando la flecha pa la derecha";
		break;
	case 563:
		cout << "estas pulsando la flecha pa la izquierda";
		break;
	case 564:
		cout << "estas pulsando el LT(tab)";
		break;
	default:
		break;
	}
	Camera::getInstance()->updateCameraPos(obs_x, obs_y);
}

