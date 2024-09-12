
//----------------------------------------------------------КВ-5--------------------------------------------------------------//

#pragma once
#include "cl_base.h"

class cl_reader : public cl_base {
	public:
		cl_reader(cl_base* p_head, std::string s_name); //Конструктор класса
		void signal_f(std::string& msg);
		void handler_f(std::string msg);
		void handler_reader_from_app(std::string msg);
		void signal_from_reader_to_all(std::string& msg);
};


