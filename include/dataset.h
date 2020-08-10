#ifndef DATASET_H
#define DATASET_H
#include "../include/input.h"//Include the parser functions and structs
#include <string>
#include <set>
#include <vector>
#include <ctime>
#include <iostream>
#include <sstream>

#define MAX_SET_SIZE 100

enum TYPE {PRIVATE, SHARED};
enum SYNC {OFF, ON};

//Each wildcard has its own dataset
//Two options to add items: manual and moodle generated
struct Dataset{
    public:
    int dataset_size();
    std::string get_random_number();//Instantiate wildcard with this value
    void add_number(const std::string& add);//Push an item to the data_set
    void print_dataset();
    void vector_to_dataset(std::vector<std::string>& data, Dataset& dataset);
    void moodle_set_generation(int min, int max);
    std::string get_wildcard();

    std::string wildcard;
    bool type;//The type of data set: private or shared
    bool syncronization;
    std::vector<std::string> datasets;
};

//std::ostream& operator<<(std::ostream& out, const Dataset& dataset);
#endif //DATASET_H