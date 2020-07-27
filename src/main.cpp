#include "../include/input.h"
#include "../include/menu.h"
#include "../include/pregunta_calculada.h"
#include "../include/pregunta_multiple.h"
#include "../include/pregunta_simple.h"
using namespace std;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMMENTS SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Author: Jesus Eduardo Uriegas Ibarra
//Moodle Replica in C++

int main() {/*
    Menu menu;
    int selected_question;
    int selected_action = menu.show_menu();

    if(selected_action == 0)
        return 0;
    else if(selected_action == 1)
        selected_question = menu.create_new_question();
//    else
        //Call function to edit an already set question

    switch (selected_question){
        case 1:
        {
            Pregunta_Simple simple;
            simple.create_simple_question();
            break;
        }
        case 2:
        {
            Pregunta_Calculada calculada;
            calculada.create_calculated_question();
            break;
        }
        case 3:
        {
            Pregunta_Multiple multiple;
            multiple.create_multiple_question();
            break;
        }
        default:
        {
            cout << "ERROR: Aun ahi un error en lo que selecciono como pregunta" << endl;
            break;
        }
    }
    cout<< "Pregunta No. " << " guardada correctamente" << endl; //Ougth to implement number of question
    //After creating a question save it to a file.
    //Create class File, with methods for converting a class into a File in a database (.txt)
    //This part is not implemented yet
    menu.show_menu(); //Call again to continue add/modify/exit cycle
*/
    Input teacher;
    Question question;
    std::vector<std::string> formula;
    std::cout << "Ingrese el texto de la pregunta" << "\n";
    question.question_text = teacher.read_question();
    question.variables = teacher.string_variable_analizer(question.question_text);
    cout << "Ingrese la formula que se usara para calcular el resultado correcto: " << endl;
    formula = teacher.read_formula(question);
    teacher.print_formula(formula);
    return 0;
}