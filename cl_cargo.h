
//----------------------------------------------------------КВ-5--------------------------------------------------------------//

#pragma once
#include "cl_base.h"


class cl_cargo : public cl_base {
	int number_of_area, number_of_square;
	float length, width, height;
public:
	cl_cargo(cl_base* p_head, std::string s_name, int number_of_area = 0, int number_of_square = 0, float length = 0, float width = 0, float height = 0); //Конструктор класса
	void signal_f(std::string& msg);
	void handler_f(std::string msg);
	void handler_cargo_from_reader(std::string msg);
	void signal_from_cargo(std::string& msg);
};

