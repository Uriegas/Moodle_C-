#include "../include/question.h"

//Answer Class
void Answer::read_formula(){
    std::string formula;
    vector_error tokenized_string;//Save tokenized string with error
err:tokenized_string.error = NOERROR;
    formula.clear();
    std::cout << "Ingrese la formula de la respuesta correcta:\n";
    std::cout << std::flush;
    std::getline(std::cin, formula);

    tokenized_string = lexer(formula);
    std::cout<< formula << "\t" << tokenized_string.error << "\n";
    if(tokenized_string.error != NOERROR){//If there is an error in the string print it
        return_error(tokenized_string.error);
        goto err;
    }
    else//If there is no error parse the string and save it to Answer object
        answer_formula = parser(tokenized_string.vector);
}

void Answer::set_tolerance(){
    size_t tole = 0;
    float type;

    std::cin >> tole;
    while(tole <= 0 || tole > 3){
        std::cout << "Ingrese un valor valido \n";
        std::cin >> tole;
    }

    std::cin >> type;
    while(type > 100 || type < 0){
        std::cout << "Ingrese un valor valido \n"
                  << "La tolerancia debe estar entre 0 a 100 \n";
        std::cin >> type;
    }
    tolerance = type;
}
void Answer::set_decimal(){
    int decimal;
    std::string choose;
ag: std::cout << "Ingrese la cantidad de decimales o cifras significativas a mostrar" << "\n";
    std::cin.clear();
    std::cin.ignore(1, '\n');
    std::cin >> decimal;
    std::cout << decimal;
    if(decimal < 0){
        std::cout << "Ingrese un valor valido" << "\n";
        goto ag;
    }
    else
        number_of_decimals = decimal;
dec:std::cout << "Decimales o cifras significativas?" << "\n";
    std::cout << "0." << "\t" << "Decimal" << "\n"
            << ">1." << "\t" << "Cifras Significativas" << std::endl;
    std::cin.ignore();
    std::getline(std::cin, choose);
    if(choose == "0")
        tolerance_type = DECIMAL;
    else if(choose == "1")
        tolerance_type = SIGNIFICATIVE;
    else{
        std::cout << "Ingrese un valor valido" << "\n";
        goto dec;
    }
}

void Answer::set_specific_feedback(){
    specific_feedback = feedback_function("retroalimentacion especifica");
}

//Question Class
//General
void Question::read_question_name(){
    std::getline(std::cin, question_name);
}

void Question::read_question_text(){
    //Save the question text to a string
    std::getline(std::cin, question_text);
    //Get the variables in question text
    wildcards = string_variable_analizer(question_text);
}

void Question::set_default_score(int score){
    default_score = score;
}

void Question::set_general_feedback(){
    general_feedback = feedback_function("retroalimentacion general");
}
void Question::set_answer(Answer answer){
    answers.push_back(answer);
}
//Units treatment
//Units
void Question::set_units(){
uni:std::cout << "Desea calificar unidades?" << "\n"
            << "0." << "\t" << "No, no emplear unidades" << "\n"
            << "1." << "\t" << "Si, OPCIONALES sin calicar" << "\n"
            << "2." << "\t" << "Si, las unidades se calificaran" << std::endl;
    std::cin.ignore();
    std::cin >> unit_treatment;
    if(unit_treatment == NO_UNITS){
        unit = "\n";
        unit_penalization = 0;
    }
    else if(unit_treatment == OPTIONAL_UNITS || unit_treatment == OBLIGATORY_UNITS){
        std::cout << "Ingrese la unidad" << "\n";
        std::cin.clear();
        std::cin.ignore();
        std::getline(std::cin, unit);
        int optional=0;
op:     std::cout << "Unidades van a la derecha o izquierda?\n"
                << "1." << "\t" << "Derecha, como 100km, cm, m" << "\n"
                << "2." << "\t" << "Izquierda, como $100\n";
        std::cin.clear();
        std::cin >> optional;
        if(optional == 1)
            unit_side = RIGHT;
        else if(optional == 2)
            unit_side = LEFT;
        else{
            std::cout << "Ingrese valores validos\n";
            goto op;
        }
        //If it is obligatory request penalization over answer
        if(unit_treatment == OBLIGATORY_UNITS){
            std::cout << "Ingrese la penalizacion" << "\n"
                        << "(Penalizacion sobre la respuesta)" << std::endl;
                        //Not implemented the multiple option or string form
                        //Because user inteface is terminal
            std::cin >> unit_penalization;
        }
    }
    else{
        std::cout << "ERROR: Ingrese una opcion valida" << "\n";
        goto uni;
    }
}
//Multiple Attempts
void Question::set_multiple_attempts(){
    std::string clue_buffer;
    char error = 'y';
    std::cout << "Ingrese la penalizacion por cada intento incorrecto\n"
              << "(Valores porcentuales entre 0 y 100)" << std::endl;
    std::cin.ignore();
    std::cin >> attempt_penalization;
    while(error == 'y'){
        clue_buffer = feedback_function("pistas?\n(Estas se muestran cada que hay un intento fallido)", error);
        if(clue_buffer != "\n")
            clues.push(clue_buffer);
    }
}

