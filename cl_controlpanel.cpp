
//----------------------------------------------------------КВ-5--------------------------------------------------------------//

#include "cl_controlpanel.h"
#include <iostream>
#include <cmath>
#define PI 3.1415

cl_controlpanel::cl_controlpanel(cl_base* p_head, std::string s_name, int crane_boom_corner, int cart_way, std::string hook) : cl_base(p_head, s_name) {
	object_class = 2; 
	this->crane_boom_corner = crane_boom_corner;
	this->cart_way = cart_way;
	this->hook = hook;
} //Конструктор класса наследованный от класса cl_base 

void cl_controlpanel::signal_f(std::string& msg) {
	msg += " (class: 3)";
	std::cout << "Signal from " << this->Absolute_Way() << std::endl;

}

void cl_controlpanel::handler_f(std::string msg) {
	std::cout << "Signal to " << this->Absolute_Way() << " Text:  " << msg << std::endl;
}

void cl_controlpanel::func(int number_square_house, std::string name) {
	bool control_flag = true;
	int length, width;
	if (control_flag) {
		for (int i = 0; i < this->get_head()->get_sub_object("HouseArea")->left_house_part.size(); i++) {
			if (this->get_head()->get_sub_object("HouseArea")->left_house_part[i] == number_square_house) {
				if (this->get_head()->get_sub_object("HouseArea")->length_house % 2 == 1)
					length = (this->get_head()->get_sub_object("HouseArea")->length_house / 2) * 4 - ((number_square_house % this->get_head()->get_sub_object("HouseArea")->length_house) * 4 - 2) + 2;
				else
					length = (this->get_head()->get_sub_object("HouseArea")->length_house / 2) * 4 - ((number_square_house % this->get_head()->get_sub_object("HouseArea")->length_house) * 4 - 2);
				int level = number_square_house / this->get_head()->get_sub_object("HouseArea")->length_house; if (number_square_house % this->get_head()->get_sub_object("HouseArea")->length_house == 0) level -= 1;
				level += 1;
				width = this->get_head()->get_sub_object("HouseArea")->width_house * 4 - level * 4 + 6;
				this->cart_way = (int)(sqrtf(pow(length, 2) + pow(width, 2)));
				this->crane_boom_corner = 180 - (int)(atan(((float)width / (float)length)) * 180.0 / PI);
				this->get_head()->tick += 1;
				this->call_helper_handlers();
				cl_base* p_head = this->get_head()->get_sub_object("HouseArea");
				new cl_base(p_head, name);
				p_head->get_sub_object(name)->Set_Readiness(10);
				this->get_head()->get_sub_object("HouseArea")->house_area[number_square_house].push_back(name);
				this->hook = "";
				this->get_head()->get_sub_object("ControlPanel")->cargo_in_hook = "";
				//this->get_head()->tick += 1; --?
				//this->call_helper_handlers();
				this->crane_boom_corner = 0;
				this->get_head()->tick += 1;
				this->call_helper_handlers();
				control_flag = false;
			}
		}
	}
	if (control_flag) {
		for (int i = 0; i < this->get_head()->get_sub_object("HouseArea")->right_house_part.size(); i++) {
			if (this->get_head()->get_sub_object("HouseArea")->right_house_part[i] == number_square_house) {
				if (this->get_head()->get_sub_object("HouseArea")->length_house % 2 == 1)
					length = ((number_square_house % this->get_head()->get_sub_object("HouseArea")->length_house) == 0 ? this->get_head()->get_sub_object("HouseArea")->length_house : number_square_house % this->get_head()->get_sub_object("HouseArea")->length_house) * 4 - this->get_head()->get_sub_object("HouseArea")->length_house / 2 * 4 - 4;
					
				else
					length = ((number_square_house % this->get_head()->get_sub_object("HouseArea")->length_house) == 0 ? this->get_head()->get_sub_object("HouseArea")->length_house : number_square_house % this->get_head()->get_sub_object("HouseArea")->length_house) * 4 - this->get_head()->get_sub_object("HouseArea")->length_house / 2 * 4 - 2;
				int level = number_square_house / this->get_head()->get_sub_object("HouseArea")->length_house; if (number_square_house % this->get_head()->get_sub_object("HouseArea")->length_house == 0) level -= 1;
				level += 1;
				width = this->get_head()->get_sub_object("HouseArea")->width_house * 4 - level * 4 + 6;
				this->cart_way = (int)(sqrtf(pow(length, 2) + pow(width, 2)));
				this->crane_boom_corner = (int)(atan(((float)width / (float)length)) * 180.0 / PI);
				this->get_head()->tick += 1;
				this->call_helper_handlers();
				cl_base* p_head = this->get_head()->get_sub_object("HouseArea");
				new cl_base(p_head, name);
				p_head->get_sub_object(name)->Set_Readiness(10);
				this->get_head()->get_sub_object("HouseArea")->house_area[number_square_house].push_back(name);
				this->hook = "";
				this->get_head()->get_sub_object("ControlPanel")->cargo_in_hook = "";
				//this->get_head()->tick += 1; --?
				//this->call_helper_handlers();
				this->crane_boom_corner = 0;
				this->get_head()->tick += 1;
				this->call_helper_handlers();
				control_flag = false;
			}
		}
	}
	if (control_flag) {
		for (int i = 0; i < this->get_head()->get_sub_object("HouseArea")->center_house_part.size(); i++) {
			if (this->get_head()->get_sub_object("HouseArea")->center_house_part[i] == number_square_house) {
				length = 0;
				int level = number_square_house / this->get_head()->get_sub_object("HouseArea")->length_house; if (number_square_house % this->get_head()->get_sub_object("HouseArea")->length_house == 0) level -= 1;
				level += 1;
				width = this->get_head()->get_sub_object("HouseArea")->width_house * 4 - level * 4 + 6;
				this->cart_way = (int)(sqrtf(pow(length, 2) + pow(width, 2)));
				this->crane_boom_corner = 90;
				this->get_head()->tick += 1;
				this->call_helper_handlers();
				cl_base* p_head = this->get_head()->get_sub_object("HouseArea");
				new cl_base(p_head, name);
				p_head->get_sub_object(name)->Set_Readiness(10);
				this->get_head()->get_sub_object("HouseArea")->house_area[number_square_house].push_back(name);
				this->hook = "";
				this->get_head()->get_sub_object("ControlPanel")->cargo_in_hook = "";
				//this->get_head()->tick += 1; --?
				//this->call_helper_handlers();
				this->crane_boom_corner = 0;
				this->get_head()->tick += 1;
				this->call_helper_handlers();
				control_flag = false;
			}
		}
	}
}

