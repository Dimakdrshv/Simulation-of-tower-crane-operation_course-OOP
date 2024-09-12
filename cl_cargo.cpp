
//----------------------------------------------------------КВ-5--------------------------------------------------------------//

#include "cl_cargo.h"
#include <iostream>

cl_cargo::cl_cargo(cl_base* p_head, std::string s_name, int number_of_area, int number_of_square, float length, float width, float height) : cl_base(p_head, s_name) { 
	object_class = 6;
	this->number_of_area = number_of_area;
	this->number_of_square = number_of_square;
	this->length = length;
	this->width = width;
	this->height = height;
} //Конструктор класса наследованный от класса cl_base 

void cl_cargo::signal_f(std::string& msg) {
	msg += " (class: 6)";
	std::cout << "Signal from " << this->Absolute_Way() << std::endl; 

}

void cl_cargo::handler_f(std::string msg) {
	std::cout << "Signal to " << this->Absolute_Way() << " Text:  " << msg << std::endl;
}

void cl_cargo::handler_cargo_from_reader(std::string msg) {
	if (msg == "cargo") {
		std::string first_three_commands;
		while (true) {
			getline(std::cin, first_three_commands);
			if (first_three_commands == "End of cargos") {
				this->get_head()->Delete_Object("Cargo"); //?
				msg = "Ready to work";
				this->emit_signal(SIGNAL_D(cl_cargo::signal_from_cargo), msg);
				return;
			}
			if (!first_three_commands.empty()) {
				int number_of_area = std::stoi(first_three_commands.substr(0, 1));
				int number_of_square = std::stoi(first_three_commands.substr(2, 1));
				int index_space;
				std::string name = first_three_commands.substr(4, first_three_commands.find(" ", 4) - 4);
				index_space = first_three_commands.find(" ", 4);
				float length = std::stof(first_three_commands.substr(index_space + 1, first_three_commands.find(" ", index_space + 1)));
				index_space = first_three_commands.find(" ", index_space + 1);
				float width = std::stof(first_three_commands.substr(index_space + 1, first_three_commands.find(" ", index_space + 1))); 
				index_space = first_three_commands.find(" ", index_space + 1);
				float height = std::stof(first_three_commands.substr(index_space + 1, first_three_commands.find(" ", index_space + 1)));
				switch (number_of_area) {
				case 1: {
					cl_base* cargo = new cl_cargo(this->get_head()->get_sub_object("P1_Cargo_Area"), name, number_of_area, number_of_square, length, width, height);
					this->get_head()->get_sub_object("P1_Cargo_Area")->cargoes[number_of_square].push_back(name);
					cargo->Set_Readiness(10);
					break;
				}
				case 2: {
					cl_base* cargo = new cl_cargo(this->get_head()->get_sub_object("P2_Cargo_Area"), name, number_of_area, number_of_square, length, width, height);
					this->get_head()->get_sub_object("P2_Cargo_Area")->cargoes[number_of_square].push_back(name);
					cargo->Set_Readiness(10);
					break;
				}
				case 3: {
					cl_base* cargo = new cl_cargo(this->get_head()->get_sub_object("P3_Cargo_Area"), name, number_of_area, number_of_square, length, width, height);
					this->get_head()->get_sub_object("P3_Cargo_Area")->cargoes[number_of_square].push_back(name);
					cargo->Set_Readiness(10);
					break;
				}
				default: break;
				}
			}
		}
	}
	else if (msg.substr(0, msg.find(" ", 6)) == "Cargo condition") {
		std::string name = msg.substr(msg.find(" ", 6) + 1);
		bool control_flag = true;
		if (control_flag) {
			for (int i = 1; i <= this->get_head()->get_sub_object("P1_Cargo_Area")->cargoes.size() && control_flag; i++) {
				if (!this->get_head()->get_sub_object("P1_Cargo_Area")->cargoes[i].empty()) {
					for (int j = 0; j < this->get_head()->get_sub_object("P1_Cargo_Area")->cargoes[i].size(); j++) {
						if (this->get_head()->get_sub_object("P1_Cargo_Area")->cargoes[i][j] == name) {
							msg += ": in area 1, square " + std::to_string(i) + "|";
							control_flag = false;
							this->emit_signal(SIGNAL_D(cl_cargo::signal_from_cargo), msg);
						}
					}
				}
			}
		}
		if (control_flag) {
			for (int i = 1; i <= this->get_head()->get_sub_object("P2_Cargo_Area")->cargoes.size() && control_flag; i++) {
				if (!this->get_head()->get_sub_object("P2_Cargo_Area")->cargoes[i].empty()) {
					for (int j = 0; j < this->get_head()->get_sub_object("P2_Cargo_Area")->cargoes[i].size(); j++) {
						if (this->get_head()->get_sub_object("P2_Cargo_Area")->cargoes[i][j] == name) {
							msg += ": in area 2, square " + std::to_string(i) + "|";
							control_flag = false;
							this->emit_signal(SIGNAL_D(cl_cargo::signal_from_cargo), msg);
						}
					}
				}
			}
		}
		if (control_flag) {
			for (int i = 1; i <= this->get_head()->get_sub_object("P3_Cargo_Area")->cargoes.size() && control_flag; i++) {
				if (!this->get_head()->get_sub_object("P3_Cargo_Area")->cargoes[i].empty()) {
					for (int j = 0; j < this->get_head()->get_sub_object("P3_Cargo_Area")->cargoes[i].size(); j++) {
						if (this->get_head()->get_sub_object("P3_Cargo_Area")->cargoes[i][j] == name) {
							msg += ": in area 3, square " + std::to_string(i) + "|";
							control_flag = false;
							this->emit_signal(SIGNAL_D(cl_cargo::signal_from_cargo), msg);
						}
					}
				}
			}
		}
		if (control_flag) {
			if (this->get_head()->get_sub_object("ControlPanel")->cargo_in_hook == name) {
				msg += ": in hook|";
				control_flag = false;
				this->emit_signal(SIGNAL_D(cl_cargo::signal_from_cargo), msg);
			}
		}
		if (control_flag) {
			for (int i = 1; i <= this->get_head()->get_sub_object("HouseArea")->house_area.size() && control_flag; i++) {
				if (!this->get_head()->get_sub_object("HouseArea")->house_area[i].empty()) {
					for (int j = 0; j < this->get_head()->get_sub_object("HouseArea")->house_area[i].size(); j++) {
						if (this->get_head()->get_sub_object("HouseArea")->house_area[i][j] == name) {
							msg += ": in floor square " + std::to_string(i) + "|";
							control_flag = false;
							this->emit_signal(SIGNAL_D(cl_cargo::signal_from_cargo), msg);
						}
					}
				}
			}
		}
		if (control_flag) {
			msg = "Cargo " + name + " not found";
			control_flag = false;
			this->emit_signal(SIGNAL_D(cl_cargo::signal_from_cargo), msg);
		}
	}
}

void cl_cargo::signal_from_cargo(std::string& msg) {}