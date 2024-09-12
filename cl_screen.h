
//----------------------------------------------------------КВ-5--------------------------------------------------------------//

#pragma once
#include "cl_base.h"
class cl_screen : public cl_base {
public:
	cl_screen(cl_base* p_head, std::string s_name); //Конструктор класса
	void signal_f(std::string& msg);
	void handler_f(std::string msg);
	void handler_screen_from_reader(std::string msg);
};

