#include "cl_1.h"
#include <iostream>
cl_1::cl_1(cl_base* p_head, std::string s_name) : cl_base(p_head, s_name) { object_class = 1; } // онструктор класса наследованный от класса cl_base 

void cl_1::signal_f(std::string& msg) {
	msg += " (class: 2)";
	std::cout << "Signal from " << this->Absolute_Way() << std::endl;

}

void cl_1::handler_f(std::string msg) {
	std::cout << "Signal to " << this->Absolute_Way() << " Text:  " << msg << std::endl;
}