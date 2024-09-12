#ifndef __CL_BASE__H
#define __CL_BASE__H
#include <string>
#include <vector>
#include <map>

#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(&signal_f)
#define HANDLER_D(handler_f)(TYPE_HANDLER)(&handler_f)

class cl_base;

typedef void (cl_base::* TYPE_SIGNAL) (std::string& msg);
typedef void (cl_base::* TYPE_HANDLER) (std::string msg);

struct o_sh { // Структура задания одной связи
	TYPE_SIGNAL p_signal; // Указатель на метод сигнала
	cl_base* p_target; // Указатель на целевой объект
	TYPE_HANDLER p_handler; // Указатель на метод обработчика
};

class cl_base {


	std::string s_name; //Имя объекта
	cl_base* p_head_object; //Головной объект
	std::vector<cl_base*> p_sub_objects; //Подчиненные объекты

	std::vector<o_sh*> connects; //Хранение соединений между сигналом и обработчиком
	int readiness = 0; //Готовность объекта

public:

	//----------------------------------------------------------КВ-5--------------------------------------------------------------//
	
	std::map<int, std::vector<std::string>> cargoes;
	int tick = 0;

	int length_house, width_house;
	std::map<int, std::vector<std::string>> house_area;
	std::vector<int> left_house_part;
	std::vector<int> right_house_part;
	std::vector<int> center_house_part;

	std::string cargo_in_hook;

	void turn_on_objects();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	int object_class = 0;
	//
	std::string Absolute_Way();
	void set_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler);
	void delete_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler);
	void emit_signal(TYPE_SIGNAL p_signal, std::string s_message);

	cl_base* get_root(); //Поиск коренного объекта дерева

	//------------------------------------------------//
	//Метод переопределения головного объекта для 
	//текущего в дереве иерархии
	//------------------------------------------------//
	bool Change_Head(cl_base* p_head);

	//------------------------------------------------//
	//Метод удаления подчиненного объекта по наименованию
	//------------------------------------------------//
	void Delete_Object(std::string s_name);

	//------------------------------------------------//
	//Метод получения указателя на любой объект в составе
	//дерева иерархии объектов согласно пути (координаты)
	//------------------------------------------------//
	cl_base* find_object_by_coordinate(std::string s_coordinate);

	//------------------------------------------------//
	//Вспомогательный метод поиска объекта
	//с заданным именем, начиная с текущего объекта
	//------------------------------------------------//
	cl_base* find_object_from_current(std::string);

	//------------------------------------------//
	//Вспомогательный метод поиска объекта
	//с заданным именем, начиная с корня дерева
	//-----------------------------------------//
	cl_base* find_object_from_root(std::string s_name);
	void Print_Tree(); //Метод вывода иерархии объектов (дерева или ветки) от текущего объекта
	//-----------------------------------//
	//Метод вывода
	//дерева объектов с указанными
	//пометками (is_ready, is_not_ready)
	//-----------------------------------//
	void Print_Readiness();
	//----------------------------------//
	//Метод подсчета объектов с 
	//заданным именем в дереве объектов
	//---------------------------------//
	void Set_Readiness(int state = 0); //Метод установки готовности объекта 

	cl_base(cl_base* p_head, std::string s_name = "Base Object"); //Конструктор класса
	~cl_base(); //Деструктор класса
	bool set_name(std::string s_new_name); //Установки имени объекта
	std::string get_name(); //Получение имени объекта
	cl_base* get_head(); //Получение головного объекта
	cl_base* get_sub_object(std::string s_name); //Нахождение подчиненного объекта по имени
};

#endif