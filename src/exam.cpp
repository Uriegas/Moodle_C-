#include "../include/exam.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMMENTS SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Note: Implement an exit option later below line 14


//First user interface
//Returns 2 if it edits a question
//Returns 1 if it adds a new question
//Returns 0 if it wants to exit
int Exam::show_exam(){
    int agregar_editar;
    std::string buffer;
    std::cout << "\t" << "MOODLE" << "\t" << "\n"
            << "Interfaz para crear un examen" << "\n"
            << "Este examen tiene " << questions.size() << " pregutas" << std::endl; 
agr:std::cout << "Opciones:" << "\n"
            << "(Ingrese el numero)" << "\n"
            << "0." << "\t" << "Salir de MOODLE" << "\n"
            << "1." << "\t" << "Agregar pregunta" << "\n"
            << "2." << "\t" << "Subir pregunta desde archivo" << "\n"
            << "3." << "\t" << "Agregar pregunta" << "\n"
            << "4." << "\t" << "Agregar pregunta" << "\n";
    std::cin.clear();
    std::getline(std::cin, buffer);
    std::stringstream(buffer) >> agregar_editar;
    if(agregar_editar < 0 || agregar_editar > 4){
        std::cout << "ERROR: Ingrese un valor valido" << std::endl;
        goto agr;
    }
    return agregar_editar;
    /*
    if(agregar_editar == 0){
        return 0;
    }
    else if(agregar_editar == 1){
        return 1;//Call function select_question_type in main.cpp
    }
    else if(agregar_editar == 2){
        if(questions.empty()){
            std::cout << "ERROR: No puede editar preguntas, ya que no hay" << std::endl;
            goto agr;
        }
        else{
            //std::cout << "Que pregunta desea editar? " << std::endl;
            return 2;
        }
    }
    else{
        std::cout << "ERROR: Ingrese un valor valido" << std::endl;
        goto agr;
    }*/
}

//Function to select a question type
//Has a counter that increments each time that is called
//For use in the examen later
Question Exam::create_new_question(){
    //Instatiate classes about the question elemnts
    int score;
    int selected_question;
que:std::cout << "Pueden ingresar 3 tipos de preguntas" << "\n"
            << "1." << "\t" << "Calculada Simple" << "\n"
            << "2." << "\t" << "Calculada Normal" << "\n"
            << "3." << "\t" << "Calculada Multiple" << "\n"
            << "\n" << "Que tipo de pregunta desea realizar?" << "\n"
            << "(Ingrese el numero)" << std::endl;
    std::cin >> selected_question;
    if (selected_question > 3 || selected_question < 1){
        std::cout << "ERROR: Ingrese un numero de pregunta valido" <<std::endl;
        goto que;
    }
    else{
        Question question(selected_question);
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
        if(selected_question == SIMPLE){
            std::string another_question = "y";
            while(another_question == "y" || another_question == "1"){
                //Read answer input
                //read_formula returns a postfix notation queue tokenized
                std::cin.clear();
                std::cin.ignore();
                answer.read_formula();
                if(selected_question != MULTIPLE){
                    std::cout << "Ingrese el tipo de tolerancia y despues el valor de la tolerancia" << "\n"
                                << "Tipos de tolerancia:" << "\n"
                                << "1." << "\t" << "Relativa" << "\n"
                                << "2." << "\t" << "Nominal" << "\n"
                                << "3." << "\t" << "Geometrica" << "\n";
                    answer.set_tolerance();
                }
                answer.set_decimal();
                answer.set_specific_feedback();
                question.set_answer(answer);
                std::cout << "Desea agregar otra pregunta?\n"
                            <<"y = si\to\t1 = si\n"
                            <<"n = no\to\t0 = no\n";
                std::cin >> another_question;
            }
            //<<<<<<<<<< Unit Section >>>>>>>>>>>>>>>
            question.set_units();
            //<<<<<<<<<< Multiple Attempts Section >>>>>>>>>>>>>>>
            //This section is not included in the simple question format

            //<<<<<<<<<< Landmark Section >>>>>>>>>>>>>>>
            std::cin.clear();
            std::cin.ignore();
            question.set_landmarks();

            //<<<<<<<<<< Created/Last Change Section >>>>>>>>>>>>>>>
            question.time();
            std::cout << "Pregunta creada en " << question.created << "\n"
                    << "Pregunta modifica en " << question.last_modified << "\n";
        }

        else if(selected_question == CALCULATED){}
        else if(selected_question == MULTIPLE){}
        else{
            std::cout << "ERROR: Ingrese un numero de pregunta valido" <<std::endl;
            goto que;
        }
        return question;
    }
}
/*
void Exam::modify_question(const int& selected_question){
    //Imprimir configuracion actual
    //Imprimir partes de la pregunta
    //Que desea modificar
    //Seleccionar con un switch lo que va a modificar llamando a la variable que modifica a eso
    //Para ello es necesario hacer una funcion de impresion, de configuarcin actual y de lo que se puede modificar, asi como la funcion del switch
    questions[selected_question];
}
*/
void Exam::load_question(std::string file){
    std::ofstream myfile;
    myfile.open(file);
    myfile << "Writing to the file";
    myfile.close();
}
//Print questions in a list
std::ostream& operator<<(std::ostream& out, std::vector<Question>& questions){
    for(int i = 1; i <= questions.size(); i++)
        out << (i) << "\t" << questions[i-1].question_name << "\n";
    return out;
}