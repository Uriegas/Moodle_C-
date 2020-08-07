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
    /*
    else{
        if(!exam.questions.empty()){
            std::cout<< "Current questions are:\n" << exam.questions << "Select one question\n";
            std::cin >> selected_question;
        }
        std::cout << "Este examen no tiene preguntas";
//        exam.modify_question();
    }*/
    std::cout<< "Pregunta No. " << exam.questions.size() << " guardada correctamente" << std::endl; //Ougth to implement number of question
    //After creating a question save it to a file.
    //Create class File, with methods for converting a class into a File in a database (.txt)
    //This part is not implemented yet
    exam.show_exam(); //Call again to continue add/modify/exit cycle
    return 0;
}