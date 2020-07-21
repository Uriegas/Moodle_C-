#include "../include/input.h"
#include "../include/menu.h"
#include "../include/pregunta_calculada.h"
#include "../include/pregunta_multiple.h"
#include "../include/pregunta_simple.h"
using namespace std;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMMENTS SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Author: Jesus Eduardo Uriegas Ibarra
//Moodle Replica in C++

int main() {
    Menu menu;
    Input teacher;
    menu.show_menu();
    int selected_question = menu.select_question_type();

    switch (selected_question)
    {
    case 1:
        Pregunta_Simple simple;
        simple.create_simple_question();
        break;
    case 2:
        Pregunta_Calculada calculada;
        calculada.create_calculated_question();
        break;
    case 3:
        Pregunta_Multiple multiple;
        multiple.create_multiple_question();
        break;
    default:
        cout << "ERROR: Aun ahi un error en lo que selecciono como pregunta" << endl;
        break;
    }

    teacher.read_question();
    teacher.print_question();
    cout << "Ingrese la formula que se usara para calcular el resultado correcto: " << endl;
    teacher.read_formula();
    teacher.print_formula();
    return 0;
}