#include "main.h"

void inline ShowLoginMenu(){
    std::cout << "--- LOGIN ---" << std::endl;
    std::cout << "1. User;" << std::endl;
    std::cout << "2. Technician;" << std::endl;
    std::cout << "0. Exit." << std::endl; 
}

int GetLoginChoice(){
    int choice{0};
    bool isValid{true};
    do{
        std::cout << "Enter your option: ";
        std::cin >> choice;
        if(choice < 0 || choice > 2){
            std::cout << "Option not allowed. Please, try again..." << std::endl;
            isValid = false;
        }
    }while(!isValid);
    return choice;
}

int main(){

    sql::Connection* DB_connection = DB_Setup(); // Connect to DB
    
    bool isAppWorking{true};

    do{
        ShowLoginMenu(); // Show menu (login)
        int loginChoice = GetLoginChoice(); // Retrieve user's choice (login)
        switch(loginChoice){
            case 0: // Exit
                std::cout << "Program ended. Please, wait..." << std::endl;
                isAppWorking = false;
                delete DB_connection;
                break;

            case 1: // Login for 'user'
                //TODO: Login for 'user'
                break;

            case 2: // Login for 'technician'
                //TODO: Login for 'technician'
                break;
        }
    }while(isAppWorking);

    exit(EXIT_SUCCESS);
}