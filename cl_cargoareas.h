
//----------------------------------------------------------КВ-5--------------------------------------------------------------//

#pragma once
#include "cl_base.h"
class cl_cargoareas : public cl_base {
	public:
		cl_cargoareas(cl_base* p_head, std::string s_name); //Конструктор класса
		void signal_f(std::string& msg);
		void handler_f(std::string msg);
		void handler_cargoareas_from_reader(std::string msg);
		void signal_from_cargoareas(std::string& msg);
};

