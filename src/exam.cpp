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
    std::string buff;
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
        if(selected_question == SIMPLE || selected_question == CALCULATED){
            std::string another_question = "y";
            while(another_question == "y" || another_question == "1"){
                //Read answer input
                //Evaluate if the string is in correct notation
                std::cin.clear();
                answer.read_formula();
                question.wildcards = string_variable_analizer(answer.formula);//Find wildcards in formula
                answer.set_calification();
                std::cout << "Ingrese el tipo de tolerancia y despues el valor de la tolerancia" << "\n"
                            << "Tipos de tolerancia:" << "\n"
                            << "1." << "\t" << "Relativa" << "\n"
                            << "2." << "\t" << "Nominal" << "\n"
                            << "3." << "\t" << "Geometrica" << "\n";
                answer.set_tolerance();
                answer.set_decimal();
                answer.set_specific_feedback();
                //Add answer to the question settings
                question.set_answer(answer);
                std::cout << "Desea agregar otra respuesta?\n"
                            <<"y = si\to\t1 = si\n"
                            <<"n = no\to\t0 = no\n";
                std::cin >> another_question;
            }
        }
        else{//MULTIPLE Question, By default 4 answers
            int pregunta = 1;
            std::cout << "Configuracion de preguntas para pregunta calculada\n"
                      << "Las preguntas calculadas tiene 4 opciones por defecto\n"
                      << "-----------------------------------------------------\n";
            while(pregunta <= 4){
                std::cout << "Opcion numero " << pregunta << '\n';
                //Read answer input
                //Evaluate if the string is in correct notation
                std::cin.clear();
                answer.read_formula();
                question.wildcards = string_variable_analizer(answer.formula);//Find wildcards in formula
                answer.set_decimal();
                answer.set_specific_feedback();
                //Add answer to the question settings
                question.set_answer(answer);
                pregunta++;
            }
        }
            //<<<<<<<<<< Unit Section >>>>>>>>>>>>>>>
            question.set_units();
            //<<<<<<<<<< Multiple Attempts Section >>>>>>>>>>>>>>>
            //This section is not included in the simple question format

            //<<<<<<<<<< Landmark Section >>>>>>>>>>>>>>>
            std::cin.clear();
            question.set_landmarks();
            
            //<<<<<<<<<< Dataset Section >>>>>>>>>>>>>>>
            //Only for Multiple and Calculated
            if(selected_question == MULTIPLE || selected_question == CALCULATED){
                score = 0; //reuse this var;
                while( (score < 1) || (score > 2) ){
                std::cout << "\nDesea configurar el conjunto de datos o que moodle lo genere?\n"
                        << "1.\tGenerado por moodle\n"
                        << "2.\tAgregar items manualmente\n";
                std::cin.clear();
                std::getline(std::cin, buff);
                std::stringstream(buff) >> score;
                std::cout << buff << '\n' << score << '\n';
                }
                if(score == 1){//Generate dataset automaticly
                    int min, max;
                    for(int i = 0; i < question.wildcards.size(); i++){
                        std::cout << "Conjunto de datos para el comodin: " << question.wildcards[i]
                                << "\nIngrese el rango de los numeros a generar\n"
                                << "Minimo>";
                        std::cin.clear();
                        std::getline(std::cin, buff);
                        std::stringstream(buff) >> min;
                        std::cout << "\nMaximo>";
                        std::cin.clear();
                        std::getline(std::cin, buff);
                        std::stringstream(buff) >> max;
                        create_dataset(question.wildcards[i], min, max);
                    }
                }
                else{//Add items to the dataset
                    for(int i = 0; i < question.wildcards.size(); i++){
                        Dataset dataset;
                        int item;
                        std::cout << "Conjunto de datos para el comodin: " << question.wildcards[i];
                        for(int j = 0; j <= MAX_SET_SIZE; j++){
                            std::cout << "Ingrese un numero para agregar al conjunto de datos\n";
                            std::cin.clear();
                            std::getline(std::cin, buff);
                            std::stringstream(buff) >> item;
                            dataset.add_number(std::to_string(item));
                        }
                        if(dataset.dataset_size() < MAX_SET_SIZE){
                            dataset.moodle_set_generation(0, 100);//Generate the rest of the data
                        }
                        datasets.push_back(dataset);
                    }
                }
            }
            else{//SIMPLE Question
                int min, max;
                for(int i = 0; i < question.wildcards.size(); i++){
                    std::cout << "Conjunto de datos para el comodin: " << question.wildcards[i]
                            << "\nIngrese el rango de los numeros a generar\n"
                            << "Minimo>";
                    std::cin.clear();
                    std::getline(std::cin, buff);
                    std::stringstream(buff) >> min;
                    std::cout << "\nMaximo>";
                    std::cin.clear();
                    std::getline(std::cin, buff);
                    std::stringstream(buff) >> max;
                    create_dataset(question.wildcards[i], min, max);
                }
            }
        //<<<<<<<<<< Created/Last Change Section >>>>>>>>>>>>>>>
        //Get current time
        question.time();
        std::cout << "Pregunta creada en " << question.created << "\n"
                << "Pregunta modifica en " << question.last_modified << "\n";
        do{
        std::cout << "Desea guardar este pregunta en un .txt?\n"
                    << "1.\tSi\n2.\tNo\n";
        std::cin.clear();
        std::getline(std::cin, buff);
        std::stringstream(buff) >> selected_question;//Reuse this int
        std::cout << selected_question;
        }while( (selected_question < 1) || (selected_question > 2) );

        if(selected_question == 1){
            std::string quest;
            std::cout << "\nIngrese el nombre del .txt\n"
                        << "(No ingrese la terminacion .txt)\n";
            std::cin.clear();
            std::getline(std::cin, quest);
            std::ofstream Questions(quest+".txt", std::ios_base::out | std::ios_base::app);
            Questions << question;
            Questions.close();
        }
        std::cout << question;
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
                dataset.datasets.clear();
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

    //To use in user input and returning calification
    std::string buffer;
    float calif;
    if(questions[no_que].question_type == SIMPLE || questions[no_que].question_type == CALCULATED){
        //Evaluate question already instantiated
        float user_ans;
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
    }
    else{//MULTIPLE Question
        int user_ans;
        do{//Display question and options (Answers)
            std::cout << questions[no_que].question_text << '\n';
            for( int i = 0; i < questions[no_que].answers.size(); i++)
                std::cout << (i+1) << ".\t" << questions[no_que].answers[i].formula << '\n';
            std::cin.clear();
            std::getline(std::cin, buffer);
            std::stringstream(buffer) >> user_ans;
        }while(user_ans < 1 || user_ans > 4);
        //Evaluate User Answer
        //Get the percentage calification for the selected answer 
        //and multiply by the default score in the current question
        user_ans -= 1;
        std::cout << "correcta\n" << "Retroalimentacion Especifica: " <<
                    questions[no_que].answers[user_ans].specific_feedback << '\n';
        calif = (float)(questions[no_que].answers[user_ans].calification)/100*(float)questions[no_que].default_score;
    }
    //Final output for every type of question
    std::cout << "Retroalimentacion General: " << questions[no_que].general_feedback << '\n'
            << "---------------------------------------------------\n\n";
    std::cout << "Su puntuacion para esta pregunta es: " << calif << '\n';
    return calif;
}
//Modularize apply question function

//Creates a dataset and push it to the datasets vector
void Exam::create_dataset(std::string wildcard, int min, int max ){
    Dataset dataset;
    dataset.wildcard = wildcard;
    dataset.moodle_set_generation(min, max);
    dataset.syncronization = OFF;
    dataset.type = PRIVATE;
    datasets.push_back(dataset);
}

void Exam::print_datasets(){
    for(int i = 0; i < datasets.size(); i++)
        datasets[i].print_dataset();
}