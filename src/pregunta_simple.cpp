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
    std::vector<std::string> variables;
    variables = simple_input.string_variable_analizer(question.question_text);
    question.variables = variables;
}