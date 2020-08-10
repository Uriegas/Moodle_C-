#include "../include/dataset.h"

int Dataset::dataset_size(){
    return datasets.size();
}

std::string Dataset::get_random_number(){
    return datasets[rand()%datasets.size()];
}

void Dataset::add_number(const std::string& add){
    //If greater than max size pop an element
    while(datasets.size() >= MAX_SET_SIZE)
        datasets.pop_back();
    datasets.push_back(add);
}

void Dataset::print_dataset(){
    std::cout << "\nComodin:\t" << wildcard << '\n'
        << "Tipo:\t" << type << '\n'
        << "Sincronizacion:\t" << syncronization << '\n';
    std::cout << datasets.size() << '\n';
    for(int i = 1; i <= datasets.size(); i++){
        std::cout << datasets[i-1] << '\t';
        if( ((i%10) == 0) && (i <= MAX_SET_SIZE) )
            std::cout << '\n';
        if( i > MAX_SET_SIZE )
            datasets[i-1].clear();
    }
}

void Dataset::vector_to_dataset(std::vector<std::string>& data, Dataset& dataset){
    std::string number = "";
    std::stringstream(data[0]) >> dataset.wildcard;
    std::stringstream(data[1]) >> dataset.type;
    std::stringstream(data[2]) >> dataset.syncronization;
    std::vector<std::string> numbers = split_string(data[3], ' ');
    for(int i = 0; i < numbers.size(); i++){
        std::stringstream(numbers[i]) >> number;
        dataset.datasets.push_back(number);
    }

}

std::string Dataset::get_wildcard(){
    return wildcard;
}

//for use this function you need to seed the random generator
void Dataset::moodle_set_generation(int min, int max){
    while(datasets.size() <= MAX_SET_SIZE)
        datasets.push_back(std::to_string(min + rand() % ((max+1) - min)));
}
/*
std::ostream& operator<<(std::ostream& out, const Dataset& dataset){
    out << dataset.print_dataset();
    return out;
}*/