void cl_controlpanel::distribution_for_first_area(int number_of_square, int number_square_house, std::string name, int i) {
	double length = 0, width = 0;
	if (number_of_square == 1 || number_of_square == 4 || number_of_square == 7) {
		length = 16;
		if (number_of_square == 1) width = 2;
		else if (number_of_square == 4) width = 6;
		else width = 10; 
		this->crane_boom_corner = 180 + (int)(atan(width / length) * 180.0 / PI);
		this->cart_way = (int)(sqrtf(pow(length, 2) + pow(width, 2)));
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		this->hook = name;
		this->get_head()->get_sub_object("ControlPanel")->cargo_in_hook = name;
		//Обработка груза на крюке//
		//std::string msg = "The cargo " + name + " is located on the hook of the tower crane";  --?
		//this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), msg); 
		//-----------------------//
		this->get_head()->get_sub_object("P1_Cargo_Area")->Delete_Object(name);
		this->get_head()->get_sub_object("P1_Cargo_Area")->cargoes[i].pop_back();
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		//this->crane_boom_corner = 90;  --?
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		func(number_square_house, name);
	}
	else if (number_of_square == 2 || number_of_square == 5 || number_of_square == 8) {
		length = 12;
		if (number_of_square == 2) width = 2;
		else if (number_of_square == 5) width = 6;
		else width = 10;
		this->cart_way = (int)(sqrtf(pow(length, 2) + pow(width, 2)));
		this->crane_boom_corner = 180 + (int)(atan(width / length) * 180.0 / PI);
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		this->hook = name;
		this->get_head()->get_sub_object("ControlPanel")->cargo_in_hook = name;
		//Обработка груза на крюке//
		//std::string msg = "The cargo " + name + " is located on the hook of the tower crane";  --?
		//this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), msg);
		//-----------------------//
		this->get_head()->get_sub_object("P1_Cargo_Area")->Delete_Object(name);
		this->get_head()->get_sub_object("P1_Cargo_Area")->cargoes[i].pop_back();
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		//this->crane_boom_corner = 90;  --?
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		func(number_square_house, name);
	}
	else if (number_of_square == 3 || number_of_square == 6 || number_of_square == 9) {
		length = 8;
		if (number_of_square == 3) width = 2;
		else if (number_of_square == 6) width = 6;
		else width = 10;
		this->cart_way = (int)(sqrtf(pow(length, 2) + pow(width, 2)));
		this->crane_boom_corner = 180 + (int)(atan(width / length) * 180.0 / PI);
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		this->hook = name;
		this->get_head()->get_sub_object("ControlPanel")->cargo_in_hook = name;
		//Обработка груза на крюке//
		//std::string msg = "The cargo " + name + " is located on the hook of the tower crane";  --?
		//this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), msg);
		//-----------------------//
		this->get_head()->get_sub_object("P1_Cargo_Area")->Delete_Object(name);
		this->get_head()->get_sub_object("P1_Cargo_Area")->cargoes[i].pop_back();
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		//this->crane_boom_corner = 90;  --?
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		func(number_square_house, name);
	}
}

