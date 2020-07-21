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
        int select_question_type();
    private:
        int number_of_questions;
};
#endif //MENU_H