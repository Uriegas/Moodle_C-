#ifndef INPUT_H
#define INPUT_H
#include "../include/parser.h"
#include "../include/question.h"
#include <iostream>
#include <string>
#include <vector>
#include<iterator>
#include <bits/stdc++.h> 
#include <math.h>
#include <ctime>


void deletespace(std::string &str);
std::vector<std::string> string_variable_analizer(const std::string base);
void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
void replace_variables_in_string(std::string &formula);
std::string read_question();
std::queue<tokens> read_formula(std::string string);
std::string current_date();
std::string feedback_function(const std::string& feedback_type);
std::string feedback_function(const std::string& feedback_type, char& error);
std::vector<std::string> split_string(std::string str, char dl);
#endif //INPUT_H