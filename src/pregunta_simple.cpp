#include "../include/pregunta_simple.h"
#include "../include/input.h"
#include <iostream>

//****************CLASS FUNCTIONS********************
void Pregunta_Simple::create_simple_question(){
    //Instatiate classes about the question elemnts
    Input simple_input;
    Question question; 
    Answer answer;
    Units units;
    Multiple_Attempts multiple_attempts;
    Landmarks_Group landmarks;
    Time time;
    //<<<<<<<<<< HERE is all the process of user interface (input from teacher) >>>>>>>>>>>>>>>
    //<<<<<<<<<< Question Section >>>>>>>>>>>>>>>
    std::cout << "Ingrese el nombre de la pregunta" << "\n";
    std::cin.ignore();
    question.question_name = simple_input.read_question();
    std::cout << "Ingrese el texto de la pregunta" << "\n";
    question.question_text = simple_input.read_question();
    question.variables = simple_input.string_variable_analizer(question.question_text);
    std::cout << "Ingrese la puntuacion por defectuo de la pregunta" << "\n";
    std::cin >> question.default_score;
    question.general_feedback = simple_input.feedback_function("retroalimentacion general");

    //<<<<<<<<<< Answer Section >>>>>>>>>>>>>>>
    //Read answer input
    std::cout << "Ingrese la formula de la respuesta correcta" << "\n";
    //read_formula should return a vector<string>
    answer.answer_formula = simple_input.read_formula();//Suppose that it returns a postfix notation
    simple_input.set_tolerance(answer);
    std::cout << "Ingrese la cantidad de decimales a mostrar" << "\n";
    std::cin >> answer.number_of_decimals;
dec:std::cout << "Decimales o cifras significativas?" << "\n";
    std::cout << "0." << "\t" << "Decimal" << "\n"
            << ">1." << "\t" << "Cifras Significativas" << std::endl;
    std::cin.ignore();
    std::cin >> answer.decimal_or_significative;
    answer.specific_feedback = simple_input.feedback_function("retroalimentacion especifica");

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
    if(time.created != "\n")
        time.last_modified = simple_input.current_date();
    else{
        time.created = simple_input.current_date();
        time.last_modified = simple_input.current_date();
    }
    std::cout<< "Pregunta creada en " << time.created << "\n";
    std::cout<< "Pregunta modifica en " << time.last_modified << "\n";
}