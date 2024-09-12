#include "cl_application.h"
#include <iostream>

cl_application::cl_application(cl_base* p_head) : cl_base(p_head) { object_class = 0; } // //Конструтор класса, наследованный от класса cl_base

//----------------------------------------------------------КВ-5--------------------------------------------------------------// Поменял floor construction на floor condition

void cl_application::build_tree_objects_4() {
	cl_base* p_head = this;
	cl_base* p_sub = nullptr;
	p_head->set_name("System");
	//Создание новых объектов//

	p_sub = new cl_reader(p_head, "Reader");
	p_sub = new cl_controlpanel(p_head, "ControlPanel");
	p_sub = new cl_cargo(p_head, "Cargo");
	p_sub = new cl_cargoareas(p_head, "P1_Cargo_Area");
	p_sub = new cl_cargoareas(p_head, "P2_Cargo_Area");
	p_sub = new cl_cargoareas(p_head, "P3_Cargo_Area");
	p_sub = new cl_housearea(p_head, "HouseArea");
	p_sub = new cl_screen(p_head, "Screen");
	
	//Установка готовности объектам//

	p_head->turn_on_objects();
	//p_head->Print_Readiness(); //ЭТО НЕ НАДО ВЫВОДИТЬ

	//Установка связей сигналов и обработчиков//

	this->set_connection(SIGNAL_D(cl_application::signal_from_app_into_reader), this->get_sub_object("Reader"), HANDLER_D(cl_reader::handler_reader_from_app));
	this->get_sub_object("Reader")->set_connection(SIGNAL_D(cl_reader::signal_from_reader_to_all), this->get_sub_object("Screen"), HANDLER_D(cl_screen::handler_screen_from_reader));
	this->get_sub_object("Reader")->set_connection(SIGNAL_D(cl_reader::signal_from_reader_to_all), this->get_sub_object("HouseArea"), HANDLER_D(cl_housearea::handler_housearea_from_reader));
	this->get_sub_object("Reader")->set_connection(SIGNAL_D(cl_reader::signal_from_reader_to_all), this->get_sub_object("Cargo"), HANDLER_D(cl_cargo::handler_cargo_from_reader));
	this->get_sub_object("Reader")->set_connection(SIGNAL_D(cl_reader::signal_from_reader_to_all), this, HANDLER_D(cl_application::app_handler));
	this->get_sub_object("Reader")->set_connection(SIGNAL_D(cl_reader::signal_from_reader_to_all), this->get_sub_object("ControlPanel"), HANDLER_D(cl_controlpanel::handler_controlpanel_from_reader));
	this->get_sub_object("ControlPanel")->set_connection(SIGNAL_D(cl_controlpanel::singnal_controlpanel), this->get_sub_object("Screen"), HANDLER_D(cl_screen::handler_screen_from_reader));
	this->get_sub_object("Cargo")->set_connection(SIGNAL_D(cl_cargo::signal_from_cargo), this->get_sub_object("Screen"), HANDLER_D(cl_screen::handler_screen_from_reader));
	this->get_sub_object("Reader")->set_connection(SIGNAL_D(cl_reader::signal_from_reader_to_all), this->get_sub_object("P1_Cargo_Area"), HANDLER_D(cl_cargoareas::handler_cargoareas_from_reader));
	this->get_sub_object("P1_Cargo_Area")->set_connection(SIGNAL_D(cl_cargoareas::signal_from_cargoareas), this->get_sub_object("Screen"), HANDLER_D(cl_screen::handler_screen_from_reader));
	this->get_sub_object("HouseArea")->set_connection(SIGNAL_D(cl_housearea::signal_from_house_area), this->get_sub_object("Screen"), HANDLER_D(cl_screen::handler_screen_from_reader));
	this->get_sub_object("ControlPanel")->set_connection(SIGNAL_D(cl_controlpanel::singnal_controlpanel), this->get_sub_object("Reader"), HANDLER_D(cl_reader::handler_reader_from_app));
	//Цикл для обработки вводимых данных//

	this->application_commad = "house_size"; //Для площадки дома дома
	this->emit_signal(SIGNAL_D(cl_application::signal_from_app_into_reader), this->application_commad);
	
	this->application_commad = "cargo";
	this->emit_signal(SIGNAL_D(cl_application::signal_from_app_into_reader), this->application_commad);
	//p_head->Print_Readiness(); //ЭТО НЕ НАДО ВЫВОДИТЬ
}

void cl_application::signal_from_app_into_reader(std::string& msg) {
	//----Сигнал от системы к окну ввода----//
}

