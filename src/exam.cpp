#include "../include/exam.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMMENTS SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Note: Implement an exit option later below line 14


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
            << "3." << "\t" << "Previsualizar pregunta" << "\n"
            << "4." << "\t" << "Aplicar examen" << "\n"
            << "5." << "\t" << "Visualizar configuracion actual" << "\n";
    std::cin.clear();
    std::getline(std::cin, buffer);
    std::stringstream(buffer) >> agregar_editar;
    if(agregar_editar < 0 || agregar_editar > 5){
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
        for(int i = 0; i < questions.size(); i++){
            calification += questions[i].apply_question();
        }
        calification/questions.size();
    }
}