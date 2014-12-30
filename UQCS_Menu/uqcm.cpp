#include "uqcm.h"

UQCM::UQCM() {

}

UQCM::UQCM(string filename) {

}

UQCM::~UQCM() {

}

bool UQCM::input(unsigned char key) {
	return false;
}

const vector<UQCM_Item>& UQCM::getItems() const {
	return m_items;
}