void cl_application::app_handler(std::string msg) {
	//----Обработчик сигналов----//
	if (msg == "Turn off the system") {
		//this->Print_Tree(); //ЭТО НЕ НАДО ВЫВОДИТЬ
		exit(0);
	}
	else if (msg == "SHOWTREE") {
		this->Print_Readiness();
		exit(0);
	}
}

int cl_application::exec_app_4() {
	while (true) {
		std::getline(std::cin, this->application_commad);
		this->emit_signal(SIGNAL_D(cl_application::signal_from_app_into_reader), this->application_commad);
		this->tick += 1;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------КВ-4--------------------------------------------------------------//

/*std::vector<cl_base*> all_objects;
std::vector <TYPE_SIGNAL> signals = { SIGNAL_D(cl_application::signal_f), SIGNAL_D(cl_1::signal_f),  SIGNAL_D(cl_2::signal_f),  SIGNAL_D(cl_3::signal_f),  SIGNAL_D(cl_4::signal_f),  SIGNAL_D(cl_5::signal_f) };
std::vector <TYPE_HANDLER> handlers = { HANDLER_D(cl_application::handler_f), HANDLER_D(cl_1::handler_f), HANDLER_D(cl_2::handler_f), HANDLER_D(cl_3::handler_f), HANDLER_D(cl_4::handler_f), HANDLER_D(cl_5::handler_f) };

//
void cl_application::signal_f(std::string& msg) {
	msg += " (class: 1)";
	std::cout << "Signal from " << this->Absolute_Way() << std::endl;

}

void cl_application::handler_f(std::string msg) {
	std::cout << "Signal to " << this->Absolute_Way() << " Text:  " << msg << std::endl;
}
//

void cl_application::build_tree_objects_3() {
	std::string s_head_name, s_sub_name; //Объявление вспомогательных переменных типа string
	cl_base* p_head = this; //Создание главного указателя, указывающего на данный объект
	cl_base* p_sub = nullptr; //Инициализация указателя подчиненных объектов
	std::cin >> s_head_name; //Инициализация названия главного объекта
	set_name(s_head_name); //Установление имени на главный объект
	int number, state; //Инициализация номера класса объекта и уровня готовности
	while (true) { //Бесконечный цикл
		std::cin >> s_head_name; //Ввод имени головного объекта
		if (s_head_name == "endtree") break; //Проверка на окончание бесконечного цикла
		std::cin >> s_sub_name >> number; //Ввод имени подчиненного объекта и номера класса объекта
		p_head = find_object_by_coordinate(s_head_name); //Нахождение указателя головного элемента в дереве иеррархии
		if (p_head != nullptr) {
			if (p_head->get_sub_object(s_sub_name) == nullptr) { //Проверка на уникальность имени подчиненного объекта на ветке и правильности ввода координат
				switch (number) { //Определение подчиненного объекта в соответствующий класс
				case 2:
					p_sub = new cl_1(p_head, s_sub_name);
					all_objects.push_back(p_head); all_objects.push_back(p_sub);
					break;
				case 3:
					p_sub = new cl_2(p_head, s_sub_name);
					all_objects.push_back(p_head); all_objects.push_back(p_sub);
					break;
				case 4:
					p_sub = new cl_3(p_head, s_sub_name);
					all_objects.push_back(p_head); all_objects.push_back(p_sub);
					break;
				case 5:
					p_sub = new cl_4(p_head, s_sub_name);
					all_objects.push_back(p_head); all_objects.push_back(p_sub);
					break;
				case 6:
					p_sub = new cl_5(p_head, s_sub_name);
					all_objects.push_back(p_head); all_objects.push_back(p_sub);
					break;
				default: break;
				}
			}
			else
				std::cout << s_sub_name << "     Dubbing the names of subordinate objects" << std::endl;
		}
		else {
			std::cout << "Object tree" << std::endl;
			this->Print_Tree();
			std::cout << "The head object " << s_head_name << " is not found" << std::endl;
			exit(1);
		}
	}
}

void cl_application::setup_connection() {
	std::string current_object_name, target_object_name; //Объявление вспомогательных переменных типа string
	while (true) {
		std::cin >> current_object_name;
		if (current_object_name == "end_of_connections") return;
		std::cin >> target_object_name;
		cl_base* current_object = find_object_by_coordinate(current_object_name);
		cl_base* target_object = find_object_by_coordinate(target_object_name);
		if (current_object != nullptr && target_object != nullptr) {
			TYPE_SIGNAL signal_t = signals[current_object->object_class];
			TYPE_HANDLER handler_t = handlers[target_object->object_class];
			current_object->set_connection(signal_t, target_object, handler_t);
		}
	}		
}

int cl_application::exec_app_3() {
	for (auto object : all_objects)
		object->Set_Readiness(2);
	cl_base* current_object = this;
	std::string command_text1_text2;
	while (true) {
		std::getline(std::cin, command_text1_text2);
		int space_1 = command_text1_text2.find(" ");
		std::string command = command_text1_text2.substr(0, space_1);
		int space_2 = command_text1_text2.find(" ", space_1 + 1);
		std::string text_1 = command_text1_text2.substr(space_1 + 1, space_2 - space_1 - 1);
		current_object = find_object_by_coordinate(text_1);
		std::string text_2 = command_text1_text2.substr(space_2 + 1);
		if (command == "EMIT") {
			if (current_object == nullptr) {
				std::cout << "Object " << text_1 << " not found" << std::endl; 
			}
			else 
				current_object->emit_signal(signals[current_object->object_class], text_2);
		}
		else if (command == "SET_CONNECT") {
			cl_base* target_object = find_object_by_coordinate(text_2);
			if (current_object == nullptr) {
				std::cout << "Object " << text_1 << " not found" << std::endl; 
			}
			else {
				if (target_object != nullptr)
					current_object->set_connection(signals[current_object->object_class], target_object, handlers[target_object->object_class]);
				else
					std::cout << "Handler object " << text_2 << " not found" << std::endl;
			}
		}
		else if (command == "DELETE_CONNECT") {
			cl_base* target_object = find_object_by_coordinate(text_2);
			if (current_object == nullptr) {
				std::cout << "Object " << text_1 << " not found" << std::endl;
			}
			else {
				if (target_object != nullptr)
					current_object->delete_connection(signals[current_object->object_class], target_object, handlers[target_object->object_class]);
				else
					std::cout << "Handler object " << text_2 << " not found" << std::endl;
			}
		}
		else if (command == "SET_CONDITION") {
			if (current_object == nullptr) {
				std::cout << "Object " << text_1 << " not found" << std::endl;
			}
			else 
				current_object->Set_Readiness(std::stoi(text_2));
		}
		else if (command == "END") {
			break;
		}
	}
	return 0;
}
//----------------------------------------------------------КВ-3--------------------------------------------------------------//

void cl_application::build_tree_objects_2() {
	std::string s_head_name, s_sub_name; //Объявление вспомогательных переменных типа string
	cl_base* p_head = this; //Создание главного указателя, указывающего на данный объект
	cl_base* p_sub = nullptr; //Инициализация указателя подчиненных объектов
	std::cin >> s_head_name; //Инициализация названия главного объекта
	set_name(s_head_name); //Установление имени на главный объект
	int number, state; //Инициализация номера класса объекта и уровня готовности
	while (true) { //Бесконечный цикл
		std::cin >> s_head_name; //Ввод имени головного объекта
		if (s_head_name == "endtree") break; //Проверка на окончание бесконечного цикла
		std::cin >> s_sub_name >> number; //Ввод имени подчиненного объекта и номера класса объекта
		p_head = find_object_by_coordinate(s_head_name); //Нахождение указателя головного элемента в дереве иеррархии
		if (p_head != nullptr) {
			if (p_head->get_sub_object(s_sub_name) == nullptr) { //Проверка на уникальность имени подчиненного объекта на ветке и правильности ввода координат
				switch (number) { //Определение подчиненного объекта в соответствующий класс
				case 2:
					p_sub = new cl_1(p_head, s_sub_name);
					break;
				case 3:
					p_sub = new cl_2(p_head, s_sub_name);
					break;
				case 4:
					p_sub = new cl_3(p_head, s_sub_name);
					break;
				case 5:
					p_sub = new cl_4(p_head, s_sub_name);
					break;
				case 6:
					p_sub = new cl_5(p_head, s_sub_name);
					break;
				default: break;
				}
			}
			else
				std::cout << s_sub_name << "     Dubbing the names of subordinate objects" << std::endl;
		}
		else {
			std::cout << "Object tree" << std::endl;
			this->Print_Tree();
			std::cout << "The head object " << s_head_name << " is not found" << std::endl;
			exit(1);
		}
	}
}

std::string coordinate_set; // ВСПОМОГАТЕЛЬНОЕ ПОЛЕ

int cl_application::exec_app_2() {
	std::cout << "Object tree" << std::endl; //Вывод на экран надписи из условия задачи
	this->Print_Tree(); //Запуск метода вывода дерева иеррархии на экран 
	cl_base* current_object = this;
	std::string command_and_coordinate;
	while (true) {
		std::getline(std::cin, command_and_coordinate);
		int space = command_and_coordinate.find(" ");
		std::string command = command_and_coordinate.substr(0, space);
		std::string coordinate = command_and_coordinate.substr(space+1);
		if (command == "SET") {
			if (current_object->find_object_by_coordinate(coordinate) != nullptr) {
				current_object = current_object->find_object_by_coordinate(coordinate);
				std::cout << "Object is set: " << current_object->get_name() << std::endl;
				coordinate_set = coordinate; //ДОПИСАЛ
			}
			else 
				std::cout << "The object was not found at the specified coordinate: " << coordinate << std::endl;
		}
		if (command == "FIND") {
			if (current_object->find_object_by_coordinate(coordinate) != nullptr) {
				std::cout << coordinate << "     Object name: " << current_object->find_object_by_coordinate(coordinate)->get_name() << std::endl;
			}
			else 
				std::cout << coordinate << "     Object is not found" << std::endl;
		}
		if (command == "MOVE") { //ПЕРЕПИСАН
			std::string name = current_object->get_name();
			std::string help_name = coordinate.substr(0, name.length());
			std::string help_name_set = coordinate.substr(0, coordinate_set.length());
			if (coordinate[0] == '.' || help_name == name || help_name_set == coordinate_set)
				std::cout << coordinate << "     Redefining the head object failed" << std::endl;
			else if (coordinate[0] == '/' && coordinate[1] == '/') {
				cl_base* help_pointer = this->find_object_by_coordinate(coordinate);
				if (help_pointer != nullptr && help_pointer->find_object_from_current(current_object->get_name()) == nullptr) {
					current_object->Change_Head(help_pointer);
					std::cout << "New head object: " << help_pointer->get_name() << std::endl;
				}
				else if (help_pointer == nullptr)
					std::cout << coordinate << "     Head object is not found" << std::endl;
				else if (help_pointer != nullptr && help_pointer->find_object_from_current(current_object->get_name()) != nullptr) 
					std::cout << coordinate << "     Dubbing the names of subordinate objects" << std::endl;
			}
			else if (coordinate[0] == '/' && coordinate.find("/", 1) == -1) {
				cl_base* help_pointer = this->find_object_by_coordinate(coordinate);
				if (help_pointer != nullptr && help_pointer->find_object_from_current(current_object->get_name()) == nullptr) {
					current_object->Change_Head(help_pointer);
					std::cout << "New head object: " << help_pointer->get_name() << std::endl;
				}
				else if (help_pointer == nullptr)
					std::cout << coordinate << "     Head object is not found" << std::endl;
				else if (help_pointer != nullptr && help_pointer->find_object_from_current(current_object->get_name()) != nullptr)
					std::cout << coordinate << "     Dubbing the names of subordinate objects" << std::endl;
			}
			else if (coordinate[0] == '/' && coordinate.find("/", 1) != -1) {
				cl_base* help_pointer = this->find_object_by_coordinate(coordinate);
				if (help_pointer != nullptr && help_pointer->find_object_from_current(current_object->get_name()) == nullptr) {
					current_object->Change_Head(help_pointer);
					std::cout << "New head object: " << help_pointer->get_name() << std::endl;
				}
				else if (help_pointer == nullptr)
					std::cout << coordinate << "     Head object is not found" << std::endl;
				else if (help_pointer != nullptr && help_pointer->find_object_from_current(current_object->get_name()) != nullptr)
					std::cout << coordinate << "     Dubbing the names of subordinate objects" << std::endl;
			} 
			/*if (coordinate.find("/") == 0 && coordinate.find(current_object->get_name()) == -1) {
				if (this->find_object_by_coordinate(coordinate) != nullptr) {
					cl_base* pointer = this->find_object_by_coordinate(coordinate);
					if (pointer->get_sub_object(current_object->get_name()) != nullptr)
						std::cout << coordinate << "     Dubbing the names of subordinate objects" << std::endl;
					else if (!current_object->Change_Head(pointer))
						std::cout << coordinate << "     Redefining the head object failed" << std::endl;
					else
						std::cout << "New head object: " << pointer->get_name() << std::endl;
				}
				else
					std::cout << coordinate << "     Head object is not found" << std::endl;
			}
			else
				std::cout << coordinate << "     Redefining the head object failed" << std::endl; */
		/*}
		if (command == "DELETE") {
			if (current_object->get_sub_object(coordinate) != nullptr) {
				current_object->Delete_Object(coordinate);
				cl_base* build_answer = current_object;
				std::string answer = "/" + coordinate;
				while (build_answer->get_head() != nullptr) {
					answer.insert(0, "/" + build_answer->get_name());
					build_answer = build_answer->get_head();
				}
				std::cout << "The object " << answer << " has been deleted" << std::endl;
			}
		}
		if (command == "END") {
			std::cout << "Current object hierarchy tree" << std::endl;
			break;
		}
	}
	this->Print_Tree(); //Запуск метода вывода дерева иеррархии на экран 
	return 0;
}

//----------------------------------------------------------КВ-2--------------------------------------------------------------//

void cl_application::build_tree_objects_1() {
	std::string s_head_name, s_sub_name; //Объявление вспомогательных переменных типа string
	cl_base* p_head = this; //Создание главного указателя, указывающего на данный объект
	cl_base* p_sub = nullptr; //Инициализация указателя подчиненных объектов
	std::cin >> s_head_name; //Инициализация названия главного объекта
	set_name(s_head_name); //Установление имени на главный объект
	int number, state; //Инициализация номера класса объекта и уровня готовности
	while (true) { //Бесконечный цикл
		std::cin >> s_head_name; //Ввод имени головного объекта
		if (s_head_name == "endtree") break; //Проверка на окончание бесконечного цикла
		std::cin >> s_sub_name >> number; //Ввод имени подчиненного объекта и номера класса объекта
		p_head = find_object_from_root(s_head_name); //Нахождение указателя головного элемента в дереве иеррархии
		if (find_object_from_root(s_sub_name) == nullptr) { //Проверка на уникальность имени подчиненного объекта
			switch (number) { //Определение подчиненного объекта в соответствующий класс
			case 2:
				p_sub = new cl_1(p_head, s_sub_name);
				break;
			case 3:
				p_sub = new cl_2(p_head, s_sub_name);
				break;
			case 4:
				p_sub = new cl_3(p_head, s_sub_name);
				break;
			case 5:
				p_sub = new cl_4(p_head, s_sub_name);
				break;
			case 6:
				p_sub = new cl_5(p_head, s_sub_name);
				break;
			default: break;
			}
		}
	}
	while (std::cin >> s_head_name) { //Цикл пока вводится имя объекта
		std::cin >> state; //Ввод готовности объекта
		p_head = find_object_from_root(s_head_name); //Нахождение указателя головного элемента в дереве иеррархии
		p_head->Set_Readiness(state); //Вызов метода установки готовности объекта
	}
}

int cl_application::exec_app_1() {
	std::cout << "Object tree" << std::endl; //Вывод на экран надписи из условия задачи
	this->Print_Tree(); //Запуск метода вывода дерева иеррархии на экран 
	std::cout << "The tree of objects and their readiness" << std::endl; //Вывод на экран надписи из условия задачи
	this->Print_Readiness(); //Запуск метода вывода дерева иеррархии и готовности каждого объекта на экран 
	return 0;
}*/

//----------------------------------------------------------КВ-1--------------------------------------------------------------//

/*void cl_application::build_tree_objects() {
	std::string s_head_name, s_sub_name; //Объявление вспомогательных переменных типа string
	cl_base* p_head = this; //Создание главного указателя, указывающего на данный объект
	cl_base* p_sub = nullptr; //Инициализация указателя подчиненных объектов
	std::cin >> s_head_name; //Инициализация названия главного объекта
	set_name(s_head_name); //Установление имени на главный объект
	while (true) { //Бесконечный цикл
		std::cin >> s_head_name >> s_sub_name; //Ввод с клавиатуры имен для главного объекта и для подчиненных
		if (s_head_name == s_sub_name) { //Проверки на совпадение имен подчиненных и главных обектов
			break; //Выход из бесконечного цила, если имена совпали
		}
		if (p_sub != nullptr && s_head_name == p_sub->get_name()) { //Условие для поиска нового главного объекта среди подчиненных
			p_head = p_sub; //Присваивание главному объекту подчиненного, так как он будет главным для прочих объектов
		}
		if (p_head->get_sub_object(s_sub_name) == nullptr && s_head_name == p_head->get_name()) { //Проверка уникальности имени нового объекта и правильности его расположения на дереве
			p_sub = new cl_1(p_head, s_sub_name); //Создаем новый подчиненный объект
		}
	}
}

int cl_application::exec_app() {
	std::cout << get_name(); //Вывод имени главного элемента
	print_tree(); //Постройка дерева иерархии
	return 0;
}*/