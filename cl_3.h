#ifndef __CL_3__H
#define __CL_3__H

#include "cl_base.h"

class cl_3 : public cl_base {
public:
	cl_3(cl_base* p_head, std::string s_name); //Конструктор класса
	void signal_f(std::string& msg);
	void handler_f(std::string msg);
};

#endif
