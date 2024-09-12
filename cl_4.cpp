#include "cl_4.h"
#include <iostream>
cl_4::cl_4(cl_base* p_head, std::string s_name) : cl_base(p_head, s_name) { object_class = 4; } //����������� ������ ������������� �� ������ cl_base 

void cl_4::signal_f(std::string& msg) {
	msg += " (class: 5)";
	std::cout << "Signal from " << this->Absolute_Way() << std::endl;

}

void cl_4::handler_f(std::string msg) {
	std::cout << "Signal to " << this->Absolute_Way() << " Text:  " << msg << std::endl;
}