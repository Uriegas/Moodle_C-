#include "../include/exam.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMMENTS SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Note: Implement an exit option later below line 14

//Returns 1 or 0 if question is correct or not
//This function evaluates tolerance
int answer_correctness(float x, float t, int type_of_tolerance){
    float dx = abs(x-t);
    if(type_of_tolerance == NOMINAL)
        return dx <= t ? 1 : 0;
    else if(type_of_tolerance == RELATIVE)
        return (dx/x) <= t ? 1 : 0;
    else if(type_of_tolerance == GEOMETRIC)
        return x/(1+t) <= (x+dx) <= x*(1+t) ? 1 : 0;
    else
        return -1;
}

//First user interface
//Returns 2 if it edits a question
//Returns 1 if it adds a new question
//Returns 0 if it wants to exit
int Exam::show_exam(){
    int agregar_editar;
    std::string buffer;
    std::cout << "\t" << "MOODLE" << "\t" << "\n"
            << "Interfaz para crear un examen" << "\n"
            << "Este examen tiene " << questions.size() << " pregutas" << std::endl; 
agr:std::cout << "Opciones:" << "\n"
            << "(Ingrese el numero)" << "\n"
            << "0." << "\t" << "Salir de MOODLE" << "\n"
            << "1." << "\t" << "Agregar pregunta" << "\n"
            << "2." << "\t" << "Subir pregunta desde archivo" << "\n"
            << "3." << "\t" << "Subir conjunto de datos desde archivo" << "\n"
            << "4." << "\t" << "Previsualizar pregunta" << "\n"
            << "5." << "\t" << "Aplicar examen" << "\n"
            << "6." << "\t" << "Visualizar configuracion actual" << "\n";
    std::cin.clear();
    std::getline(std::cin, buffer);
    std::stringstream(buffer) >> agregar_editar;
    if(agregar_editar < 0 || agregar_editar > 6){
        std::cout << "ERROR: Ingrese un valor valido" << std::endl;
        goto agr;
    }
    return agregar_editar;
}

//Function to select a question type
//Has a counter that increments each time that is called
//For use in the examen later
Question Exam::create_new_question(){
    //Instatiate classes about the question elemnts
    int score;
    int selected_question;
que:std::cout << "Pueden ingresar 3 tipos de preguntas" << "\n"
            << "1." << "\t" << "Calculada Simple" << "\n"
            << "2." << "\t" << "Calculada Normal" << "\n"
            << "3." << "\t" << "Calculada Multiple" << "\n"
            << "\n" << "Que tipo de pregunta desea realizar?" << "\n"
            << "(Ingrese el numero)" << std::endl;
    std::cin >> selected_question;
    if (selected_question > 3 || selected_question < 1){
        std::cout << "ERROR: Ingrese un numero de pregunta valido" <<std::endl;
        goto que;
    }
    else{
        Question question(selected_question);
        //<<<<<<<<<< HERE is all the process of user interface (input from teacher) >>>>>>>>>>>>>>>
        //<<<<<<<<<< Question Section >>>>>>>>>>>>>>>
        //This sections applies to the three types of questions
        std::cout << "Ingrese el nombre de la pregunta" << "\n";
        std::cin.ignore();
        question.read_question_name();
        std::cout << "Ingrese el texto de la pregunta" << "\n";
        question.read_question_text();
        std::cout << "Ingrese la puntuacion por defectuo de la pregunta" << "\n"
                    << "(Puntos de la pregunta) Comunmente este valor es de 1" << "\n";
        std::cin >> score;
        question.set_default_score(score);
        question.set_general_feedback();

        //<<<<<<<<<< Answer Section >>>>>>>>>>>>>>>
        Answer answer;
        if(selected_question == SIMPLE){
            std::string another_question = "y";
            while(another_question == "y" || another_question == "1"){
                //Read answer input
                //read_formula returns a postfix notation queue tokenized
                std::cin.clear();
                std::cin.ignore();
                answer.read_formula();
                if(selected_question != MULTIPLE){
                    std::cout << "Ingrese el tipo de tolerancia y despues el valor de la tolerancia" << "\n"
                                << "Tipos de tolerancia:" << "\n"
                                << "1." << "\t" << "Relativa" << "\n"
                                << "2." << "\t" << "Nominal" << "\n"
                                << "3." << "\t" << "Geometrica" << "\n";
                    answer.set_tolerance();
                }
                answer.set_decimal();
                answer.set_specific_feedback();
                question.set_answer(answer);
                std::cout << "Desea agregar otra pregunta?\n"
                            <<"y = si\to\t1 = si\n"
                            <<"n = no\to\t0 = no\n";
                std::cin >> another_question;
            }
            //<<<<<<<<<< Unit Section >>>>>>>>>>>>>>>
            question.set_units();
            //<<<<<<<<<< Multiple Attempts Section >>>>>>>>>>>>>>>
            //This section is not included in the simple question format

            //<<<<<<<<<< Landmark Section >>>>>>>>>>>>>>>
            std::cin.clear();
            std::cin.ignore();
            question.set_landmarks();

            //<<<<<<<<<< Created/Last Change Section >>>>>>>>>>>>>>>
            question.time();
            std::cout << "Pregunta creada en " << question.created << "\n"
                    << "Pregunta modifica en " << question.last_modified << "\n";
        }
        else if(selected_question == CALCULATED){}
        else{//Multiple Question -No need to prove it
        }
        return question;
    }
}

