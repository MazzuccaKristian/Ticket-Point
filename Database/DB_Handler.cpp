#include "DB_Handler.h"

// Credentials for DB.
//TODO: possible encryption/hash
std::string DB_HOST = "tcp://127.0.0.1:3306";
std::string DB_USER = "root";
std::string DB_PASSWORD = "Devod1ment1cart!";
std::string DB_SCHEMA = "TicketPoint_DB";
//

void inline PrintError(sql::SQLException *exception){
    std::cout << "MYSQL ERROR:" << std::endl;
    std::cout << exception -> what();
    std::cout << " (MySQL error code: " << exception -> getErrorCode();
    std::cout << ", SQLState: " << exception -> getSQLState() << " )" << std::endl;
}

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
        PrintError(&exception);
        //! Can't recover, EXIT...
        exit(EXIT_FAILURE);
    }
    return connection;
}

void tryLogin_mockup(sql::Connection *connection, std::string userData){
    //TODO: userData must be tokenized!
    if(connection -> isValid()){
    }
}