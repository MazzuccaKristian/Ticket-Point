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
 * @return std::string, mail:password format.
 */
std::string CollectUserData(){
    std::string loginDataRecord {""};
    std::string loginDataRecord_temp{""};
    std::cout << "Enter your mail: ";
    std::getline(std::cin >> std::ws, loginDataRecord_temp);
    loginDataRecord = loginDataRecord + loginDataRecord_temp;
    loginDataRecord_temp = {""};
    std::cout << "Enter your password: ";
    std::getline(std::cin, loginDataRecord_temp);
    loginDataRecord = loginDataRecord + ":" + loginDataRecord_temp;
    return loginDataRecord;
}

/**
 * @brief Tokenize login result (as std::string) and create a tuple.
 * 
 * @param loginResultString 
 * @return std::tuple<int userId, std::string mail, std::string name, std::string lastname, std::string password> 
 */
std::tuple<int, std::string, std::string, std::string, std::string> BuildLoginResultTuple_User(std::string loginResultString){
    std::size_t startDelimiter {0};
    std::size_t endDelimiter {loginResultString.find_first_of(':')};
    int userId {std::stoi(loginResultString.substr(startDelimiter, endDelimiter - startDelimiter))};
    startDelimiter = endDelimiter + 1;
    endDelimiter = loginResultString.find_first_of(':', startDelimiter);
    std::string mail {loginResultString.substr(startDelimiter, endDelimiter - startDelimiter)};
    startDelimiter = endDelimiter + 1;
    endDelimiter = loginResultString.find_first_of(':', startDelimiter);
    std::string name {loginResultString.substr(startDelimiter, endDelimiter - startDelimiter)};
    startDelimiter = endDelimiter + 1;
    endDelimiter = loginResultString.find_first_of(':', startDelimiter);
    std::string lastname {loginResultString.substr(startDelimiter, endDelimiter - startDelimiter)};
    startDelimiter = endDelimiter + 1;
    endDelimiter = loginResultString.find_first_of(':', startDelimiter);
    std::string password {loginResultString.substr(startDelimiter, endDelimiter - startDelimiter)};
    return std::make_tuple(userId, mail, name, lastname, password);
}

std::tuple<int, std::string, std::string, std::string, std::string, int> BuildLoginResultTuple_Technician(std::string loginResultString){
    std::size_t startDelimiter {0};
    std::size_t endDelimiter {loginResultString.find_first_of(':')};
    int technicianId {std::stoi(loginResultString.substr(startDelimiter, endDelimiter - startDelimiter))};
    startDelimiter = endDelimiter + 1;
    endDelimiter = loginResultString.find_first_of(':', startDelimiter);
    std::string mail {loginResultString.substr(startDelimiter, endDelimiter - startDelimiter)};
    startDelimiter = endDelimiter + 1;
    endDelimiter = loginResultString.find_first_of(':', startDelimiter);
    std::string name {loginResultString.substr(startDelimiter, endDelimiter - startDelimiter)};
    startDelimiter = endDelimiter + 1;
    endDelimiter = loginResultString.find_first_of(':', startDelimiter);
    std::string lastname {loginResultString.substr(startDelimiter, endDelimiter - startDelimiter)};
    startDelimiter = endDelimiter + 1;
    endDelimiter = loginResultString.find_first_of(':', startDelimiter);
    std::string password {loginResultString.substr(startDelimiter, endDelimiter - startDelimiter)};
    startDelimiter = endDelimiter + 1;
    endDelimiter = loginResultString.find_first_of(':', startDelimiter);
    int skillId {std::stoi(loginResultString.substr(startDelimiter, endDelimiter - startDelimiter))};
    return std::make_tuple(technicianId, mail, name, lastname, password, skillId);
}

/**
 * @brief Collect data and attemp login. Then, return a tuple with user's info.
 * 
 * @param connection 
 * @return std::tuple<int userId, std::string mail, std::string name, std::string lastname, std::string password> 
 */
std::tuple<int, std::string, std::string, std::string, std::string> LoginPhase_User(sql::Connection *connection){
    std::string loginData {""};
    std::string loggedUserData {""};
    bool isLoginValid {false};
    do{
        loginData = CollectUserData();
        loggedUserData = TryLogin(connection, loginData, false);
        if(loggedUserData.compare("-1") != 0){
            isLoginValid = true;
        }else{
            std::cout << "Login failed. Please, try again..." << std::endl;
        }
    }while(!isLoginValid);
    std::tuple<int, std::string, std::string, std::string, std::string> loginResultTuple;
    loginResultTuple = BuildLoginResultTuple_User(loggedUserData);
    return loginResultTuple;
}

/**
 * @brief Collect data and attemp login. Then, return a tuple with user's info.
 * 
 * @param connection 
 * @return std::tuple<int technicianId, std::string mail, std::string name, std::string lastname, std::string password, int skillId> 
 */
std::tuple<int, std::string, std::string, std::string, std::string, int> LoginPhase_Technician(sql::Connection *connection){
    std::string loginData {""};
    std::string loggedUserData {""};
    bool isLoginValid {false};
    do{
        loginData = CollectUserData();
        loggedUserData = TryLogin(connection, loginData, true);
        if(loggedUserData.compare("-1") != 0){
            isLoginValid = true;
        }else{
            std::cout << "Login failed. Please, try again..." << std::endl;
        }
    }while(!isLoginValid);
    std::tuple<int, std::string, std::string, std::string, std::string, int> loginResultTuple;
    loginResultTuple = BuildLoginResultTuple_Technician(loggedUserData);
    return loginResultTuple;
}

void ShowUserMenu(){
    std::cout << "--- USER ---" << std::endl;
    std::cout << "1. Show unresolved tickets;" << std::endl;
    std::cout << "2. Create new ticket;" << std::endl;
    std::cout << "3. Show archive;" << std::endl;
    std::cout << "4. Logout;" << std::endl;
    std::cout << "0. Exit." << std::endl;
}

int getUserChoice(){
    int choice {0};
    bool isChoiceValid {false};
    do{
        std::cout << "Enter your option: ";
        std::cin >> choice;
        if(choice < 0 || choice > 4){
            std::cout << "Option not allowed. Please, try again..." << std::endl;
            isChoiceValid = false;
        }
    }while(!isChoiceValid);
    return choice;
}

void ShowUnresolvedTickets(int userId, sql::Connection *connection){
    sql::ResultSet *ticketSelectionResult {RetrieveOpenTickets(connection, userId)};
}