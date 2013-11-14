#include "stdafx.h"
#include "Tile.h"

Tile::Tile() {
	m_orientation = 0;
}

Tile::Tile(int i) {

}

Tile::~Tile() { }

std::vector<Abbey> Tile::getAbbeys() {
	return m_abbeys;
}

std::vector<Road> Tile::getRoads() {
	return m_roads;
}

std::vector<City> Tile::getCities() {
	return m_cities;
}

std::vector<Farm> Tile::getFarms() {
	return m_farms;
}

int Tile::getSide(int i) {
	return m_sides[(i + m_orientation)%4];
}

int Tile::getOrientation() {
	return m_orientation;
}

Sprite Tile::getSprite() {
	return m_sprite;
}

void Tile::setAbbeys(std::vector<Abbey> abbeys) {
	m_abbeys = abbeys;
}

void Tile::setRoads(std::vector<Road> roads) {
	m_roads = roads;
}

void Tile::setCities(std::vector<City> cities) {
	m_cities = cities;
}

void Tile::setFarms(std::vector<Farm> farms) {
	m_farms = farms;
}

void Tile::setSides(std::vector<int> sides) {
	m_sides = sides;
}

void Tile::setOrientation(int orientation) {
	m_orientation = orientation;
}

void Tile::setSprite(Sprite sprite) {
	m_sprite = sprite;
}

