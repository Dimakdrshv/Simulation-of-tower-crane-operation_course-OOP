#include "cl_5.h"
#include <iostream>
cl_5::cl_5(cl_base* p_head, std::string s_name) : cl_base(p_head, s_name) { object_class = 5; } // онструктор класса наследованный от класса cl_base 

void cl_5::signal_f(std::string& msg) {
	msg += " (class: 6)";
	std::cout << "Signal from " << this->Absolute_Way() << std::endl;

}

void cl_5::handler_f(std::string msg) {
	std::cout << "Signal to " << this->Absolute_Way() << " Text:  " << msg << std::endl;
}