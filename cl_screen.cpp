
//----------------------------------------------------------КВ-5--------------------------------------------------------------//

#include "cl_screen.h"
#include <iostream>
cl_screen::cl_screen(cl_base* p_head, std::string s_name) : cl_base(p_head, s_name) { object_class = 7; } //Конструктор класса наследованный от класса cl_base 

void cl_screen::signal_f(std::string& msg) {
	msg += " (class: 6)";
	std::cout << "Signal from " << this->Absolute_Way() << std::endl;

}

void cl_screen::handler_f(std::string msg) {
	std::cout << "Signal to " << this->Absolute_Way() << " Text:  " << msg << std::endl;
}

void cl_screen::handler_screen_from_reader(std::string msg) {
	if (msg != "house_size" && msg != "cargo" && msg.substr(0, msg.find(" ", 11)) != "Submit the cargo"
		&& msg.substr(0, msg.find(" ", 23)) != "Condition of the cargo area" && msg != "SHOWTREE" && msg != "Floor condition" &&
		msg != "Condition of the tower crane" && msg.substr(0, msg.find(" ", 6)) != "Cargo condition" && msg[0] != '|')
		std::cout << msg << std::endl;
	if (msg[msg.size() - 1] == '|') {
		msg.pop_back();
		std::cout << msg << std::endl;
	}
	if (msg[0] == '|') {
		msg.erase(msg.begin());
		std::cout << msg << std::endl;
	}
}