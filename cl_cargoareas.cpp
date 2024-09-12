
//----------------------------------------------------------КВ-5--------------------------------------------------------------//

#include "cl_cargoareas.h"
#include <iostream>
cl_cargoareas::cl_cargoareas(cl_base* p_head, std::string s_name) : cl_base(p_head, s_name) { object_class = 4; } //Конструктор класса наследованный от класса cl_base 

void cl_cargoareas::signal_f(std::string& msg) {
	msg += " (class: 5)";
	std::cout << "Signal from " << this->Absolute_Way() << std::endl;

}

void cl_cargoareas::handler_f(std::string msg) {
	std::cout << "Signal to " << this->Absolute_Way() << " Text:  " << msg << std::endl;
}

void cl_cargoareas::handler_cargoareas_from_reader(std::string msg) {
	if (msg.substr(0, msg.find(" ", 23)) == "Condition of the cargo area") {
		int area_number = std::stoi(msg.substr(28));
		msg += " ";
		std::string save_msg = msg;
		std::map<int, std::string> helper;
		switch (area_number) {
			case 1: {
				for (int i = 1; i <= this->get_head()->get_sub_object("P1_Cargo_Area")->cargoes.size(); i++) {
					if (!this->get_head()->get_sub_object("P1_Cargo_Area")->cargoes[i].empty() && helper[i].empty()) {
						msg += "-- s " + std::to_string(i) + ": ";
						for (int j = this->get_head()->get_sub_object("P1_Cargo_Area")->cargoes[i].size() - 1; j >= 0; j--) {
							msg += this->get_head()->get_sub_object("P1_Cargo_Area")->cargoes[i][j] + " ";
							helper[i] += msg;
							msg = "";
						}
					}
				}
				if (save_msg == msg) msg += "--";
				for (int i = 1; i <= helper.size(); i++)
					msg += helper[i];
				msg += "|";
				this->emit_signal(SIGNAL_D(cl_cargoareas::signal_from_cargoareas), msg);
				break;
			}
			case 2: {
				for (int i = 0; i < this->get_head()->get_sub_object("P2_Cargo_Area")->cargoes.size(); i++) {
					if (!this->get_head()->get_sub_object("P2_Cargo_Area")->cargoes[i].empty() && helper[i].empty()) {
						msg += "-- s " + std::to_string(i) + ": ";
						for (int j = this->get_head()->get_sub_object("P2_Cargo_Area")->cargoes[i].size() - 1; j >= 0; j--) {
							msg += this->get_head()->get_sub_object("P2_Cargo_Area")->cargoes[i][j] + " ";
							helper[i] += msg;
							msg = "";
						}
					}
				}
				if (save_msg == msg) msg += "--";
				for (int i = 1; i <= helper.size(); i++)
					msg += helper[i];
				msg += "|";
				this->emit_signal(SIGNAL_D(cl_cargoareas::signal_from_cargoareas), msg);
				break;
			}
			case 3: {
				for (int i = 0; i < this->get_head()->get_sub_object("P3_Cargo_Area")->cargoes.size(); i++) {
					if (!this->get_head()->get_sub_object("P3_Cargo_Area")->cargoes[i].empty() && helper[i].empty()) {
						msg += "-- s " + std::to_string(i) + ": ";
						for (int j = this->get_head()->get_sub_object("P3_Cargo_Area")->cargoes[i].size() - 1; j >= 0; j--) {
							msg += this->get_head()->get_sub_object("P3_Cargo_Area")->cargoes[i][j] + " ";
							helper[i] += msg;
							msg = "";
						}
					}
				}
				if (save_msg == msg) msg += "--";
				for (int i = 1; i <= helper.size(); i++)
					msg += helper[i];
				msg += "|";
				this->emit_signal(SIGNAL_D(cl_cargoareas::signal_from_cargoareas), msg);
				break;
			}
		}
	}
}

void cl_cargoareas::signal_from_cargoareas(std::string& msg) {}