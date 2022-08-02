#include <iostream>

#include "mysql_connection.h"
#include "Database/Database.h"
#include "Utils/Utils.h"

int main(){

    sql::Connection *connection = DatabaseSetup(); // Test and connect to DB.

    bool isAppWorking {true};
    std::string userDataRecord {""};
    std::string loginData{""};
    std::string loggedUserData{""};

    do{
        ShowMainMenu();
        int userChoice {GetLoginChoice()};
        switch(userChoice){
            case 0: // EXIT
            {
                std::cout << "Program ended. Please, wait..." << std::endl;
                isAppWorking = false;
                delete connection;
                break;
            }
            case 1: // Login for 'user'
            {
                loginData = CollectUserData();
                loggedUserData = TryLogin(connection, loginData); //ID:Name:password
                //TODO: create new User from loggedUserData
                break;
            }
            case 2: // Login for 'technician'
            {
                loginData = CollectUserData();
                break;
            }
        }
    }while(isAppWorking);

    return EXIT_SUCCESS;
}