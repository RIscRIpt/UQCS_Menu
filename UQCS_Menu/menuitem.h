#ifndef UQCM_ITEM_H
#define UQCM_ITEM_H

#include <string>
#include <vector>
#include <map>
#include <limits>

using namespace std;

class UQCM_Item {
public:
	enum type {
		t_string,
		t_boolean,
		t_integer,
		t_float,
	};
	union value_t {
		int i;
		float f;
	};

	const string& getTitle() const;
	inline bool isSelected() { return m_selected; }

private:
	bool m_selected;

	string m_title;

	vector<string> m_strlist;

	value_t m_value;
	vector<map<map<value_t, value_t>, value_t>> m_limsteps;
};

#endif //UQCM_ITEM_H
