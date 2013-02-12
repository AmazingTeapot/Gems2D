#include "stdafx.h"
#include "Resource.h"


Resource::Resource(void) {
	m_path = "";
}

Resource::Resource(string path) {
	m_path = path;
}

Resource::~Resource(void) {}
	
string Resource::getPath () {
	return m_path;
}

void Resource::setPath (string Path) {
	m_path = Path;
}

bool Resource::load() {
	return false;
}