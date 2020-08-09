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
class Dataset{
    public:
    int dataset_size();
    float get_random_number();//Instantiate wildcard with this value
    void add_number(const float& add);//Push an item to the data_set
    void print_dataset();
    void vector_to_dataset(std::vector<std::string>& data, Dataset& dataset);

    private:
    std::string wildcard;
    bool type;//The type of data set: private or shared
    bool syncronization;
    std::vector<float> datasets;
};

//std::ostream& operator<<(std::ostream& out, const Dataset& dataset);
#endif //DATASET_H