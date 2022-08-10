#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "mysql_connection.h"
#include "../Database/Database.h"

void ShowMainMenu();
int GetLoginChoice();
std::string CollectUserData();
std::tuple<int, std::string, std::string, std::string, std::string> BuildLoginResultTuple(std::string loginResultString);
std::tuple<int, std::string, std::string, std::string, std::string> LoginPhase(sql::Connection *connection);

#endif