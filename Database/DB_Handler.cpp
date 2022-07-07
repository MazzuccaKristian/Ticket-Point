#include "DB_Handler.h"

// PLACEHOLDERS...
std::string DB_HOST = "tcp://127.0.0.1:3306";
std::string DB_USER = "ticketpointuser";
std::string DB_PASSWORD = "TicketPoint";
std::string DB_SCHEMA = "ticketpoint";
//

sql::Connection* DB_Setup(){
    sql::Connection *connection;
    sql::Driver *driver;
    try{
        driver = get_driver_instance();
        connection = driver -> connect(DB_HOST, DB_USER, DB_PASSWORD);
        if(connection -> isValid()){
            connection -> setSchema(DB_SCHEMA);
        }
    }catch(sql::SQLException &exception){
        std::cout << "MYSQL ERROR (CONNECTION):" << std::endl;
        std::cout << exception.what();
        std::cout << " (MySQL error code: " << exception.getErrorCode();
        std::cout << ", SQLState: " << exception.getSQLState() << " )" << std::endl;
        //! Can't recover, EXIT...
        exit(EXIT_FAILURE);
    }
    return connection;
}