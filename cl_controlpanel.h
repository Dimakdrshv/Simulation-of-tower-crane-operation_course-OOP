
//----------------------------------------------------------КВ-5--------------------------------------------------------------//

#pragma once
#include "cl_base.h"

class cl_controlpanel : public cl_base {
	int crane_boom_corner;
	int cart_way;
	std::string hook;
	public:
		cl_controlpanel(cl_base* p_head, std::string s_name, int crane_boom_corner = 0, int cart_way = 1, std::string hook = ""); //Конструктор класса
		void signal_f(std::string& msg);
		void handler_f(std::string msg);
		void handler_controlpanel_from_reader(std::string msg);
		void singnal_controlpanel(std::string& msg);
		void func(int number_square_house, std::string name);
		void distribution_for_first_area(int number_of_square, int number_square_house, std::string name, int i);
		void distribution_for_second_area(int number_of_square, int number_square_house, std::string name, int i);
		void distribution_for_thrid_area(int number_of_square, int number_square_house, std::string name, int i);
		void call_helper_handlers();
};

