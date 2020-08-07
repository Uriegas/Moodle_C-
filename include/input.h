#ifndef INPUT_H
#define INPUT_H
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <math.h>
#include <ctime>
#include <algorithm>
#include <sstream>

void deletespace(std::string &str);
std::vector<std::string> string_variable_analizer(const std::string base);
void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
void replace_variables_in_string(std::string &formula);
std::string read_question();
std::string current_date();
std::string feedback_function(const std::string& feedback_type);
std::string feedback_function(const std::string& feedback_type, char& error);
std::vector<std::string> split_string(std::string str, char dl);
#endif //INPUT_H