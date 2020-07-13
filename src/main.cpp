#include "../include/input.h"
using namespace std;

int main() {
    cout << "Hello World!" << endl;
    Input teacher;
    cout << "\t" << "MOODLE" << "\t" << endl;
    cout << "Ingrese la pregunta calculada: " << endl;
    teacher.read_question();
    teacher.print_question();
    return 0;
}/*
int main(){
    string hola = {"hola como estan"};
    cout << hola << endl;
    Input input;
    input.deletespace(hola, 4);
    cout << hola << endl;
}*/