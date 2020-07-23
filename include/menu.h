#ifndef MENU_H
#define MENU_H
#include <iostream>
//#include <string>
//#include <vector>
//#include <bits/stdc++.h> 

class Menu {
    public:
        Menu():number_of_questions(0){};
        int show_menu();
        int create_new_question();
    private:
        int number_of_questions; //Increments each time that a new question is created 
};
#endif //MENU_H