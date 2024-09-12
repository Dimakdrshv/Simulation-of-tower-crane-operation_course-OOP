
//----------------------------------------------------------КВ-5--------------------------------------------------------------//

#pragma once
#include "cl_base.h"
class cl_housearea : public cl_base {
public:
	cl_housearea(cl_base* p_head, std::string s_name); //Конструктор класса
	void signal_f(std::string& msg);
	void handler_f(std::string msg);
	int floor, length, width;
	void handler_housearea_from_reader(std::string msg);
	void signal_from_house_area(std::string& msg);
};

