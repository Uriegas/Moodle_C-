#include "../include/menu.h"
#include "../include/question.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMMENTS SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Note: Implement an exit option later below line 14


//First user interface
//Returns 2 if it edits a question
//Returns 1 if it adds a new question
//Returns 0 if it wants to exit
int Menu::show_menu(){
    int agregar_editar;
    std::cout << "\t" << "MOODLE" << "\t" << "\n"
            << "Interfaz para crear un examen" << "\n"
            << "Este examen tiene " << number_of_questions << " pregutas" << std::endl; 
agr:std::cout << "Desea agregar o editar preguntas?" << "\n"
            << "(Ingrese el numero)" << "\n"
            << "0." << "\t" << "Salir de MOODLE" << "\n"
            << "1." << "\t" << "Agregar" << "\n"
            << "2." << "\t" << "Editar" << std::endl;
    std::cin >> agregar_editar;

    if(agregar_editar == 0){
        return 0;
    }
    else if(agregar_editar == 1){
        return 1;//Call function select_question_type in main.cpp
    }
    else if(agregar_editar == 2){
        if(number_of_questions == 0){
            std::cout << "ERROR: No puede editar preguntas, ya que no hay" << std::endl;
            goto agr;
        }
        else{
            //std::cout << "Que pregunta desea editar? " << std::endl;
            return 2;
        }
    }
    else{
        std::cout << "ERROR: Ingrese un valor valido" << std::endl;
        goto agr;
    }
}

//Function to select a question type
//Has a counter that increments each time that is called
//For use in the examen later
Question Menu::create_new_question(){
    //Instatiate classes about the question elemnts
    Question question(CALCULATED);
    int score;
    int selected_question;
que:std::cout << "Pueden ingresar 3 tipos de preguntas" << "\n"
            << "1." << "\t" << "Calculada Simple" << "\n"
            << "2." << "\t" << "Calculada Normal" << "\n"
            << "3." << "\t" << "Calculada Multiple" << "\n"
            << "\n" << "Que tipo de pregunta desea realizar?" << "\n"
            << "(Ingrese el numero)" << std::endl;
    std::cin >> selected_question;
    if (selected_question > 3 || selected_question < 1){
        std::cout << "ERROR: Ingrese un numero de pregunta valido" <<std::endl;
        goto que;
    }
    else{
        number_of_questions++;
        return selected_question;
    }
    if(selected_question == SIMPLE){

    //<<<<<<<<<< HERE is all the process of user interface (input from teacher) >>>>>>>>>>>>>>>
    //<<<<<<<<<< Question Section >>>>>>>>>>>>>>>
    std::cout << "Ingrese el nombre de la pregunta" << "\n";
    std::cin.ignore();
    question.read_question_name();
    std::cout << "Ingrese el texto de la pregunta" << "\n";
    question.read_question_text();
    std::cout << "Ingrese la puntuacion por defectuo de la pregunta" << "\n"
                << "(Puntos de la pregunta) Comunmente este valor es de 1" << "\n";
    std::cin >> score;
    question.set_default_score(score);
    question.set_general_feedback();

    //<<<<<<<<<< Answer Section >>>>>>>>>>>>>>>
    Answer answer;
    //Read answer input
    std::cout << "Ingrese la formula de la respuesta correcta" << "\n";
    //read_formula returns a postfix notation queue tokenized
    answer.read_formula();
    std::cout << "Ingrese la tolerancia y el tipo de tolerancia" << "\n"
                << "Tipos de tolerancia:" << "\n"
                << "1." << "\t" << "Relativa" << "\n"
                << "2." << "\t" << "Nominal" << "\n"
                << "3." << "\t" << "Geometrica" << "\n";
    answer.set_tolerance();
    answer.set_decimal();
    answer.set_specific_feedback();
    question.set_answer(answer);

    //<<<<<<<<<< Unit Section >>>>>>>>>>>>>>>
    question.set_units();
    //<<<<<<<<<< Multiple Attempts Section >>>>>>>>>>>>>>>
    //This section is not included in the simple question format

    //<<<<<<<<<< Landmark Section >>>>>>>>>>>>>>>
    question.set_landmarks();

    //<<<<<<<<<< Created/Last Change Section >>>>>>>>>>>>>>>
    question.time();
    std::cout << "Pregunta creada en " << question.created << "\n"
              << "Pregunta modifica en " << question.last_modified << "\n";
    }
    else if(selected_question == CALCULATED){}
    else if(selected_question == MULTIPLE){}
    else{
        std::cout << "ERROR: Ingrese un numero de pregunta valido" <<std::endl;
        goto que;
    }
    return question;
}