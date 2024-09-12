
//----------------------------------------------------------КВ-5--------------------------------------------------------------//

#include "cl_reader.h"
#include <iostream>
cl_reader::cl_reader(cl_base* p_head, std::string s_name) : cl_base(p_head, s_name) { object_class = 1; } //Конструктор класса наследованный от класса cl_base 

void cl_reader::signal_f(std::string& msg) {
	msg += " (class: 2)";
	std::cout << "Signal from " << this->Absolute_Way() << std::endl;

}

void cl_reader::handler_f(std::string msg) {
	std::cout << "Signal to " << this->Absolute_Way() << " Text:  " << msg << std::endl;
}

void cl_reader::handler_reader_from_app(std::string msg) {
	if (msg == "house_size")
		this->emit_signal(SIGNAL_D(cl_reader::signal_from_reader_to_all), msg);
	else if (msg == "cargo")
		this->emit_signal(SIGNAL_D(cl_reader::signal_from_reader_to_all), msg);
	else if (msg == "Turn off the system")
		this->emit_signal(SIGNAL_D(cl_reader::signal_from_reader_to_all), msg);
	else if (msg.substr(0, msg.find(" ", 11)) == "Submit the cargo")
		this->emit_signal(SIGNAL_D(cl_reader::signal_from_reader_to_all), msg);
	else if (msg.substr(0, msg.find(" ", 23)) == "Condition of the cargo area")
		this->emit_signal(SIGNAL_D(cl_reader::signal_from_reader_to_all), msg);
	else if (msg == "SHOWTREE")
		this->emit_signal(SIGNAL_D(cl_reader::signal_from_reader_to_all), msg);
	else if (msg == "Floor condition")
		this->emit_signal(SIGNAL_D(cl_reader::signal_from_reader_to_all), msg);
	else if (msg == "Condition of the tower crane")
		this->emit_signal(SIGNAL_D(cl_reader::signal_from_reader_to_all), msg);
	else if (msg.substr(0, msg.find(" ", 6)) == "Cargo condition")
		this->emit_signal(SIGNAL_D(cl_reader::signal_from_reader_to_all), msg);
}

void cl_reader::signal_from_reader_to_all(std::string& msg) {
	//----Сигнал для класса housearea----//
}