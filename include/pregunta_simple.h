#ifndef PREGUNTA_SIMPLE_H
#define PREGUNTA_SIMPLE_H
#include "../include/pregunta_estructura.h"
#include <iostream>
//#include <string>
#include <vector>
#include <queue> 
//#include <bits/stdc++.h> 

class Pregunta_Simple {
    public:
        Pregunta_Simple(){};
        ~Pregunta_Simple(){
            std::cout << "Destroying this simple question" << "/n";
        }
        //Add functions interfaces
        void create_simple_question();
};
#endif //PREGUNTA_SIMPLE_H