#ifndef UQCM_H
#define UQCM_H

#include <vector>

#include "menuitem.h"

using namespace std;

class UQCM {
public:
	UQCM();
	UQCM(string filename);
	~UQCM();

	bool input(unsigned char key);

	const vector<UQCM_Item>& getItems() const;

private:
	vector<UQCM_Item> m_items;
	vector<UQCM_Item>::iterator m_selected_item;
};

#endif //UQCM_H
