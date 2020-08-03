#ifndef PREGUNTA_ESTRUCTURADA_H
#define PREGUNTA_ESTRUCTURADA_H
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include "../include/parser.h"//Include the parser functions and structs

enum TOLERANCE{RELATIVE = 1, NOMINAL, GEOMETRIC};
enum DECIMAL_OR_SIGNIFICATIVE{DECIMAL = true, SIGNIFICATIVE = false};
enum UNIT_TREATMENT{LEFT, RIGHT, NO_UNITS, OPTIONAL_UNITS, OBLIGATORY_UNITS, STRING_INPUT, MULTIPLE_OPTION};
enum QUESTION_TYPE{CALCULATED, SIMPLE, MULTIPLE};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMMENTS SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Functions to modify the elements of this structures are defined in input.cpp file.
//And their implementation is on every type of question .cpp files

struct Answer {
    public:
        Answer()
            :calification(100), tolerance(0), tolerance_type(RELATIVE), number_of_decimals(2), decimal_or_significative(DECIMAL){}
        void read_formula();
        void set_tolerance();
        void set_decimal();
        void set_specific_feedback();
        std::queue <tokens> answer_formula;
        size_t calification;//Specified in percentage 0-100%
        float tolerance;
        unsigned int tolerance_type;
        unsigned int number_of_decimals; //Should implement significative digits
        bool decimal_or_significative;//Defualt to DECIMAL
        std::string specific_feedback;
};

void Answer::read_formula(){
    std::string formula;
err:std::getline(std::cin, formula);
    vector_error tokenized_string;//Save tokenized string with error

    tokenized_string = lexer(formula);
    if(tokenized_string.error != NOERROR){//If there is an error in the string print it
        return_error(tokenized_string.error);
        goto err;
    }
    else//If there is no error parse the string and save it to Answer object
        answer_formula = parser(tokenized_string.vector);
}

void Answer::set_tolerance(){
    size_t tole = 0;
    float type;

    std::cin >> tole;
    while(tole <= 0 || tole > 3){
        std::cout << "Ingrese un valor valido \n";
        std::cin >> tole;
    }

    std::cin >> type;
    while(type > 100 || type < 0){
        std::cout << "Ingrese un valor valido \n"
                  << "La tolerancia debe estar entre 0 a 100 \n";
        std::cin >> type;
    }
    tolerance = type;
}
void Answer::set_decimal(){
    int decimal;
    std::string choose;
ag: std::cout << "Ingrese la cantidad de decimales o cifras significativas a mostrar" << "\n";
    std::cin >> decimal;
    if(decimal < 0){
        std::cout << "Ingrese un valor valido" << "\n";
        goto ag;
    }
    else
        number_of_decimals = decimal;
dec:std::cout << "Decimales o cifras significativas?" << "\n";
    std::cout << "0." << "\t" << "Decimal" << "\n"
            << ">1." << "\t" << "Cifras Significativas" << std::endl;
    std::cin.ignore();
    std::getline(std::cin, choose);
    if(choose == "0")
        tolerance_type = DECIMAL;
    else if(choose == "1")
        tolerance_type = SIGNIFICATIVE;
    else{
        std::cout << "Ingrese un valor valido" << "\n";
        goto dec;
    }
}

void Answer::set_specific_feedback(){
    specific_feedback = feedback_function("retroalimentacion especifica");
}

class Question
{//Comments specifies the sections found in Moodle
private:
    //Background variables IMPORTANT
    std::vector<std::string> wildcards;
    std::vector<std::set<float>> datasets;//A vector composed of sets of float values;
    int question_type;
    //*******First Page*******
    //General
    int category;//Not implemented
    std::string question_name;
    std::string question_text;
    int default_score;//Number of points for this question
    std::string general_feedback;
    //Answers
    std::vector<Answer> answers;//A data structure to save the answers configuration
    //Units treatment
    size_t unit_treatment;
    float unit_penalization;
    size_t unit_input;
    bool unit_side;
    //Units
    std::string unit; //Ej. Meters, centimeters, feets, etc.
    float unit_penalization;
    //Multiple Attempts
    float wrong_answer_penalization;//If incorrect answered, have another attempt but less calification
    std::queue <std::string> clues; //Display everytime that fails an attempt
    //Landmarks
    std::vector<std::string> landmarks;

public:
    Question(int question_type)
        :category(1), default_score(1), unit_treatment(NO_UNITS), question_type(question_type), created("\n"){}
    //*******First Page*******
    void read_question_name();
    void read_question_text();
    void set_default_score(int score);
    void set_general_feedback();
    void set_answer(Answer answer);
    std::queue <tokens> read_formula(std::string string);
    void print_question();
    std::ofstream generate_questions();//Not implemented
    void print_answer();
    void set_tolerance(Answer& answer); //Not implemented 
    std::string feedback_function(const std::string& feedback_type);
    std::vector<std::string> string_variable_analizer(const std::string base);
    std::string current_date();
    std::vector<std::string> split_string(std::string str, char dl);
    float evaluate(std::queue<tokens> string, float lower, float upper);
    void time();
    //Created/Modified
    std::string created;
    std::string last_modified;
};

void Question::read_question_name(){
    std::getline(std::cin, question_name);
}

void Question::read_question_text(){
    //Save the question text to a string
    std::getline(std::cin, question_text);
    //Get the variables in question text
    wildcards = string_variable_analizer(question_text);
}

void Question::set_default_score(int score){
    default_score = score;
}

void Question::set_answer(Answer answer){
    answers.push_back(answer);
}
void Question::set_general_feedback(){
    general_feedback = feedback_function("retroalimentacion general");
}
void Question::time(){
    if(created == "\n")
        created = current_date();
    last_modified = current_date();
}
#endif