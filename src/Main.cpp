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
    std::tuple<int, std::string, std::string, std::string, std::string, int> loggedTechnicianTuple;

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
                loggedUserTuple = LoginPhase_User(connection);
                User loggedUser (std::get<0>(loggedUserTuple),
                                std::get<1>(loggedUserTuple),
                                std::get<2>(loggedUserTuple),
                                std::get<3>(loggedUserTuple),
                                std::get<4>(loggedUserTuple));
                std::cout << "Welcome back, " << loggedUser.getName() << std::endl;
                ShowUserMenu();
                int userChoice {getUserChoice()};
                switch(userChoice){
                    case 0:
                    {
                        std::cout << "Program ended. Please, wait..." << std::endl;
                        isAppWorking = false;
                        delete connection;
                        break;
                    }
                    case 1:
                    {
                        ShowUnresolvedTickets(connection, loggedUser.getId());
                    }
                }
                break;
            }
            case 2: // Login for 'technician'
            {
                loggedTechnicianTuple = LoginPhase_Technician(connection);
                Technician loggedTechnician(std::get<0>(loggedTechnicianTuple),
                                            std::get<1>(loggedTechnicianTuple),
                                            std::get<2>(loggedTechnicianTuple),
                                            std::get<3>(loggedTechnicianTuple),
                                            std::get<4>(loggedTechnicianTuple),
                                            std::get<5>(loggedTechnicianTuple));
                std::cout << "Welcome back, " << loggedTechnician.getName() << std::endl;
                break;
            }
        }
    }while(isAppWorking);

    return EXIT_SUCCESS;
}