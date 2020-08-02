#include "../include/input.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMMENTS SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Functions to modify the question

//Function that delete spaces from a string ej. "e sto y asi " -> "estoyasi"
void deletespace(std::string &str){
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}

//Finds variables (sorrounded by {}) in a string and returns them in a vector
std::vector<std::string> string_variable_analizer(const std::string base) {
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

//****************CLASS FUNCTIONS********************
//Rea d question from keyboard to a string
std::string read_question(){
    std::string question;
    std::getline(std::cin, question);
    return question;
}

//Prints the question string to the screen
void print_question(){
//	std::cout << "You are in question no. " << question_number << std::endl;
	std::cout << question << std::endl;
}

//Reads from keyboard and saves to an string
//ans converts it from infix to postifx notation
//It returns a vector in postfix notation
std::queue<tokens> read_formula(std::string string){
    //Tokenize and parse the string
    std::queue<tokens> postfix_formula = parser( lexer(string) );
    return postfix_formula;
}

//Accepts the Answer strcuture
//Modifies tolerance parameters
void set_tolerance(Answer& answer){ //Not implemented
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

//Brief interface that returns what the user entered
std::string feedback_function(const std::string& feedback_type){
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
std::vector<std::string> split_string(std::string str, char dl){
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