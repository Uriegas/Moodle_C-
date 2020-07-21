#include "../include/menu.h"

int Menu::show_menu(){
    int selected_question;
    std::cout << "\t" << "MOODLE" << "\t" << "\n"
            << "Interfaz para crear un examen" <<"\n"
            << "Pueden ingresar 3 tipos de preguntas" << "\n"
            << "1." << "\t" << "Calculada Simple" << "\n"
            << "2." << "\t" << "Calculada Normal" << "\n"
            << "3." << "\t" << "Calculada Multiple" << "\n"
            << "Que tipo de pregunta desea realizar?" << "\n"
            << "(Ingrese el numero)" << std::endl;
    std::cin >> selected_question;

    if (selected_question > 3 || selected_question < 1){
        std::cout << "ERROR: Ingrese un numero de pregunta valido" <<std::endl;
        return 0;
    }
    else{
        return selected_question;
    }
}
