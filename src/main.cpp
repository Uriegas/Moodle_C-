#include "../include/input.h"
using namespace std;

int main() {
    cout << "Hello World!" << endl;
    Input teacher;
    teacher.set_question(10);
    teacher.print_question();
    return 0;
}