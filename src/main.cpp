#include "../include/exam.h"
#include "../include/question.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMMENTS SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Author: Jesus Eduardo Uriegas Ibarra
//Moodle Replica in C++

int main() {
    Exam exam;
    int selected_question;
    int selected_action = exam.show_exam();

    if(selected_action == 0)
        return 0;
    else if(selected_action == 1)
        exam.questions.push_back( exam.create_new_question() );
    else{
        std::cout<< "Current questions are:\n" << exam.questions << "Select one question\n";
        std::cin >> selected_question;
//        exam.modify_question();
    }
/*
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
    }*/
    std::cout<< "Pregunta No. " << selected_question << " guardada correctamente" << std::endl; //Ougth to implement number of question
    //After creating a question save it to a file.
    //Create class File, with methods for converting a class into a File in a database (.txt)
    //This part is not implemented yet
    exam.show_exam(); //Call again to continue add/modify/exit cycle
    /*
    Input teacher;
    Question question;
    std::queue<tokens> formula;
    std::cout << "Ingrese el texto de la pregunta" << "\n";
    question.question_text = teacher.read_question();
    question.variables = teacher.string_variable_analizer(question.question_text);
    cout << "Ingrese la formula que se usara para calcular el resultado correcto: " << endl;
    formula = teacher.read_formula(question.answer_formula);
    cout << formula << endl;
    */
    return 0;
}