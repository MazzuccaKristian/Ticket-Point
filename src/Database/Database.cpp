#include "Database.h"

sql::Connection *DatabaseSetup(){
    sql::Connection *connection;
    try{
        sql::Driver *driver = get_driver_instance();
        connection = driver -> connect(DB_HOST, DB_USER, DB_PASSWORD);
        if(connection -> isValid()){
            connection -> setSchema(DB_SCHEMA);
        }
    }catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__ << std::endl;
        std::cout << "# ERR: " << e.what() << std::endl;
        std::cout << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        exit(EXIT_FAILURE); //! FORCE EXIT
    }
    return connection;
}

std::string TryLogin(sql::Connection *connection, const std::string loginRecord){
    if(!connection -> isValid()){
        std::cout << "Connection lost..." << std::endl;
        exit(EXIT_FAILURE);
    }
    const std::string username {loginRecord.substr(0, loginRecord.find_first_of(':'))};
    const std::string password {loginRecord.substr(loginRecord.find_first_of(':') + 1, loginRecord.length())};
    sql::PreparedStatement *loginStatement;
    std::string result {""};
    try{
        loginStatement = connection -> prepareStatement(loginQuery);
        loginStatement -> setString(1, username);
        loginStatement -> setString(2, password);
        sql::ResultSet *loginResult = loginStatement -> executeQuery();
        if(loginResult -> next()){
            result = (std::to_string(loginResult -> getInt("Id"))) + ":" + (loginResult -> getString("Name")) + ":" + (loginResult -> getString("Password"));
        }
        delete loginResult;
    }catch(sql::SQLException &e){
        std::cout << "# ERR: SQLException in " << __FILE__ << std::endl;
        std::cout << "# ERR: " << e.what() << std::endl;
        std::cout << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
    delete loginStatement;
    return result;
}