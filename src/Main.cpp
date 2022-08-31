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
                bool isUserLogged {false};
                loggedUserTuple = LoginPhase_User(connection);
                User loggedUser (std::get<0>(loggedUserTuple),
                                std::get<1>(loggedUserTuple),
                                std::get<2>(loggedUserTuple),
                                std::get<3>(loggedUserTuple),
                                std::get<4>(loggedUserTuple));
                std::cout << "Welcome back, " << loggedUser.getName() << std::endl;
                if(&loggedUser != nullptr){ // check existence of User object.
                    isUserLogged = true; 
                }
                while(isUserLogged){
                    ShowUserMenu();
                    int userChoice {getUserChoice()};
                    switch(userChoice){
                        case 0:
                        {
                            std::cout << "Program ended. Please, wait..." << std::endl;
                            isAppWorking = false;
                            delete connection;
                            exit(EXIT_SUCCESS);
                        }
                        case 1:
                        {
                            ShowUnresolvedTickets(connection, loggedUser.getId());
                            break;
                        }
                        case 2:
                        {
                            OpenNewTicket(connection, loggedUser.getId());
                            break;
                        }
                        case 3:
                        {
                            ShowArchive(connection, loggedUser.getId());
                            break;
                        }
                        case 4:
                        {
                            std::cout << "Logout..." << std::endl;
                            loggedUser.~User();
                            isUserLogged = false;
                        }
                    }
                }
                break;
            }
            case 2: // Login for 'technician'
            {
                bool isTechnicianLogged {false};
                loggedTechnicianTuple = LoginPhase_Technician(connection);
                Technician loggedTechnician(std::get<0>(loggedTechnicianTuple),
                                            std::get<1>(loggedTechnicianTuple),
                                            std::get<2>(loggedTechnicianTuple),
                                            std::get<3>(loggedTechnicianTuple),
                                            std::get<4>(loggedTechnicianTuple),
                                            std::get<5>(loggedTechnicianTuple));
                if(&loggedTechnician != nullptr){
                    isTechnicianLogged = true;
                }
                std::cout << "Welcome back, " << loggedTechnician.getName() << std::endl;
                while(isTechnicianLogged){
                    ShowTechnicianMenu();
                    int technicianChoice {getUserChoice()};
                    switch(technicianChoice){
                        case 0:
                        {
                            std::cout << "Program ended. Please, wait..." << std::endl;
                            isAppWorking = false;
                            delete connection;
                            exit(EXIT_SUCCESS);
                        }
                    }
                }
                break;
            }
        }
    }while(isAppWorking);

    return EXIT_SUCCESS;
}