void cl_controlpanel::distribution_for_second_area(int number_of_square, int number_square_house, std::string name, int i) {
	int length = 0, width = 0;
	if (number_of_square == 1 || number_of_square == 4 || number_of_square == 7) {
		length = 4;
		if (number_of_square == 1) width = 14;
		else if (number_of_square == 4) width = 18;
		else width = 22;
		this->cart_way = (int)(sqrtf(pow(length, 2) + pow(width, 2)));
		this->crane_boom_corner = 270 - (int)(atan(width / length) * 180.0 / PI);
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		this->hook = name;
		this->get_head()->get_sub_object("ControlPanel")->cargo_in_hook = name;
		//Обработка груза на крюке//
		//std::string msg = "The cargo " + name + " is located on the hook of the tower crane";  --?
		//this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), msg);
		//-----------------------//
		this->get_head()->get_sub_object("P2_Cargo_Area")->Delete_Object(name);
		this->get_head()->get_sub_object("P2_Cargo_Area")->cargoes[i].pop_back();
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		//this->crane_boom_corner = 90;  --?
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		func(number_square_house, name);
	}
	else if (number_of_square == 2 || number_of_square == 5 || number_of_square == 8) {
		length = 0;
		if (number_of_square == 2) width = 14;
		else if (number_of_square == 5) width = 18;
		else width = 22;
		this->cart_way = (int)(sqrtf(pow(length, 2) + pow(width, 2)));
		this->crane_boom_corner = 270;
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		this->hook = name;
		this->get_head()->get_sub_object("ControlPanel")->cargo_in_hook = name;
		//Обработка груза на крюке//
		//std::string msg = "The cargo " + name + " is located on the hook of the tower crane";  --?
		//this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), msg);
		//-----------------------//
		this->get_head()->get_sub_object("P2_Cargo_Area")->Delete_Object(name);
		this->get_head()->get_sub_object("P2_Cargo_Area")->cargoes[i].pop_back();
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		//this->crane_boom_corner = 90;  --?
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		func(number_square_house, name);
	}
	else if (number_of_square == 3 || number_of_square == 6 || number_of_square == 9) {
		length = 4;
		if (number_of_square == 3) width = 14;
		else if (number_of_square == 6) width = 18;
		else width = 22;
		this->cart_way = (int)(sqrtf(pow(length, 2) + pow(width, 2)));
		this->crane_boom_corner = 270 + (int)(atan(width / length) * 180.0 / PI);
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		this->hook = name;
		this->get_head()->get_sub_object("ControlPanel")->cargo_in_hook = name;
		//Обработка груза на крюке//
		//std::string msg = "The cargo " + name + " is located on the hook of the tower crane";  --?
		//this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), msg);
		//-----------------------//
		this->get_head()->get_sub_object("P2_Cargo_Area")->Delete_Object(name);
		this->get_head()->get_sub_object("P2_Cargo_Area")->cargoes[i].pop_back();
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		//this->crane_boom_corner = 90;  --?
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		func(number_square_house, name);
	}
}

