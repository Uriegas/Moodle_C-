#ifndef PREGUNTA_SIMPLE_H
#define PREGUNTA_SIMPLE_H
#include <iostream>
//#include <string>
//#include <vector>
//#include <bits/stdc++.h> 

class Pregunta_Simple {
    public:
        Pregunta_Simple(){};
        //Add functions interfaces
        void create_simple_question();
    private:
        std::string question_name, general_feedback, specific_feedback, units;
        std::vector <std::string> landmarks;
};
#endif //PREGUNTA_SIMPLE_H