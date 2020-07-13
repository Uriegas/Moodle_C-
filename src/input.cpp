#include "../include/input.h"
/*
void Input::set_question( int question ){
	question_number = question;
	}
*/
void Input::deletespace(std::string &string, int space){
	for(int i=space; i <= string.length(); i++){
		string[i] = string[i+1];
	}
	string.resize(string.length()-1);
}

void Input::read_question(){
	int flag = 0;
	int variables_length = 0;

	while(std::cin.peek() != '\n'){//Read user input and save in question
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
/*
void Input::read_formula(){
//	int flag = 0;
//	int variables_length = 0;
	std::vector<std::string> formulas;
	char variables[10][10];
	std::string* formu = new std::string;

	while(std::cin.peek() != '\n'){//Read user input and save in formula
		std::getline(std::cin, formula);
	}

	if(formula[0] == '='){
		deletespace(formula, 0);
	}

	for(int i = 0; i< formula.length(); i++){
		if(formula[i] == ' '){
			deletespace(formula, i);
		}
	}

	for(int i = 0; i < formula.length(); i++){
		if(formula[i] == '('){
			;
		}
		formu[0] = formula[i];
		formulas.push_back(formula);

	}

	if(formula[0] == '('){

	}
	else if(formula[0] == '{'){

	}
	else{
	}

	for(int i = 0; i< formula.length(); i++){
		if(formula[i] == '('){
			flag = 1;
			variables_quantity++;
			continue;
		}
		if(flag == 1 && formula[i] != '}'){
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
}*/


// Function to find precedence of  
// operators. 
int precedence(char op){ 
    if(op == '+'||op == '-') 
    return 1; 
    if(op == '*'||op == '/') 
    return 2; 
    return 0; 
} 
  
// Function to perform arithmetic operations. 
int applyOp(int a, int b, char op){ 
    switch(op){ 
        case '+': return a + b; 
        case '-': return a - b; 
        case '*': return a * b; 
        case '/': return a / b; 
    } 
} 
  

// Function that returns value of 
// expression after evaluation. 
int read_formula(std::string tokens){ 
    int i; 
      
    // stack to store integer values. 
    std::stack <int> values; 
      
    // stack to store operators. 
    std::stack <char> ops; 
      
    for(i = 0; i < tokens.length(); i++){ 
          
        // Current token is a whitespace, 
        // skip it. 
        if(tokens[i] == ' ') 
            continue; 
          
        // Current token is an opening  
        // brace, push it to 'ops' 
        else if(tokens[i] == '('){ 
            ops.push(tokens[i]); 
        } 
          
        // Current token is a number, push  
        // it to stack for numbers. 
        else if(isdigit(tokens[i])){ 
            int val = 0; 
              
            // There may be more than one 
            // digits in number. 
            while(i < tokens.length() &&  
                        isdigit(tokens[i])) 
            { 
                val = (val*10) + (tokens[i]-'0'); 
                i++; 
            } 
              
            values.push(val); 
        } 
          
        // Closing brace encountered, solve  
        // entire brace. 
        else if(tokens[i] == ')') 
        { 
            while(!ops.empty() && ops.top() != '(') 
            { 
                int val2 = values.top(); 
                values.pop(); 
                  
                int val1 = values.top(); 
                values.pop(); 
                  
                char op = ops.top(); 
                ops.pop(); 
                  
                values.push(applyOp(val1, val2, op)); 
            } 
              
            // pop opening brace. 
            if(!ops.empty()) 
               ops.pop(); 
        } 
          
        // Current token is an operator. 
        else
        { 
            // While top of 'ops' has same or greater  
            // precedence to current token, which 
            // is an operator. Apply operator on top  
            // of 'ops' to top two elements in values stack. 
            while(!ops.empty() && precedence(ops.top()) 
                                >= precedence(tokens[i])){ 
                int val2 = values.top(); 
                values.pop(); 
                  
                int val1 = values.top(); 
                values.pop(); 
                  
                char op = ops.top(); 
                ops.pop(); 
                  
                values.push(applyOp(val1, val2, op)); 
            } 
              
            // Push current token to 'ops'. 
            ops.push(tokens[i]); 
        } 
    } 
      
    // Entire expression has been parsed at this 
    // point, apply remaining ops to remaining 
    // values. 
    while(!ops.empty()){ 
        int val2 = values.top(); 
        values.pop(); 
                  
        int val1 = values.top(); 
        values.pop(); 
                  
        char op = ops.top(); 
        ops.pop(); 
                  
        values.push(applyOp(val1, val2, op)); 
    } 
      
    // Top of 'values' contains result, return it. 
    return values.top();
} 