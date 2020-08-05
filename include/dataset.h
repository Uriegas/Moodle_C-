#ifndef DATASET_H
#define DATASET_H
#include <string>
#include <set>
#include <vector>
#include <ctime>

#define MAX_SET_SIZE 100

enum TYPE {PRIVATE, SHARED};
enum SYNC {OFF, ON};

//Each wildcard has its own dataset
//Two options to add items: manual and moodle generated
class Dataset{
    public:
    int dataset_size();
    float get_random_number();
    void add_number(const float& add);


    private:
    std::string wildcard;
    bool type;//The type of data set
    bool syncronization;
    std::vector<float> data_set;
};

#endif //DATASET_H