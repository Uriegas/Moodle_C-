#ifndef EXAM_H
#define EXAM_H
#include "../include/question.h"
#include "../include/dataset.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

enum SELECT_OPTION { GET_OUT, CREATE_QUESTION, LOAD_QUESTION, LOAD_DATASET, PREVIEW_QUESTION, APPLY_EXAM, CURRENT_CONFIG };
//Each time that we find a new wildcard in a question we create a new dataset
class Exam {
    public:
        Exam():calification(0){};
        int show_exam();
        Question create_new_question();
        void create_dataset(std::string wildcard, int min = 0, int max = 100);
        float apply_question(int& no_que);
        void add_dataset(Dataset& dataset);
        void load_question(std::string file);
        void load_dataset(std::string& file);
        void print_question_list();
        void apply_exam();
        void print_datasets();
        std::vector<Question> questions;
    private:
        std::vector<Dataset> datasets;
        float calification;
};
std::ostream& operator<<(std::ostream& out, std::vector<Question>& questions);
#endif //EXAM_H