void cl_controlpanel::distribution_for_thrid_area(int number_of_square, int number_square_house, std::string name, int i) {
	int length = 0, width = 0;
	if (number_of_square == 1 || number_of_square == 4 || number_of_square == 7) {
		length = 8;
		if (number_of_square == 1) width = 2;
		else if (number_of_square == 4) width = 6;
		else width = 10;
		this->cart_way = (int)(sqrtf(pow(length, 2) + pow(width, 2)));
		this->crane_boom_corner = 360 - (int)(atan(width / length) * 180.0 / PI);
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		this->hook = name;
		this->get_head()->get_sub_object("ControlPanel")->cargo_in_hook = name;
		//Обработка груза на крюке//
		//std::string msg = "The cargo " + name + " is located on the hook of the tower crane";  --?
		//this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), msg);
		//-----------------------//
		this->get_head()->get_sub_object("P3_Cargo_Area")->Delete_Object(name);
		this->get_head()->get_sub_object("P3_Cargo_Area")->cargoes[i].pop_back();
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		//this->crane_boom_corner = 90;  --?
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		func(number_square_house, name);
	}
	else if (number_of_square == 2 || number_of_square == 5 || number_of_square == 8) {
		length = 12;
		if (number_of_square == 2) width = 2;
		else if (number_of_square == 5) width = 6;
		else width = 10;
		this->cart_way = (int)(sqrtf(pow(length, 2) + pow(width, 2)));
		this->crane_boom_corner = 360 - (int)(atan(width / length) * 180.0 / PI);
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		this->hook = name;
		this->get_head()->get_sub_object("ControlPanel")->cargo_in_hook = name;
		//Обработка груза на крюке//
		//std::string msg = "The cargo " + name + " is located on the hook of the tower crane";  --?
		//this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), msg);
		//-----------------------//
		this->get_head()->get_sub_object("P3_Cargo_Area")->Delete_Object(name);
		this->get_head()->get_sub_object("P3_Cargo_Area")->cargoes[i].pop_back();
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		//this->crane_boom_corner = 90;  --?
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		func(number_square_house, name);
	}
	else if (number_of_square == 3 || number_of_square == 6 || number_of_square == 9) {
		length = 16;
		if (number_of_square == 3) width = 2;
		else if (number_of_square == 6) width = 6;
		else width = 10;
		this->cart_way = (int)(sqrtf(pow(length, 2) + pow(width, 2)));
		this->crane_boom_corner = 360 - (int)(atan(width / length) * 180.0 / PI);
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		this->hook = name;
		this->get_head()->get_sub_object("ControlPanel")->cargo_in_hook = name;
		//Обработка груза на крюке//
		//std::string msg = "The cargo " + name + " is located on the hook of the tower crane";  --?
		//this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), msg);
		//-----------------------//
		this->get_head()->get_sub_object("P3_Cargo_Area")->Delete_Object(name);
		this->get_head()->get_sub_object("P3_Cargo_Area")->cargoes[i].pop_back();
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		//this->crane_boom_corner = 90; --?
		this->get_head()->tick += 1;
		this->call_helper_handlers();
		func(number_square_house, name);
	}
}

