#include "cl_3.h"
#include <iostream>
cl_3::cl_3(cl_base* p_head, std::string s_name) : cl_base(p_head, s_name) { object_class = 3; } // онструктор класса наследованный от класса cl_base 

void cl_3::signal_f(std::string& msg) {
	msg += " (class: 4)";
	std::cout << "Signal from " << this->Absolute_Way() << std::endl;

}

void cl_3::handler_f(std::string msg) {
	std::cout << "Signal to " << this->Absolute_Way() << " Text:  " << msg << std::endl;
}