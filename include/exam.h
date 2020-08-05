#ifndef EXAM_H
#define EXAM_H
#include "../include/question.h"
#include "../include/dataset.h"

//Each time that we find a new wildcard in a question we create a new dataset
class Exam;
class Exam {
    public:
        Exam():number_of_questions(0){};
        int show_exam();
        Question create_new_question();
        void modify_question(const int& selected_question);//Return exit or failure
        void add_dataset(Dataset& dataset);
        std::vector<Question> questions;
    private:
        int number_of_questions; //Increments each time that a new question is created 
        std::vector<Dataset> datasets;
};
std::ostream& operator<<(std::ostream& out, std::vector<Question>& questions);
#endif //EXAM_H