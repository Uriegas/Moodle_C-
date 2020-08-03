#ifndef QUESTION_H
#define QUESTION_H
#include "../include/parser.h"//Include the parser functions and structs
#include "../include/input.h"//Include the parser functions and structs
#include <iostream>
#include <vector>
#include <queue>
#include <set>

enum TOLERANCE{RELATIVE = 1, NOMINAL, GEOMETRIC};
enum DECIMAL_OR_SIGNIFICATIVE{DECIMAL = true, SIGNIFICATIVE = false};
enum UNIT_TREATMENT{LEFT, RIGHT, NO_UNITS=0, OPTIONAL_UNITS, OBLIGATORY_UNITS, STRING_INPUT, MULTIPLE_OPTION};
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
    size_t unit_treatment;//Are units settled?
    bool unit_side;//Are units on left or rigth side?
    std::string unit; //Ej. Meters, centimeters, feets, etc.
    float unit_penalization;//If bad unit input, then what percentage extract?
    //Multiple Attempts
    float attempt_penalization;//If incorrect answered, have another attempt but less calification
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
//    std::queue <tokens> read_formula(std::string string);
//    std::ofstream generate_questions();//Not implemented
//    void print_answer();
    void set_units();
//    void set_tolerance(Answer& answer); //Not implemented 
//    std::string feedback_function(const std::string& feedback_type);
//    std::vector<std::string> string_variable_analizer(const std::string base);
//    std::string current_date();
//    std::vector<std::string> split_string(std::string str, char dl);
//    float evaluate(std::queue<tokens> string, float lower, float upper);
    void set_multiple_attempts();
    void set_landmarks();
    //Created/Modified
    void time();
    //Public to print it
    std::string created;
    std::string last_modified;
};

#endif