#ifndef INPUT_H
#define INPUT_H
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h> 

class Input{
	public:
		Input()
			:question_number(0) {
//				for(int i = 0; i < 10; i++){//Initialize ultimate characters to '\n'
//					variables_names[i][9] = '\n';
//				}
			};
//		void set_question( int question_number );
//		void set_answer();
		void read_question();
		void read_answer();
		void print_question();
		void print_answer(); //Not implemented yet
		int read_formula();
		void print_formula();
		std::ofstream generate_questions();

	private:
		std::string question; //String where the question is saved
		std::string answer; //String where the answer is saved
		std::string formula;//String where the formula is saved
		int question_number = 0;
		std::vector <std::string> variable_names;
};

#endif //INPUT_H