#ifndef PREGUNTA_ESTRUCTURADA_H
#define PREGUNTA_ESTRUCTURADA_H
#include <iostream>
#include <vector>
#include <queue> 

struct Question {
    std::string question_name;
    std::string question_text;
    std::vector <std::string> variables;
    int default_score;
    std::string general_feedback;
};
struct Answer {
    public:
        std::vector <std::string> answer_formula;
        float tolerance;
        int tolerance_type;
        int number_of_decimals; //Should implement significative digits
        std::string specific_feedback;
};
struct Units {
    std::string unit; //Ej. Meters, centimeters, feets, etc.
    float unit_penalization;
};
struct Multiple_Attempts {
    float attempt_penalization;
    std::queue <std::string> clue; //Display everytime that fails an attempt
};
struct Landmarks_Group{
    std::vector<std::string> landmarks;
};
#endif