#ifndef INPUT_H
#define INPUT_H
#include "../include/pregunta_estructura.h"
#include "../include/parser.h"
#include <iostream>
#include <string>
#include <vector>
#include<iterator>
#include <bits/stdc++.h> 
#include <math.h>
#include <ctime>

class Input{
	public:
		Input(){};
		std::string read_question();
		void read_answer();
		std::queue <tokens> read_formula(std::string string);
		void print_question();
		std::ofstream generate_questions();//Not implemented
		void print_answer();
		void set_tolerance(Answer& answer); //Not implemented 
		std::string feedback_function(const std::string& feedback_type);
		std::vector<std::string> string_variable_analizer(const std::string base);
		std::string current_date();
		std::vector<std::string> split_string(std::string str, char dl);
		float evaluate(std::queue<tokens> string, float lower, float upper);

	private:
		std::string question; //String where the question is saved
		std::string answer; //String where the answer is saved
//		std::string formula;//String where the formula is saved
//		int question_number= 0;
		std::vector <std::string> variable_names;
};

#endif //INPUT_H