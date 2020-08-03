#include "../include/pregunta_simple.h"
#include "../include/input.h"
#include <iostream>

//****************CLASS FUNCTIONS********************
void Pregunta_Simple::create_simple_question(){
    //Instatiate classes about the question elemnts
    Question question(CALCULATED);
    int score;
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
    int select;
uni:std::cout << "Desea calificar unidades?" << "\n";
    std::cout << "0." << "\t" << "No, no emplear unidades" << "\n"
            << "1." << "\t" << "Si, OPCIONALES sin calicar" << "\n"
            << "2." << "\t" << "Si, las unidades se calificaran" << std::endl;
    std::cin.ignore();
    std::cin >> select;
    if(select == 0){
        units.unit = "\n";
        units.unit_penalization = 0;
    }
    else if(select == 1 || select == 2){
        std::cout << "Ingrese la unidad" << "\n";
        std::getline(std::cin, units.unit);
        if(select == 2){
            std::cout << "Ingrese la penalizacion" << "\n"
                        << "(Penalizacion sobre la respuesta)" << std::endl;
            std::cin >> units.unit_penalization;
        }
    }
    else{
        std::cout << "ERROR: Ingrese una opcion valida" << "\n";
        goto uni;
    }

    //<<<<<<<<<< Multiple Attempts Section >>>>>>>>>>>>>>>
    //This section is not included in the simple question format

    //<<<<<<<<<< Landmark Section >>>>>>>>>>>>>>>
    landmarks.landmarks[0] = simple_input.feedback_function("marcas");
    landmarks.landmarks = simple_input.split_string(landmarks.landmarks[0], ' ');

    //<<<<<<<<<< Created/Last Change Section >>>>>>>>>>>>>>>
    question.time();
    std::cout << "Pregunta creada en " << question.created << "\n"
              << "Pregunta modifica en " << question.last_modified << "\n";
}