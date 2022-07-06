#include "main.h"

int main(){
    
    bool isAppWorking{true};

    do{
        ShowLoginMenu(); // Show menu (login)
        int loginChoice = GetLoginChoice(); // Retrieve user's choice (login)
        switch(loginChoice){
            case 0: // Exit
                std::cout << "Program ended. Please, wait..." << std::endl;
                isAppWorking = false;
                break;

            case 1: // Login for 'user'
                //TODO: Login for 'user'
                break;

            case 2: // Login for 'technician'
                //TODO: Login for 'technician'
                break;
        }
    }while(!isAppWorking);

    exit(EXIT_SUCCESS);
}