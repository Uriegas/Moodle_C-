#ifndef PREGUNTA_SIMPLE_H
#define PREGUNTA_SIMPLE_H
#include <iostream>
//#include <string>
#include <vector>
#include <queue> 
//#include <bits/stdc++.h> 

class Pregunta_Simple {
    public:
        Pregunta_Simple(){};
        //Add functions interfaces
        void create_simple_question();
    private:
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
};
    struct Question {
        std::string question_name;
        std::string question_text;
        std::vector <std::string> variables;
        int default_score;
        std::string general_feedback;
    };
#endif //PREGUNTA_SIMPLE_H