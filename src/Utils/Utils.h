#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "mysql_connection.h"
#include "../Database/Database.h"

void ShowMainMenu();
int GetLoginChoice();
std::string CollectUserData();
std::tuple<int, std::string, std::string, std::string, std::string> LoginPhase_User(sql::Connection *connection);
std::tuple<int, std::string, std::string, std::string, std::string, std::string, std::string> LoginPhase_Technician(sql::Connection *connection);
std::tuple<int, std::string, std::string, std::string, std::string> BuildLoginResultTuple_User(std::string loginResultString);
std::tuple<int, std::string, std::string, std::string, std::string, std::string, std::string> BuildLoginResultTuple_Technician(std::string loginResulString);
void ShowUserMenu();

#endif