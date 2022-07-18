#include "DB_Handler.h"

// Credentials for DB.
//TODO: possible encryption/hash
std::string DB_HOST = "tcp://127.0.0.1:3306";
std::string DB_USER = "ticketpoint_user";
std::string DB_PASSWORD = "T!cketPo1ntPassword";
std::string DB_SCHEMA = "TicketPoint_DB";
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