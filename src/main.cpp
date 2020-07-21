#include "../include/input.h"
#include "../include/menu.h"
using namespace std;

int main() {
    Menu menu;
    Input teacher;
    int selected_question = menu.show_menu();
    teacher.read_question();
    teacher.print_question();
    cout << "Ingrese la formula que se usara para calcular el resultado correcto: " << endl;
    teacher.read_formula();
    teacher.print_formula();
    return 0;
}/*
int main(){
    string hola = {"hola como estan"};
    cout << hola << endl;
    Input input;
    input.deletespace(hola, 4);
    cout << hola << endl;
}*/