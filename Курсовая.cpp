#include <stdlib.h>
#include <stdio.h>
#include "cl_application.h"
int main() {
	cl_application* ob_cl_application = new cl_application(nullptr); // Создание корневого объекта класса cl_application
	ob_cl_application->build_tree_objects_4();
	ob_cl_application->exec_app_4();
	
	//ob_cl_application->build_tree_objects_3();
	//ob_cl_application->setup_connection();
	//ob_cl_application->exec_app_3();
	//ob_cl_application->build_tree_objects_2(); // Конструирование системы, построение дерева объектов
	//ob_cl_application->exec_app_2();
	//ob_cl_application.exec_app(); // Запуск системы
	return(0);
}
