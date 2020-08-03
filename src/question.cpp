#include "../include/question.h"

//Answer Class
void Answer::read_formula(){
    std::string formula;
err:std::getline(std::cin, formula);
    vector_error tokenized_string;//Save tokenized string with error

    tokenized_string = lexer(formula);
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
    std::cin >> decimal;
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
    int select;
uni:std::cout << "Desea calificar unidades?" << "\n"
            << "0." << "\t" << "No, no emplear unidades" << "\n"
            << "1." << "\t" << "Si, OPCIONALES sin calicar" << "\n"
            << "2." << "\t" << "Si, las unidades se calificaran" << std::endl;
    std::cin.ignore();
    std::cin >> select;
    if(select == 0){
        unit = "\n";
        unit_penalization = 0;
        unit_treatment = NO_UNITS;
    }
    else if(select == 1 || select == 2){
        std::cout << "Ingrese la unidad" << "\n";
        std::getline(std::cin, unit);
        int optional;
op:     std::cout << "Unidades van a la derecha o izquierda?\n"
                << "1." << "\t" << "Derecha, como 100km, cm, m" << "\n"
                << "2." << "\t" << "Izquierda, como $100" << std::endl;
        std::cin >> optional;
        if(optional == 1)
            unit_side = RIGHT;
        else if(optional == 2)
            unit_side = LEFT;
        else
            std::cout << "Ingrese valores validos\n";
            goto op;

        if(select == 2){
            unit_treatment = OBLIGATORY_UNITS;
            std::cout << "Ingrese la penalizacion" << "\n"
                        << "(Penalizacion sobre la respuesta)" << std::endl;
                        //Not implemented the multiple option or string form
        }
        else
            unit_treatment = OPTIONAL_UNITS;
    }
    else{
        std::cout << "ERROR: Ingrese una opcion valida" << "\n";
        goto uni;
    }
}
//Landmarks
void Question::set_landmarks(){
    landmarks[0] = feedback_function("marcas");
    landmarks = split_string(landmarks[0], ' ');
}
//Created/Modified
void Question::time(){
    if(created == "\n")
        created = current_date();
    last_modified = current_date();
}