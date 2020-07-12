#ifndef INPUT_H
#define INPUT_H
#include <iostream>
#include <string>

class Input{
	public:
		Input()
			:question_number(0) {
				for(int i = 0; i < 10; i++){//Initialize ultimate characters to '\n'
					variables_names[i][9] = '\n';
				}
			};
		void set_question( int question_number );
		void set_answer();
		void read_question();
		void read_answer();
		void print_question();
	private:
		std::string question;
		std::string answer;
		int question_number;
		int variables_quantity = -1; // Initialized in -1 because it is incremented by 1 and used in an array
		char variables_names[10][10];
};

#endif //INPUT_H