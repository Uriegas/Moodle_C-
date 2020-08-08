#include "../include/exam.h"
#include "../include/question.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMMENTS SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Author: Jesus Eduardo Uriegas Ibarra
//Moodle Replica in C++

int main() {
    Exam exam;
    int selected_action;

    while(true){
        selected_action = exam.show_exam();

        switch (selected_action){
        case GET_OUT:
            return 0;
            break;
        case CREATE_QUESTION:
            exam.questions.push_back(exam.create_new_question());
            break;
        case LOAD_QUESTION:{
            std::string&& file = " ";
            std::cout << "Ingrese el nombre del archivo\n";
            std::cin.clear();
            std::getline(std::cin, file);
            exam.load_question(file);
            break;
        }
        case PREVIEW_QUESTION:
            exam.print_question_list();
            std::string&& buf = " ";
            int preview_question;
            std::cout << "Ingrese el número de la pregunta que desea previsualizar\n>";
            std::cin.clear();
            std::getline(std::cin, buf);
            std::stringstream(buf) >> preview_question;
            if( !(preview_question > exam.questions.size() || preview_question < 0) ){
                std::cout << "Previsualizando pregunta no. " << preview_question << '\n';
                exam.questions[preview_question-1].apply_question();//Apply selected question
            }
            else
                std::cout << "Esta pregunta no existe aun\nChao\n";
            break;
        case APPLY_EXAM:
            return APPLY_EXAM;
            break;
        case CURRENT_CONFIG:
            std::cout << exam.questions;
            break;
        }
    }
}