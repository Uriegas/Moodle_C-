#include "../include/input.h"
#include "../include/menu.h"
#include "../include/question.h"
using namespace std;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMMENTS SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Author: Jesus Eduardo Uriegas Ibarra
//Moodle Replica in C++

int main() {
    Menu menu;
    int selected_question;
    int selected_action = menu.show_menu();
    /*
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
    Input teacher;
    Question question;
    std::queue<tokens> formula;
    std::cout << "Ingrese el texto de la pregunta" << "\n";
    question.question_text = teacher.read_question();
    question.variables = teacher.string_variable_analizer(question.question_text);
    cout << "Ingrese la formula que se usara para calcular el resultado correcto: " << endl;
    formula = teacher.read_formula(question.answer_formula);
    cout << formula << endl;*/

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
    question.set_units();
    //<<<<<<<<<< Multiple Attempts Section >>>>>>>>>>>>>>>
    //This section is not included in the simple question format

    //<<<<<<<<<< Landmark Section >>>>>>>>>>>>>>>
    question.set_landmarks();

    //<<<<<<<<<< Created/Last Change Section >>>>>>>>>>>>>>>
    question.time();
    std::cout << "Pregunta creada en " << question.created << "\n"
              << "Pregunta modifica en " << question.last_modified << "\n";
    return 0;
}