//Load question from a file to the exam
void Exam::load_question(std::string file){
    //Create temporary question data type
    Question question;
    std::ifstream myfile;
    std::string buffer;
    std::vector<std::string> arr;//Saves data temporary to a vector

    myfile.open(file, std::ios::in);
    if(myfile.fail())
        std::cout << "No se pudo abrir el archivo\nIntente subir un archivo valido\n";
    else{

        while(!myfile.eof()){
            std::getline(myfile, buffer, '\n');
            arr.push_back(buffer);
        }
        myfile.close();
        //Save to struct
        vector_to_question(arr, question);
        /*
        me.myname = arr[0];
        std::stringstream(arr[1]) >> me.myage;
        me.state = arr[2];
        std::stringstream(arr[3]) >> me.avg;
        */
        //Print temporary array
        for(int i = 0; i < arr.size(); i++)
            std::cout << arr[i] << '\n';
        std::cout << "\n---------------------------\n";
    }

    //Print question data type
    std::cout << question;
    //Save question to the exam
    questions.push_back(question);
}

void Exam::load_dataset(std::string& file){
    Dataset dataset;
    std::ifstream myfile;
    std::string buffer;
    std::vector<std::string> data;//Saves data temporary to a vector
    std::vector<std::string> arr;
    std::string numbers;
    int counter = 0;
    myfile.open(file, std::ios::in);

    if(myfile.fail())
        std::cout << "Error abriendo el archivo datasets.txt\nAsegurese de que no lo haya borrado\n";
    else{
        //Load file to string
        while(!myfile.eof()){
            std::getline(myfile, buffer, '\n');
            if(buffer == "Dataset\n" || counter == 0){
                counter++;
                continue;
            }
            else if(counter == 1){//Save wildcard
                arr = split_string(buffer, ' ');
                data.push_back(arr[1]);
                counter ++;
                continue;
            }
            else if(counter == 2){//Save type 
                arr = split_string(buffer, ' ');
                if(arr[1] == "PRIVATE"){
                    data.push_back("0");
                }
                else if(arr[1] == "SHARED"){
                    data.push_back("1");
                }
                else
                    break;
                counter++;
                continue;
            }
            else if(counter == 3){//Save syncronization
                arr = split_string(buffer, ' ');
                if(arr[1] == "OFF"){
                    data.push_back("0");
                }
                else if(arr[1] == "ON"){
                    data.push_back("1");
                }
                else
                    break;
                counter++;
                continue;
            }
            else if(counter == 4 || counter == 5 || counter == 6 ||
                    counter == 6 || counter == 7){//Save values of dataset
                numbers += buffer;
                counter++;
                continue;
            }
            else if(buffer == "End\n" || counter == 8){//Save to datasets vector
                numbers+= buffer;
                data.push_back(numbers);
                dataset.vector_to_dataset(data, dataset);
                datasets.push_back(dataset);
                data.clear();
                arr.clear();
                numbers.clear();
                counter = 0;
                continue;
            }
            else{
                std::cout << "Estructura invalida\n";
                break;
            }
        }
        myfile.close();
        //Print temporary array
        /*
        for(int i = 0; i < data.size(); i++)
            std::cout << data[i] << '\n';
        std::cout << "\n---------------------------\n";
        */
    }
    //Print question data type
    /*
    for(int i = 0; i < datasets.size(); i++)
        datasets[i].print_dataset();
    */
}

//Print exam (all questions) in a list
std::ostream& operator<<(std::ostream& out, std::vector<Question>& questions){
    for(int i = 0; i < questions.size(); i++)
        out << questions[i];
    return out;
}

void Exam::print_question_list(){
    std::cout << "Lista de Preguntas en el Examen Actual\n";
    for(int i = 0; i < questions.size(); i++)
        std::cout << "Pregunta No. " << (i+1) << '\t' << questions[i].question_name << '\n';
    std::cout << '\n';
}

