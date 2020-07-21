#include "../include/menu.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMMENTS SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Note: Implement an exit option later below line 14

//First user interface
int Menu::show_menu(){
    int agregar_editar;
    std::cout << "\t" << "MOODLE" << "\t" << "\n"
            << "Interfaz para crear un examen" << "\n"
            << "Este examen tiene " << number_of_questions << " pregutas" << std::endl; 
agr:std::cout << "Desea agregar o editar preguntas?" << "\n"
            << "1." << "\t" << "Agregar"
            << "2." << "\t" << "Editar" << std::endl;
    std::cin >> agregar_editar;

    if(agregar_editar == 1){
        return 1;//Call function select_question_type in main.cpp
    }
    else if(agregar_editar == 1){
        if(number_of_questions == 0){
            std::cout << "ERROR: No puede editar preguntas, ya que no hay" << std::endl;
            goto agr;
        }
        std::cout << "Que pregunta desea editar? " << std::endl;
    }
    else{
        std::cout << "ERROR: Ingrese un valor valido" << std::endl;
        goto agr;
    }
}

//Function to select a question type
//Has a counter that increments each time that is called
//For use in the examen later
int Menu::select_question_type(){
    int selected_question;
    std::cout << "Pueden ingresar 3 tipos de preguntas" << "\n"
            << "1." << "\t" << "Calculada Simple" << "\n"
            << "2." << "\t" << "Calculada Normal" << "\n"
            << "3." << "\t" << "Calculada Multiple" << "\n"
            << "Que tipo de pregunta desea realizar?" << "\n"
            << "(Ingrese el numero)" << std::endl;
    std::cin >> selected_question;
    number_of_questions++;
    
    if (selected_question > 3 || selected_question < 1){
        std::cout << "ERROR: Ingrese un numero de pregunta valido" <<std::endl;
        return 0;
    }
    else{
        return selected_question;
    }
}