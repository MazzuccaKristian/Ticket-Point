#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include "mysql_connection.h"
#include "Database/DB_Handler.h"

void ShowLoginMenu();
int GetLoginChoice();
void CollectUserData(std::string *dataCollection);

#endif