void Exam::apply_exam(){
    if(questions.empty())
        std::cout << "Error: No hay preguntas cargadas en el examen";
    else{
        //Get the total points of the exam
        float max_score = 0;
        for(int i = 0; i < questions.size(); i++)
            max_score += questions[i].default_score;
        for(int i = 0; i < questions.size(); i++)
            calification += apply_question(i);
        std::cout << "Su puntuacion final en este examen es de " << (calification/max_score)*100
                  << "\n------------------------------------------------------\n\n";
    }
}
//Reads current question config and performs an operation
//Returns de result of the operation
//no_que = number of question
float Exam::apply_question(int& no_que){
    //This function dependes on datasets
    //There are 3 types of applications
    //1.    Fetch dataset
    //2,    Instantiate wildcards
    //3.    Set cout and cin options (User interface)
    //4.    Evaluate input considering configuration
    
    //only simple question supported yet
    std::vector<std::string> inst_wild;
    std::vector<std::string> formulas;
    std::vector<std::string> formulas_to_replace;
    std::vector<std::string> solved_formulas;
    std::vector<float> result_of_formulas;

    srand(time(NULL));
    //Find according dataset for each wildcard and instantate them in order
    for(int i = 0; i < questions[no_que].wildcards.size(); i++)//Instantate variables
        for(int j = 0; j < datasets.size(); j++)
            if(questions[no_que].wildcards[i] == datasets[j].wildcard)
                inst_wild.push_back(datasets[j].get_random_number());
    //Configure the current question
    questions[no_que].apply(inst_wild);
/*
    //Replace wildacards in question text and formula of answer by the instantiated ones
    for(int i = 0; i < inst_wild.size(); i++){
        ReplaceStringInPlace(questions[no_que].question_text, '{'+questions[no_que].wildcards[i]+'}', inst_wild[i]);
        ReplaceStringInPlace(questions[no_que].answers[0].formula, '{'+questions[no_que].wildcards[i]+'}', inst_wild[i]);
    }

    //Get string formula for specific and general feedback
    //Saved in vector, IMPORTANT we know that the first two positions are fixed but clues not
    formulas.push_back(find_formula_in_string(questions[no_que].general_feedback));
    for(int i = 0; i < questions[no_que].answers.size(); i++)//Iterate over answers feedback to find the formulas in answeer
        formulas.push_back(find_formula_in_string(questions[no_que].answers[i].specific_feedback));
    formulas_to_replace = formulas;
    //Dont implemnt clues 
    //for(int i = 0; i < questions[no_que].clues.size(); i++)
    //    formulas.push_back(find_formula_in_string(questions[no_que].clues[i]));
    //Now replace variables in formulas by a random number saved in instant_wildcards
    for(int i = 0; i < formulas.size(); i++)//Iterate over each formula
        for(int j = 0; j < questions[no_que].wildcards.size(); j++)//Iterate over each wildcard
            ReplaceStringInPlace(formulas[i], '{' + questions[no_que].wildcards[j] + '}', inst_wild[j]);

    //Instantiate all the formulas and save to another verctor
    for(int i = 0; i < formulas.size(); i++){
        result_of_formulas.push_back(questions[no_que].answers[0].string_to_formula(formulas[i]));
//        result_of_formulas.push_back( evaluate(parser(lexer(formulas[i]).vector), 0, 1000) );
    }
    //Replace the result in every string that is going to be shown to the user
    ReplaceStringInPlace(questions[no_que].general_feedback, '[' + formulas_to_replace[0] + ']', std::to_string(result_of_formulas[0]));
    ReplaceStringInPlace(questions[no_que].answers[0].specific_feedback, '[' + formulas_to_replace[1] + ']', std::to_string(result_of_formulas[1]));

    //Convert the string formula in the answer into a result instantiaded by the wildcards
    for(int j = 0; j < questions[no_que].wildcards.size(); j++)//Iterate over each wildcard
        ReplaceStringInPlace(questions[no_que].answers[0].formula, '{' + questions[no_que].wildcards[j] + '}', inst_wild[j]);
    questions[no_que].answers[0].result = questions[no_que].answers[0].string_to_formula(questions[no_que].answers[0].formula);
*/
    //Evaluate question already instantiated
    std::string buffer;
    float user_ans;
    float calif;
    std::cout << questions[no_que].question_text << '\n';
    std::cin.clear();
    std::getline(std::cin, buffer);
    std::stringstream(buffer) >> user_ans;
    std::cout << "Su respuesta fue " << user_ans << '\n'
                << "La respuesta es ";
    //Evaluate if the answer is correct
    if(answer_correctness(user_ans, questions[no_que].answers[0].tolerance, 
                 questions[no_que].answers[0].tolerance_type) == 1){
                std::cout << "correcta\n" << "Retroalimentacion Especifica: " <<
                questions[no_que].answers[0].specific_feedback << '\n';
                calif = (float)(questions[no_que].answers[0].calification)/100*(float)questions[no_que].default_score;
    }
    else{
        std::cout << "incorrecta\n";
        calif = 0;
    }
    std::cout << "La respuesta correcta es " << questions[no_que].answers[0].result << '\n';
    std::cout << "Retroalimentacion General: " << questions[no_que].general_feedback << '\n'
              << "---------------------------------------------------\n\n";
    std::cout << "Su puntuacion para esta pregunta es: " << calif << '\n';
    return calif;
}
//Modularize apply question function