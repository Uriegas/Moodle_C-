#include "../include/input.h"

void Input::set_question( int question ){
	question_number = question;
	}

void Input::read_question(){
	int flag = 0;
	int variables_length = 0;
	while(std::cin.peek() != '\n'){
		std::getline(std::cin, question);
	}
	for( int i = 0; i < question.length(); i++){
		if(question[i] == '{'){
			flag = 1;
			variables_quantity++;
			continue;
		}
		if(flag == 1 && question[i] != '}'){
			if(variables_length >= 9){
				continue;
			}
			variables_names[variables_quantity][variables_length] = question[i];
			variables_length++;
			continue;
		}
		if(question[i] == '}'){
			variables_names[variables_quantity][variables_length] = '\n';
		}
		flag = 0;
		variables_length = 0;
	}
}

void Input::print_question(){
	std::cout << "You are in question no. " << question_number << std::endl;
	std::cout << question << std::endl;
	std::cout << "There are " << variables_quantity+1 << " variables." << std::endl;

	for(int i = 1; i <= variables_quantity+1; i++){//Print variables
		std::cout << "Variable no. " << i << " is ";
		for(int j = 0; variables_names[i-1][j] != '\n'; j++){
			std::cout << variables_names[i-1][j];
		}
		std::cout << std::endl;
	}
}