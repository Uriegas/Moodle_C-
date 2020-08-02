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
		if(flag == 1 && base[i] != '{')
            buffer += base[i];

        if(base[i] == '}'){
            buffer.pop_back();
            stack.push_back(buffer);
            flag = 0;
            buffer.clear();
        }
    }
    return stack;
}

// Function to find precedence of  
// operators. 
//Think that I dont need it anymore
int precedence(char op){ 
    if(op == '+'||op == '-') 
    return 1; 
    if(op == '*'||op == '/') 
    return 2; 
    return 0; 
} 
  
// Function to perform arithmetic operations. 
//Think that I dont need it anymore
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
//Think that I dont need it anymore
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
        else if(tokens[i] == '(')
            ops.push(tokens[i]);
          
        // Current token is a number, push  
        // it to stack for numbers. 
        else if(isdigit(tokens[i])){ 
            int val = 0; 
            // There may be more than one 
            // digits in number. 
            while(i < tokens.length() && isdigit(tokens[i])){
                val = (val*10) + (tokens[i]-'0'); 
                i++; 
            } 
            values.push(val); 
        } 
          
        // Closing brace encountered, solve  
        // entire brace. 
        else if(tokens[i] == ')'){
            while(!ops.empty() && ops.top() != '('){
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
        else{
            // While top of 'ops' has same or greater  
            // precedence to current token, which 
            // is an operator. Apply operator on top  
            // of 'ops' to top two elements in values stack. 
            while(!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])){ 
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

	for( int i = 0; i < formula.length(); i++){
		if(formula[i] == '{'){
			flag = i+1;
            buffer += formula[i];
			continue;
		}
		if(flag != 0 && formula[i] != '{')
            buffer += formula[i];

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

//Function to return precedence of operators 
int prec(char c){
	if(c == '^') 
        return 3; 
	else if(c == '*' || c == '/') 
        return 2; 
	else if(c == '+' || c == '-') 
        return 1; 
	else
        return -1; 
} 

// The main function to convert infix expression 
//to postfix expression 
std::string infixToPostfix(std::string s){
	std::stack<char> st;
	st.push('N');
	int l = s.length();
	std::string ns;

	for(int i = 0; i < l; i++){
		// If the scanned character is an operand, add it to output string. 
		if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) 
            ns+=s[i]; 
		// If the scanned character is an ‘(‘, push it to the stack. 
		else if(s[i] == '(') 
            st.push('('); 
		
		// If the scanned character is an ‘)’, pop and to output string from the stack 
		// until an ‘(‘ is encountered. 
		else if(s[i] == ')'){
			while(st.top() != 'N' && st.top() != '('){
				char c = st.top(); 
				st.pop(); 
                ns += c; 
			} 
			if(st.top() == '('){
				char c = st.top(); 
				st.pop(); 
			} 
		} 
		//If an operator is scanned 
		else{ 
			while(st.top() != 'N' && prec(s[i]) <= prec(st.top())){ 
				char c = st.top(); 
				st.pop(); 
				ns += c; 
			} 
			st.push(s[i]); 
		} 
	} 
	//Pop all the remaining elements from the stack 
	while(st.top() != 'N'){ 
		char c = st.top(); 
		st.pop(); 
		ns += c; 
	} 
} 

//****************CLASS FUNCTIONS********************
//Rea d question from keyboard to a string
std::string Input::read_question(){
    std::string question;
    std::getline(std::cin, question);
    return question;
}

//Prints the question string to the screen
void Input::print_question(){
//	std::cout << "You are in question no. " << question_number << std::endl;
	std::cout << question << std::endl;
}

//Reads from keyboard and saves to an string
//ans converts it from infix to postifx notation
//It returns a vector in postfix notation
std::queue<tokens> Input::read_formula(std::string string){
    //Tokenize and parse the string
    std::queue<tokens> postfix_formula = parser( lexer(string) );
    return postfix_formula;
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
std::string Input::current_date(){
   // current date/time based on current system
    time_t now = time(0);
   // convert now to string form
    std::string dt = ctime(&now);
    return dt;
}

//Brief interface that returns what the user entered
std::string Input::feedback_function(const std::string& feedback_type){
    char* retro = new char;
    std::string feedback_return;
ret:std::cout << "Desea agregar " << feedback_type << "\n"
            << "y = si" << "\n"
            << "n = no" << "\n";
    std::cin >> *retro;
    if((*retro) == 'y'){
        std::cout << "Ingrese la(s) " << feedback_type << "\n";
        std::cin.ignore();
        std::getline(std::cin, feedback_return);
    }
    else if((*retro) == 'n'){
        feedback_return = "\n";
    }
    else{
        std::cout << "Ingrese un valor valido" << "\n";
        goto ret;
    }
    delete retro;
    return feedback_return;
}

// function to split string into substrings on the 
// basis of delimiter and return the substrings 
// after split in a vector of strings
std::vector<std::string> Input::split_string(std::string str, char dl){
    std::string word = ""; 
    // to count the number of split strings 
    int num = 0; 
    // adding delimiter character at the end 
    // of 'str' 
    str = str + dl; 
    // length of 'str' 
    int l = str.size(); 
    // traversing 'str' from left to right 
    std::vector<std::string> substr_list; 
    for (int i = 0; i < l; i++) { 
        // if str[i] is not equal to the delimiter 
        // character then accumulate it to 'word' 
        if (str[i] != dl) 
            word = word + str[i]; 
        else { 
            // if 'word' is not an empty string, 
            // then add this 'word' to the array 
            // 'substr_list[]' 
            if ((int)word.size() != 0) 
                substr_list.push_back(word); 
            // reset 'word' 
            word = ""; 
        } 
    } 
    // return the splitted strings 
    return substr_list; 
}