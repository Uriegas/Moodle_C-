#include "../include/pregunta_simple.h"
#include "../include/input.h"
#include <iostream>

void Pregunta_Simple::create_simple_question(){
    Input simple_input;
    Question question; 
    Answer answer;
    Units units;
    Multiple_Attempts multiple_attempts;
    Landmarks_Group landmarks;
    std::cout << "Ingrese el nombre de la pregunta" << "\n";
    std::cin.ignore();
    question.question_name = simple_input.read_question();
    std::cout << "Ingrese el texto de la pregunta" << "\n";
    question.question_text = simple_input.read_question();
//    std::vector<std::string> variables;
    question.variables = simple_input.string_variable_analizer(question.question_text);
//    question.variables = variables;
    std::cout << "Ingrese la puntuacion por defectuo de la pregunta" << "\n";
    std::cin >> question.default_score;
    char* retro = new char;
ret:std::cout << "Desea agregar retroalimentacion general" << "\n";
    std::cin >> *retro;
    if((*retro) == 'y'){
        std::cout << "Ingrese la reotroalimentacion general" << "\n";
        std::cin.ignore();
        std::getline(std::cin, question.general_feedback);
    }
    else if((*retro) == 'n'){
        question.general_feedback == "\n";
    }
    else{
        std::cout << "Ingrese un valor valido" << "\n";
        goto ret;
    }
    delete retro;

    //Read answer input
    std::cout << "Ingrese la formula de la respuesta correcta" << "\n";
    simple_input.read_formula();
}