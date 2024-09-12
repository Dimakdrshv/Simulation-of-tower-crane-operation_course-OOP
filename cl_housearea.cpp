
//---------------------------------------------------------- ¬-5--------------------------------------------------------------//

#include "cl_housearea.h"
#include <iostream>

cl_housearea::cl_housearea(cl_base* p_head, std::string s_name) : cl_base(p_head, s_name) { object_class = 5; } // онструктор класса наследованный от класса cl_base 

void cl_housearea::signal_f(std::string& msg) {
	msg += " (class: 6)";
	std::cout << "Signal from " << this->Absolute_Way() << std::endl;

}

void cl_housearea::handler_f(std::string msg) {
	std::cout << "Signal to " << this->Absolute_Way() << " Text:  " << msg << std::endl;
}

void cl_housearea::handler_housearea_from_reader(std::string msg) {
	if (msg == "house_size") {
		std::cin >> this->width >> this->length >> this->floor;
		this->get_head()->get_sub_object("HouseArea")->length_house = this->length / 4; this->get_head()->get_sub_object("HouseArea")->width_house = this->width / 4;
		int length_square = this->length / 4, width_square = this->width / 4;
		int index = 1;
		for (int i = 1; i <= length_square * width_square; i++) {
			if (i % length_square <= length_square / 2 && i % length_square != 0)
				this->get_head()->get_sub_object("HouseArea")->left_house_part.push_back(i); //–аспределение квадратов дома на левую часть, правую часть, центральную часть
			else if (i == length_square / 2 + index && length_square % 2 != 0) {
				this->get_head()->get_sub_object("HouseArea")->center_house_part.push_back(i);
				index += length_square;
			}
			else this->get_head()->get_sub_object("HouseArea")->right_house_part.push_back(i);
		}
	}
	else if (msg == "Floor condition") { //»справить, если на квадрат дома можно будет запилить больше, чем 1 груз
		msg += " ";
		for (int i = 1; i <= this->house_area.size(); i++) {
			if (!this->house_area[i].empty()) {
				msg += "s " + std::to_string(i) + ": ";
				for (int j = this->house_area[i].size() - 1; j >= 0; j--) {
					msg += this->house_area[i][j] + " ";
				}
			}
		}
		this->emit_signal(SIGNAL_D(cl_housearea::signal_from_house_area), msg);
	}
}

void cl_housearea::signal_from_house_area(std::string& msg) {}