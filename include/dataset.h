#ifndef DATASET_H
#define DATASET_H
#include <string>
#include <set>
#include <vector>

enum TYPE {PRIVATE, SHARED};
enum SYNC {OFF, ON};

class wildcard{
    public:
    std::string name;
    int frequency;
    std::vector<int> used_in_question;//Save in which questions the wildcard is used
    float value;
};

class Dataset{
    bool type;//The type of data set
    bool syncronization;
    std::set<wildcard> dataset;
};
#endif //DATASET_H