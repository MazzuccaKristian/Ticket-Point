#include "Utils.h"

void ShowMainMenu(){
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

/**
 * @brief Collect username and password from user for login.
 * 
 * @return std::string, username:password format.
 */
std::string CollectUserData(){
    std::string loginDataRecord {""};
    std::string loginDataRecord_temp{""};
    std::cout << "Enter your username: ";
    std::getline(std::cin >> std::ws, loginDataRecord_temp);
    loginDataRecord = loginDataRecord + loginDataRecord_temp;
    loginDataRecord_temp = {""};
    std::cout << "Enter your password: ";
    std::getline(std::cin, loginDataRecord_temp);
    loginDataRecord = loginDataRecord + ":" + loginDataRecord_temp;
    return loginDataRecord;
}