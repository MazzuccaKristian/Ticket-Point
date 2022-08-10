#include <iostream>

#include "mysql_connection.h"
#include "Database/Database.h"
#include "Utils/Utils.h"
#include "Classes/Person.h"
#include "Classes/User.h"
#include "Classes/Technician.h"

int main(){

    sql::Connection *connection = DatabaseSetup(); // Test and connect to DB.

    bool isAppWorking {true};
    std::string userDataRecord {""};
    std::string loginData{""};
    std::string loggedUserData{""}; //TODO: unnecessary (still here for prototype of login for Technician)
    std::tuple<int, std::string, std::string, std::string, std::string> loggedUserTuple;

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
                loggedUserTuple = LoginPhase(connection);
                break;
            }
            case 2: // Login for 'technician'
            {
                loginData = CollectUserData();
                loggedUserData = TryLogin(connection, loginData); //ID:Name:password
                //! Check for success
                int id {std::stoi(loggedUserData.substr(0, loggedUserData.find_first_of(':')))};
                std::string username {loggedUserData.substr(loggedUserData.find_first_of(':')+1, loggedUserData.find_last_of(':')-2)};
                std::string password {loggedUserData.substr(loggedUserData.find_last_of(':')+1)};
                // Technician technician(id, username, password);
                break;
            }
        }
    }while(isAppWorking);

    return EXIT_SUCCESS;
}