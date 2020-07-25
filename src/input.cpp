#include "../include/input.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMMENTS SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Input Example
//pow({x}, 2) + (pow(sin({y}), 2));

//Output Example
//x2!2y^!+

//****************LOCAL FUNCTIONS********************

//Function that delete spaces from a string ej. "e sto y asi " -> "estoyasi"
void deletespace(std::string &str){
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}

//Finds variables (sorrounded by {}) in a string and returns them in a vector
std::vector<std::string> Input::string_variable_analizer(const std::string base) {
	int flag = 0;
    std::string buffer;
    std::vector<std::string> stack;

	for( int i = 0; i < base.length(); i++){
		if(base[i] == '{'){
			flag = 1;
			continue;
		}
		if(flag == 1 && base[i] != '{'){
            buffer += base[i];
		}

        if(base[i] == '}'){
            buffer.pop_back();
            stack.push_back(buffer);
            flag = 0;
            buffer.clear();
        }
    }
    return stack;
}

//ERROR:Delete this
void string_sintax_processor(std::string formula){
    std::stack <char> variables;

    int replace_position = 0; 
    for(int i; i< formula.length(); i++){
        replace_position = formula.find('{');

    }
}

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
float applyOp(int a, int b, char op){ 
    switch(op){ 
        case '+': return a + b; 
        case '-': return a - b; 
        case '*': return a * b; 
        case '/': return a / b;//Added math functions, not implemented yet
        case '!': return pow(a, b);
        case '@': return abs(a);
        case '#': return log(a);
        case '$': return rand();
        case '%': return sqrt(a);
        case '^': return sin(a);
        case '&': return cos(a);
        case '~': return tan(a);
    } 
} 

// Function that returns value of 
// expression after evaluation. 
int formula_to_postfix_notation(const std::string tokens){ 
    int i; 
    // stack to store float values. 
    std::stack <float> values; 
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

//Give it a base string (subject), and search and replace strings, 
//and it changes the result string
void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

//Finds variables aka "comodines" (ej. {var})
//in a string and replace them with
//the second element of the variable (ej. 'v')
void replace_variables_in_string(std::string &formula){
	int flag = 0;
    std::string buffer;
//{Hola} + {todo}
	for( int i = 0; i < formula.length(); i++){
		if(formula[i] == '{'){
			flag = i+1;
            buffer += formula[i];
			continue;
		}
		if(flag != 0 && formula[i] != '{'){
            buffer += formula[i];
		}

        if(formula[i] == '}'){
            std::string buffer2;
            buffer2+=buffer[1];
            ReplaceStringInPlace(formula, buffer, buffer2);
            flag = 0;
            buffer.clear();
            buffer2.clear();
            i = 1;
        }
    }
}
//****************CLASS FUNCTIONS********************

//Read question from keyboard to a string
std::string Input::read_question(){
    std::string question;
    std::getline(std::cin, question);
    return question;
//    if(ANALIZE == 1)
//        variable_names = string_variable_analizer(question);
//  question_number++;
}

//Prints the question string to the screen
void Input::print_question(){
//	std::cout << "You are in question no. " << question_number << std::endl;
	std::cout << question << std::endl;
}

//Reads from keyboard and saves to string the formula
//also convert it to postfix notation for future use
int Input::read_formula(){
    std::getline(std::cin, formula);

    std::vector <std::string> variables;
    std::string buffer;
    int counter = 0;

    variables = string_variable_analizer(formula);
    for(int j=0; j<variable_names.size(); j++){
        for(int i=0; i<variables.size(); i++){
            if(variables[i] == variable_names[j])
                counter++;
        }
    }

    if(counter == variable_names.size() && counter == variables.size()){
        std::cout << "Variables were well written" << std::endl;
        //Here the parser and postfix converter
        deletespace(formula);
        replace_variables_in_string(formula);
    }
    else{
        std::cout<< "Error: Ingreso mal las varaibles" << std::endl;
        return 0;
    }
}

//Prints the formula string in the class Input
void Input::print_formula(){
	std::cout << formula << std::endl;
}
//Accepts the Answer strcuture
//Modifies tolerance parameters
void Input::set_tolerance(Answer& answer){ //Not implemented
    std::cout << "Ingrese la tolerancia de la respuesta" << "\n";
    std::cin >> answer.tolerance;

    std::cout << "Ingrese el tipo de tolerancia" << "\n"
            << "1." << "\t" << "Relativa" << "\n"
            << "2." << "\t" << "Nominal" << "\n"
            << "3." << "\t" << "Geometrica" << std::endl;
    std::cin >> answer.tolerance_type;
} 

//Simple function that returns
//the current date and time
std::string current_date(){
   // current date/time based on current system
    time_t now = time(0);
   // convert now to string form
    std::string dt = ctime(&now);
    return dt;
}