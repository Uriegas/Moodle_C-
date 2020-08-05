#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <iostream>
#include "../include/question.h"
#include "../include/dataset.h"

//Each time that we find a new wildcard in a question we create a new dataset
class Menu {
    public:
        Menu():number_of_questions(0){};
        int show_menu();
        Question create_new_question();
        void modify_question(const int& selected_question);//Return exit or failure
        void add_dataset(Dataset& dataset);
        std::vector<Question> questions;
    private:
        int number_of_questions; //Increments each time that a new question is created 
        std::vector<Dataset> datasets;
};

void Menu::modify_question(const int& selected_question){
    //Imprimir configuracion actual
    //Imprimir partes de la pregunta
    //Que desea modificar
    //Seleccionar con un switch lo que va a modificar llamando a la variable que modifica a eso
    //Para ello es necesario hacer una funcion de impresion, de configuarcin actual y de lo que se puede modificar, asi como la funcion del switch
    questions[selected_question];
}
//Print questions in a list
std::ostream& operator<<(std::ostream& out, std::vector<Question> questions){
    for(int i = 1; i <= questions.size(); i++)
        out<< i << ".\t" << questions[i-1].question_name << "\n";
}

#endif //MENU_H