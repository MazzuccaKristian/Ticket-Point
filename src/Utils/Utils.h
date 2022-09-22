#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "mysql_connection.h"
#include "../Database/Database.h"

void ShowMainMenu();
int GetLoginChoice();
std::string CollectUserData();
std::tuple<int, std::string, std::string, std::string, std::string> LoginPhase_User(sql::Connection *connection);
std::tuple<int, std::string, std::string, std::string, std::string, int> LoginPhase_Technician(sql::Connection *connection);
std::tuple<int, std::string, std::string, std::string, std::string> BuildLoginResultTuple_User(std::string loginResultString);
std::tuple<int, std::string, std::string, std::string, std::string, int> BuildLoginResultTuple_Technician(std::string loginResultString);
void ShowUserMenu();
void ShowTechnicianMenu();
int getUserChoice();
void ShowUnresolvedTickets(sql::Connection *connection, int userId);
void OpenNewTicket(sql::Connection *connection, int userId);
void ShowArchive(sql::Connection *connection, int userId);
void ShowFormattedPool(sql::ResultSet *rawPool);

#endif