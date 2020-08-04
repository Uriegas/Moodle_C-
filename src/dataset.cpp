#include "../include/dataset.h"

int Dataset::dataset_size(){
    return data_set.size();
}

float Dataset::get_random_number(){
    srand(time(NULL));
    return data_set[rand()%data_set.size()];
}

void Dataset::add_number(const float& add){
    //If greater than max size pop an element
    while(data_set.size() >= MAX_SET_SIZE)
        data_set.pop_back();
    data_set.push_back(add);
}