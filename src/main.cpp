#include "../include/input.h"
using namespace std;

int main() {
    cout << "Hello World!" << endl;
    Input teacher;
    teacher.set_question(10);
    cout << "Ingrese la pregunta calculada: " << endl;
    teacher.read_question();
    teacher.print_question();
    return 0;
}