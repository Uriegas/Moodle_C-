#ifndef PREGUNTA_ESTRUCTURADA_H
#define PREGUNTA_ESTRUCTURADA_H
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include "../include/parser.h"//Include the parser functions and structs

enum TOLERANCE{RELATIVE, NOMINAL, GEOMETRIC};
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
        std::queue <tokens> answer_formula;
        size_t calification;//Specified in percentage 0-100%
        float tolerance;
        unsigned int tolerance_type;
        unsigned int number_of_decimals; //Should implement significative digits
        bool decimal_or_significative;//Defualt to DECIMAL
        std::string specific_feedback;
};

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
    size_t unit_treatment = NO_UNITS;//Default
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
    //Created/Modified
    std::string created = "\n";
    std::string last_modified = "\n";

public:
    Question(int question_type)
        :category(1), default_score(1), unit_treatment(NO_UNITS), question_type(question_type){}
};

#endif