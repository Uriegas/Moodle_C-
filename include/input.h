#ifndef INPUT_H
#define INPUT_H
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h> 

//Input Interface
class Input{
	public:
		Input(){};
		void read_question();
		void read_answer();
		void print_question();
		void print_answer();
		int read_formula();
		void print_formula();
		void set_tolerance(); //Not implemented 
		std::ofstream generate_questions();//Not implemented

	private:
		std::string question; //String where the question is saved
		std::string answer; //String where the answer is saved
		std::string formula;//String where the formula is saved
//		int question_number= 0;
		std::vector <std::string> variable_names;
};

#endif //INPUT_H