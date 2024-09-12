#include "cl_base.h"
#include <string>
#include <iostream>
#include <queue>

std::string prefix_for_tree = ""; //Глоабльные переменные для корректного вывода построенного дерева иеррархии
std::string prefix_for_readiness = "";



cl_base::cl_base(cl_base* p_head, std::string s_name) {
	this->s_name = s_name; //Обработка переменных в конструкторе класса
	this->p_head_object = p_head;
	if (p_head_object != nullptr) { //Переопределение экземпляра класса по дереву иеррархии
		p_head_object->p_sub_objects.push_back(this);
	}
}
cl_base::~cl_base() {
	for (int i = 0; i < this->p_sub_objects.size(); ++i) {
		delete this->p_sub_objects[i]; //Удаление каждого элемента динамического массива ветви дерева
	}
}
bool cl_base::set_name(std::string s_new_name) {
	if (p_head_object != nullptr) {
		for (int i = 0; i < p_head_object->p_sub_objects.size(); ++i) {
			if (p_head_object->p_sub_objects[i]->get_name() == s_new_name) { //Обрабокта алгоритма нахождения экземпляра по имени
				return false; //Организация возвращаемого значения
			}
		}
	}
	this->s_name = s_new_name;
	return true; //Организация возвращаемого значения
}

std::string cl_base::get_name() {
	return this->s_name; //Полечение имени объекта
}

cl_base* cl_base::get_head() {
	return this->p_head_object; //Получение головного объекта
}

cl_base* cl_base::get_sub_object(std::string s_name) {
	for (int i = 0; i < p_sub_objects.size(); ++i) {
		if (p_sub_objects[i]->get_name() == s_name) { //Получение по имени объекта из ветви дерева иеррархии
			return p_sub_objects[i]; //Организация возвращаемого значения
		}
	}
	return nullptr; //Если такого имени в ветви дерева иеррархии нет, то возвращается пустой указатель
}

cl_base* cl_base::find_object_from_current(std::string s_name) {
	std::queue<cl_base*> q;
	cl_base* p_found = nullptr; //Организация вспомогательрных полей метода 
	q.push(this);
	while (!q.empty()) { //Обработка очереди по алгоритму обхода графа в ширину
		if (q.front()->get_name() == s_name) {
			if (p_found == nullptr) p_found = q.front(); //Метод нахождения элемента ветви
			else return nullptr; //Организация возвращаемого значения
		}
		for (auto p_sub_object : q.front()->p_sub_objects)
			q.push(p_sub_object); //Добавление новых элементы для дальнейшего осуществуления поиска
		q.pop();
	}
	return p_found; //Организация возвращаемого значения
}

cl_base* cl_base::find_object_from_root(std::string s_name) {
	cl_base* root = this;
	while (root->get_head() != nullptr)
		root = root->get_head(); //Поиск головного элемента в цикле
	return root->find_object_from_current(s_name); //Организация возвращаемого значения
}

void cl_base::Set_Readiness(int state) {
	this->readiness = state; //Установки готовности объекта
	if (state == 0) {
		for (auto p_sub_object : p_sub_objects)
			p_sub_object->Set_Readiness(0); //Установка готовности подчиненных объектов
	}
	else {
		cl_base* root = this;
		while (root->get_head() != nullptr) {
			root = root->get_head();
			if (root->readiness == 0) {
				this->readiness = 0; return;
			}
		}
	}
}

void cl_base::Print_Readiness() {
	std::string is_ready;
	if (this->readiness != 0) is_ready = " is ready";  //Организация вывода дерева и установленной динамически им готовности
	else is_ready = " is not ready";
	std::string child_prefix = "    ";
	std::string saved_prefix = prefix_for_readiness;
	std::cout << prefix_for_readiness << this->get_name() << is_ready << std::endl;
	prefix_for_readiness += child_prefix;
	for (auto p_sub_object : this->p_sub_objects) //Обработка вывода дерева иеррархии
		p_sub_object->Print_Readiness();
	prefix_for_readiness = saved_prefix;
}

void cl_base::Print_Tree() {
	std::string child_prefix = "    "; //Обработка вывода дерева иеррархии
	std::string saved_prefix = prefix_for_tree;
	std::cout << prefix_for_tree << this->get_name() << std::endl;
	prefix_for_tree += child_prefix;
	for (auto p_sub_object : this->p_sub_objects)
		p_sub_object->Print_Tree();
	prefix_for_tree = saved_prefix;
}


bool cl_base::Change_Head(cl_base* p_head) {
	if (this->get_head() == nullptr || p_head == nullptr) //Обработка алгоритма смены головного объекта у текущего
		return false; //Организация возвращаемого значения
	std::vector<cl_base*> help; //Создание вспомогательных экземпляров
	for (auto p_sub_object : this->p_sub_objects) {
		help.push_back(p_sub_object);
	}
	this->get_head()->Delete_Object(this->get_name()); //Обработка перемещения экземпляра по дереву иеррархии
	p_head->p_sub_objects.push_back(this);
	for (auto p_sub_object : help) {
		this->p_sub_objects.push_back(p_sub_object);
	}
	return true; //Организация возвращаемого значения
}

