#ifndef __CL_4__H
#define __CL_4__H

#include "cl_base.h"

class cl_4 : public cl_base {
public:
	cl_4(cl_base* p_head, std::string s_name); //Конструктор класса
	void signal_f(std::string& msg);
	void handler_f(std::string msg);
};

#endif
