#ifndef UQCM_ITEM_H
#define UQCM_ITEM_H

#include <Windows.h> //for virtual key codes

#include <string>
#include <vector>
#include <map>
#include <set>
#include <limits>

using namespace std;

class UQCM_Item {
public:
	typedef void(*callback_int)(string variable, int value);
	typedef void(*callback_float)(string variable, float value);
	typedef void(*callback_string)(string variable, string *value);
	typedef void(*callback_strlist)(vector<string> *strlist);
	enum type {
		t_none,
		t_integer,
		t_float,
		t_string,
		t_strlist,
	};
	union value_t {
		type type;
		struct {
			int i;
			float f;
			string *str;
			vector<string> *strlist;
		};

		//required for std::map
		bool operator< (const value_t& rhs) const {
			switch(type) {
				case t_integer: return i < rhs.i;
				case t_float: return f < rhs.f;
				default: return true;
			}
		}
	};
	union callback_t {
		callback_int i;
		callback_float f;
		callback_string str;
		callback_strlist strlist;
	};
	typedef map<value_t, value_t> base_step_t;

	bool m_selected;
	string m_title;
	string m_variable;
	value_t m_value;
	base_step_t m_value_base_step;
	callback_t m_callback;

	UQCM_Item *m_parent;
	vector<UQCM_Item> m_children;

	void input(unsigned char key);

private:
	value_t &m_value_curr_step;

	static const set<unsigned char> keys_inc;
	static const set<unsigned char> keys_dec;
};

#endif //UQCM_ITEM_H
