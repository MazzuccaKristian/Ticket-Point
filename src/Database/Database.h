#ifndef DATABASE_H
#define DATABASE_H

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>

const std::string DB_HOST {"tcp://127.0.0.1:3306"};
const std::string DB_USER {"ticketpoint_user"};
const std::string DB_PASSWORD {"T!cketPointP4ssword"};
const std::string DB_SCHEMA {"TicketPoint_DB"};

const std::string loginQuery {"SELECT * FROM User WHERE mail = ? AND password = ? and isTechnician = ?"};

sql::Connection *DatabaseSetup();
std::string TryLogin(sql::Connection *connection, const std::string loginRecord, bool isTechnician = false);
std::string BuildReturnString(sql::ResultSet *loginResult);

#endif