void cl_base::Delete_Object(std::string s_name) {
	for (int i = 0; i < this->p_sub_objects.size(); ++i) { //Обработка удаления элемента из дерева иеррархии
		if (this->p_sub_objects[i]->get_name() == s_name) {	//Нахождение элемента по имени
			for (int j = p_sub_objects[i]->p_sub_objects.size() - 1; j >= 0; --j) {
				p_sub_objects[i]->p_sub_objects.erase(p_sub_objects[i]->p_sub_objects.begin() + j); //Удаление подчиненных ему элементов
			}
			this->p_sub_objects.erase(this->p_sub_objects.begin() + i); //Удаление самого элемента
			return;
		}
	}
}


cl_base* cl_base::find_object_by_coordinate(std::string s_coordinate) {
	std::string s_name;
	int i_slash_2; //Создание вспомогательных полей метода
	cl_base* p_object = nullptr;
	if (s_coordinate == "") //Обработка данного типа координат 
		return nullptr;
	if (s_coordinate == "/") //Обработка данного типа координат
		return this->get_root();
	if (s_coordinate == ".") //Обработка данного типа координат
		return this;
	if (s_coordinate[0] == '/' && s_coordinate[1] == '/') {
		s_name = s_coordinate.substr(2); //Обработка данного типа координат
		return this->find_object_from_root(s_name);
	}
	if (s_coordinate[0] == '.') {
		s_name = s_coordinate.substr(1); //Обработка данного типа координат
		return this->find_object_from_current(s_name);
	}
	i_slash_2 = s_coordinate.find("/", 1);
	if (s_coordinate[0] == '/') {
		if (i_slash_2 != -1) { //Обработка данного типа координат
			s_name = s_coordinate.substr(1, i_slash_2 - 1);
			p_object = this->get_root()->get_sub_object(s_name);
			if (p_object != nullptr)
				return p_object->find_object_by_coordinate(s_coordinate.substr(i_slash_2 + 1));
			else
				return p_object;
		}
		else {
			s_name = s_coordinate.substr(1); //Обработка данного типа координат
			return this->get_root()->get_sub_object(s_name);
		}
	}
	else {
		if (i_slash_2 != -1) { //Обработка данного типа координат
			s_name = s_coordinate.substr(0, i_slash_2);
			p_object = this->get_sub_object(s_name);
			if (p_object != nullptr)
				return p_object->find_object_by_coordinate(s_coordinate.substr(i_slash_2 + 1));
			else
				return p_object;
		}
		else {
			s_name = s_coordinate; //Обработка данного типа координат
			return this->get_sub_object(s_name);
		}
	}
}


cl_base* cl_base::get_root() {
	cl_base* root = this;
	while (root->get_head() != nullptr) //Полечение головного объекта дерева иеррархии 
		root = root->get_head();
	return root; //Организация возвращения головного объекта дерева иеррархии
}

void cl_base::set_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler) {
	o_sh* p_value;
	for (int i = 0; i < connects.size(); ++i) // Цикл для исключения повторного установления связи
		if (connects[i]->p_signal == p_signal && connects[i]->p_target == p_target && connects[i]->p_handler == p_handler)
			return;

	p_value = new o_sh(); // создание объекта структуры для

	p_value->p_signal = p_signal;
	p_value->p_target = p_target; // хранения информации о новой связи
	p_value->p_handler = p_handler;

	connects.push_back(p_value); // добавление новой связи
}

void cl_base::delete_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler) {
	auto iterator = connects.begin();
	for (iterator; iterator != connects.end(); ++iterator)
		if ((*iterator)->p_signal == p_signal && (*iterator)->p_target == p_target && (*iterator)->p_handler == p_handler) {
			//
			delete (*iterator);
			//
			connects.erase(iterator); 
			return;
		}
}

void cl_base::emit_signal(TYPE_SIGNAL p_signal, std::string s_message) {
	if (this->readiness == 0) return;
	(this->*p_signal)(s_message); // вызов метода сигнала
	for (auto connection : connects) { // цикл по всем обработчикам
		if (connection->p_signal == p_signal) { // определение допустимого обработчика
			if (connection->p_target->readiness == 0) continue;
			cl_base* p_target = connection->p_target;
			TYPE_HANDLER p_handler = connection->p_handler;

			(p_target->*p_handler)(s_message); // вызов метода обработчика
		}
	}
}

std::string cl_base::Absolute_Way() {
	cl_base* build_answer = this;
	std::string answer; //Создание дополнительных полей класса
	while (build_answer->get_head() != nullptr) {
		answer.insert(0, "/" + build_answer->get_name()); //Обработка построение абсолютного пути до текущего объекта
		build_answer = build_answer->get_head();
	}
	if (answer.empty())
		return answer += "/";
	return answer; //Возвращение абсолютного пути
}

//----------------------------------------------------------КВ-5--------------------------------------------------------------//

void cl_base::turn_on_objects() {
	this->readiness = 10;
	for (auto p_sub_object : this->p_sub_objects) {
		p_sub_object->Set_Readiness(10);
		if (p_sub_object->p_sub_objects.size() != 0)
			p_sub_object->turn_on_objects();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////