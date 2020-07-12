#ifndef INPUT_H
#define INPUT_H
#include <iostream>
class Input{
	public:
		Input()
			:question_number(0) {};
		void set_question( int question_number );
		void set_answer();
		void read_answer();
		void print_question();
	private:
//		char[] question;
		int question_number;
};

#endif //INPUT_H