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
				for(int i = 0; i < 10; i++){//Initialize ultimate characters to '\n'
					variables_names[i][9] = '\n';
				}
			};
//		void set_question( int question_number );
//		void set_answer();
		void read_question();
		void read_answer();
		void print_question();
		void print_answer(); //Not implemented yet
		int read_formula(std::string tokens);
		void deletespace(std::string &string, int const space);//delete seleceted space in a string

	private:
		std::string question; //String where the question is saved
		std::string answer; //String where the answer is saved
		std::string formula;
		int question_number;
		int variables_quantity = -1; // Initialized in -1 because it is incremented by 1 and used in an array
		char variables_names[10][10];
};

#endif //INPUT_H