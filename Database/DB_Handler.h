#ifndef DB_HANDLER_H
#define DB_HANDLER_H

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>

sql::Connection* DB_Setup();

#endif