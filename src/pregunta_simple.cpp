#include "../include/pregunta_simple.h"
#include "../include/input.h"
#include <iostream>

void Pregunta_Simple::create_simple_question(){
    Input simple_input;
    std::cout << "Ingrese el nombre de la pregunta" << std::endl;
    simple_input.read_question();
}