//Landmarks
void Question::set_landmarks(){
    std::string temp = feedback_function("marcas");
    std::cout << temp;
    if(temp != "\n")
        landmarks = split_string(temp, ' ');
}
//Created/Modified
void Question::time(){
    if(created == "\n")
        created = current_date();
    last_modified = current_date();
}

//************************************************PRINT FUNCTIONS************************************************
//Print wildcards
std::ostream& operator<<(std::ostream& out, const std::vector<std::string>& wildcards){
    for(int i = 0; i < wildcards.size(); i++)
        out << wildcards[i];
    return out;
}
//Print dataset
//It prints them in a list, ougth to implement matrix printing
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<float>>& datasets){
    for(int i = 0; i < datasets.size(); i++)
        for(int j = 0; j < datasets[i].size(); j++)
            out << datasets[i][j];
    return out;
}
//Print answer
std::ostream& operator<<(std::ostream& out, const std::vector<Answer>& answers){
    for(int i = 0; i < answers.size(); i++){
        out << "Pregunta Numero: " << i << '\n'
            << answers[i].answer_formula << '\n'
            << answers[i].calification << '\n'
            << answers[i].tolerance << '\n'
            << answers[i].tolerance_type << '\n'
            << answers[i].number_of_decimals << '\n'
            << answers[i].decimal_or_significative << '\n'
            << answers[i].specific_feedback << '\n';
    }
    return out;
}
//Print clues
std::ostream& operator<<(std::ostream& out, std::queue <std::string> clues){
    int i = 0;
    while(!clues.empty()){
        out << "Clue: " << i++ << clues.front() << "\n";
        clues.pop();
    }
    return out;
}
void print_question(Question question){
    std::cout << question.question_type << '\n'
        << question.question_name << '\n'
        << question.question_text << '\n'
        << question.default_score << '\n'
        << question.general_feedback << '\n'
        << question.answers << '\n'//overload << operator for vector of answers
        << question.unit_treatment << '\n'
        << question.unit_side << '\n'
        << question.unit << '\n'
        << question.unit_penalization << '\n'
        << question.attempt_penalization << '\n'
        << question.clues << '\n'//Overflow
        << question.landmarks << '\n'
        << question.created << '\n'
        << question.last_modified << '\n';
}
//Print question configuration
std::ostream& operator<<(std::ostream& out, Question& question){
    out << question.question_type << '\n'
        << question.question_name << '\n'
        << question.question_text << '\n'
        << question.default_score << '\n'
        << question.general_feedback << '\n'
        << question.answers << '\n'//overload << operator for vector of answers
        << question.unit_treatment << '\n'
        << question.unit_side << '\n'
        << question.unit << '\n'
        << question.unit_penalization << '\n'
        << question.attempt_penalization << '\n'
        << question.clues << '\n'//Overflow
        << question.landmarks << '\n'
        << question.created << '\n'
        << question.last_modified << '\n';
    return out;
}