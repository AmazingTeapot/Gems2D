#include "stdafx.h"
#include "Resource.h"

Resource::Resource(void) {
	m_path = "";
}

Resource::Resource(std::string path) {
	m_path = path;
}

Resource::~Resource(void) {}
	
std::string Resource::getPath () {
	return m_path;
}

void Resource::setPath (std::string Path) {
	m_path = Path;
}