#ifndef __CL_5__H
#define __CL_5__H

#include "cl_base.h"

class cl_5 : public cl_base {
public:
	cl_5(cl_base* p_head, std::string s_name); //Конструктор класса
	void signal_f(std::string& msg);
	void handler_f(std::string msg);
};

#endif
