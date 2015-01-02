#include "menuitem.h"

const set<unsigned char> UQCM_Item::keys_inc = {
	VK_UP,
	VK_RIGHT,
	VK_RETURN,
	VK_SPACE,
	VK_SHIFT,
};

const set<unsigned char> UQCM_Item::keys_dec = {
	VK_DOWN,
	VK_LEFT,
	VK_BACK,
	VK_CONTROL,
	VK_DELETE,
};

void UQCM_Item::input(unsigned char key) {
	switch(m_value.type) {
		case t_integer:
		case t_float: {
						  int multiplier;
						  if(keys_inc.find(key) != keys_inc.end()) {
							  base_step_t::iterator tbsi;
							  if((tbsi = m_value_base_step.find(m_value)) != m_value_base_step.end()) {
								  //if current value is on a base
								  //using step value from current base
								  m_value_curr_step = tbsi->second;
							  }
							  multiplier = +1;
						  } else if(keys_dec.find(key) != keys_dec.end()) {
							  base_step_t::iterator tbsi;
							  if((tbsi = m_value_base_step.find(m_value)) != m_value_base_step.end()) {
								  //if current value is on a base
								  //using step value from previous base
								  m_value_curr_step = (--tbsi)->second;
							  }
							  multiplier = -1;
						  } else {
							  break;
						  }
						  
						  //float 0 == int 0
						  //but checking float as it can contain signed zero
						  if(m_value_curr_step.f != 0.0f) {
							  switch(m_value.type) {
								  case t_integer:
									  m_value.i += m_value_curr_step.i * multiplier;
									  m_callback.f(m_variable, m_value.i);
									  break;
								  case t_float:
									  m_value.f += m_value_curr_step.f * multiplier;
									  m_callback.f(m_variable, m_value.f);
									  break;
							  }
						  }
						  break;
		}
		case t_string:
			if(m_value.str->length() < m_value.str->capacity()) {
				//TODO: check if input key/char is allowed
				*m_value.str += key;
				m_callback.str(m_variable, m_value.str);
			}
			break;

		case t_strlist:
			if(keys_inc.find(key) != keys_inc.end()) {
				m_callback.strlist(m_value.strlist);
			}
			break;
	}
}
