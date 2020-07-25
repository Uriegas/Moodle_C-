#include "../include/pregunta_simple.h"
#include "../include/input.h"
#include <iostream>

std::string feedback_function(const std::string& feedback_type){
    char* retro = new char;
    std::string feedback_return;
ret:std::cout << "Desea agregar " << feedback_type << "\n"
            << "y = si" << "\n"
            << "n = no" << "\n";
    std::cin >> *retro;
    if((*retro) == 'y'){
        std::cout << "Ingrese la " << feedback_type << "\n";
        std::cin.ignore();
        std::getline(std::cin, feedback_return);
    }
    else if((*retro) == 'n'){
        feedback_return = "\n";
    }
    else{
        std::cout << "Ingrese un valor valido" << "\n";
        goto ret;
    }
    delete retro;
    return feedback_return;
}

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

    question.general_feedback = feedback_function("retroalimentacion general");

    //Read answer input
    std::cout << "Ingrese la formula de la respuesta correcta" << "\n";
    //read_formula should return a vector<string>
    simple_input.read_formula();//Suppose that it returns a postfix notation
    simple_input.set_tolerance(answer);
    std::cout << "Ingrese la cantidad de decimales a mostrar" << "\n";
    std::cin >> answer.number_of_decimals;
dec:std::cout << "Decimales o cifras significativas?" << "\n";
    std::cout << "0." << "\t" << "Decimal" << "\n"
            << ">1." << "\t" << "Cifras Significativas" << std::endl;
    std::cin.ignore();
    std::cin >> answer.decimal_or_significative;
    answer.specific_feedback = feedback_function("retroalimentacion especifica");
}