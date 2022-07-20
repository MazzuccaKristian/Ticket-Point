#ifndef DB_HANDLER_H
#define DB_HANDLER_H

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

void inline PrintError(sql::SQLException *exception);
sql::Connection* DB_Setup();
void tryLogin_mockup(sql::Connection *connection, std::string userData);

#endif