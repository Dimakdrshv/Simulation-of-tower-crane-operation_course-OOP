#ifndef __CL_1__H
#define __CL_1__H
#include "cl_base.h"

class cl_1 : public cl_base {
public:
	cl_1(cl_base* p_head, std::string s_name); //Конструктор класса
	void signal_f(std::string& msg);
	void handler_f(std::string msg);
};

#endif