void cl_controlpanel::handler_controlpanel_from_reader(std::string msg) {
	int number_of_square = 0;
	if (msg.substr(0, msg.find(" ", 11)) == "Submit the cargo") {
		std::string name = msg.substr(17, msg.find(" ", 17) - 17);
		int space = msg.find(" ", 17);
		int number_square_house = std::stoi(msg.substr(space + 1));
		if (this->get_head()->get_sub_object("P1_Cargo_Area")->get_sub_object(name) == nullptr &&
			this->get_head()->get_sub_object("P2_Cargo_Area")->get_sub_object(name) == nullptr &&
			this->get_head()->get_sub_object("P3_Cargo_Area")->get_sub_object(name) == nullptr &&
			this->get_head()->get_sub_object("HouseArea")->get_sub_object(name) == nullptr) {
				msg = "Cargo " + name + " not found";
				this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), msg); return;
		}
		else if (this->get_head()->get_sub_object("P1_Cargo_Area")->get_sub_object(name) == nullptr &&
			this->get_head()->get_sub_object("P2_Cargo_Area")->get_sub_object(name) == nullptr &&
			this->get_head()->get_sub_object("P3_Cargo_Area")->get_sub_object(name) == nullptr &&
			this->get_head()->get_sub_object("HouseArea")->get_sub_object(name) != nullptr) {
				msg = "The cargo " + name + " is located on the floor";
				this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), msg); return;
			}
		else {
			bool flag_1 = false;
			bool flag_2 = false;
			bool flag_3 = false;
			if (this->get_head()->get_sub_object("P1_Cargo_Area")->get_sub_object(name) != nullptr) {
				for (int i = 1; i <= 9; i++) {
					std::string s_name;
					if (!this->get_head()->get_sub_object("P1_Cargo_Area")->cargoes[i].empty()) {
						s_name = this->get_head()->get_sub_object("P1_Cargo_Area")->cargoes[i][this->get_head()->get_sub_object("P1_Cargo_Area")->cargoes[i].size() - 1];
						if (name == s_name) {
							flag_1 = true;
							number_of_square = i;
							distribution_for_first_area(number_of_square, number_square_house, name, i);
							break;
						}
					}
				}
				if (flag_1 == false) {
					msg = "The cargo " + name + " is not available";
					this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), msg);
					return;
				}
			}
			else if (this->get_head()->get_sub_object("P2_Cargo_Area")->get_sub_object(name) != nullptr) {
				for (int i = 1; i <= 9; i++) {
					std::string s_name;
					if (!this->get_head()->get_sub_object("P2_Cargo_Area")->cargoes[i].empty()) {
						s_name = this->get_head()->get_sub_object("P2_Cargo_Area")->cargoes[i][this->get_head()->get_sub_object("P2_Cargo_Area")->cargoes[i].size() - 1];
						if (name == s_name) {
							flag_2 = true;
							number_of_square = i;
							distribution_for_second_area(number_of_square, number_square_house, name, i);
							break;
						}
					}
				}
				if (flag_2 == false) {
					msg = "The cargo " + name + " is not available";
					this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), msg);
					return;
				}
			}
			else if (this->get_head()->get_sub_object("P3_Cargo_Area")->get_sub_object(name) != nullptr) {
				for (int i = 1; i <= 9; i++) {
					std::string s_name;
					if (!this->get_head()->get_sub_object("P3_Cargo_Area")->cargoes[i].empty()) {
						s_name = this->get_head()->get_sub_object("P3_Cargo_Area")->cargoes[i][this->get_head()->get_sub_object("P3_Cargo_Area")->cargoes[i].size() - 1];
						if (name == s_name) {
							flag_3 = true;
							number_of_square = i;
							distribution_for_thrid_area(number_of_square, number_square_house, name, i);
							break;
						}
					}
				}
				if (flag_3 == false) {
					msg = "The cargo " + name + " is not available";
					this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), msg);
					return;
				}
			}
		}
	}
	else if (msg == "Condition of the tower crane") {
		msg = "Tower crane " + std::to_string(this->crane_boom_corner) + " " + std::to_string(this->cart_way);
		this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), msg);
	}
}

void cl_controlpanel::call_helper_handlers() {
	while (true) {
		std::string additional_command;
		std::getline(std::cin, additional_command);
		if (additional_command.substr(0, additional_command.find(" ", 6)) == "Cargo condition" && additional_command.substr(additional_command.find(" ", 6) + 1) == this->hook) {
			additional_command = "|Cargo condition " + this->hook + ": in hook";
			this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), additional_command);
			break;
		}
		else if (additional_command.substr(0, additional_command.find(" ", 6)) == "Cargo condition" && this->get_head()->get_sub_object("HouseArea")->get_sub_object(additional_command.substr(additional_command.find(" ", 6) + 1)) != nullptr) {
			for (int i = 1; i <= this->get_head()->get_sub_object("HouseArea")->house_area.size(); i++) {
				if (!this->get_head()->get_sub_object("HouseArea")->house_area[i].empty()) {
					for (int j = 0; j < this->get_head()->get_sub_object("HouseArea")->house_area[i].size(); j++) {
						if (this->get_head()->get_sub_object("HouseArea")->house_area[i][j] == additional_command.substr(additional_command.find(" ", 6) + 1)) {
							additional_command += ": in floor square " + std::to_string(i) + "|";
							additional_command.pop_back();
							std::cout << additional_command << std::endl;
							break;
						}
					}
				}
			}
			break;
		}
		
		else if (additional_command != "" && additional_command.substr(0, additional_command.find(" ", 11)) != "Submit the cargo") {
			this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), additional_command);
			break;
		}
		else if (additional_command == "") break;
		else if (additional_command.substr(0, additional_command.find(" ", 11)) == "Submit the cargo") { //--?
			if (this->hook == additional_command.substr(17, additional_command.find(" ", 18) - 17)) {
				additional_command = "The cargo " + this->hook + " is located on the hook of the tower crane";
				this->emit_signal(SIGNAL_D(cl_controlpanel::singnal_controlpanel), additional_command);
			}
			break;
		}
	}
}

void cl_controlpanel::singnal_controlpanel(std::string& msg) {}