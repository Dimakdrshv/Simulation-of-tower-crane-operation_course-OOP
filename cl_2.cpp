#include "cl_2.h"
#include <iostream>
cl_2::cl_2(cl_base* p_head, std::string s_name) : cl_base(p_head, s_name) { object_class = 2; } // онструктор класса наследованный от класса cl_base 

void cl_2::signal_f(std::string& msg) {
	msg += " (class: 3)";
	std::cout << "Signal from " << this->Absolute_Way() << std::endl;

}

void cl_2::handler_f(std::string msg) {
	std::cout << "Signal to " << this->Absolute_Way() << " Text:  " << msg << std::endl;
}