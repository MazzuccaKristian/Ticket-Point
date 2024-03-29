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
        exit(EXIT_FAILURE); //! FORCED EXIT
    }
    return connection;
}

/**
 * @brief Login phase: extract mail and password; setup params for LoginQuery; attempt login.
 * 
 * @param connection 
 * @param loginRecord mail:password format.
 * @return std::string - userId:mail:name:lastname:password:skillId:isTechnician
 */
std::string TryLogin(sql::Connection *connection, const std::string loginRecord, bool isTechnician){
    if(!connection -> isValid()){
        std::cout << "Connection lost..." << std::endl;
        exit(EXIT_FAILURE);
    }
    const std::string mail {loginRecord.substr(0, loginRecord.find_first_of(':'))};
    const std::string password {loginRecord.substr(loginRecord.find_first_of(':') + 1, loginRecord.length())};
    int technicianFlag {0};
    if(isTechnician){
        technicianFlag = 1;
    }
    sql::PreparedStatement *loginStatement;
    std::string result {""};
    try{
        loginStatement = connection -> prepareStatement(loginQuery);
        loginStatement -> setString(1, mail);
        loginStatement -> setString(2, password);
        loginStatement -> setInt(3, technicianFlag);
        sql::ResultSet *loginResult = loginStatement -> executeQuery();
        if(loginResult -> next()){
            result = BuildReturnString(loginResult);
        }else{
            result = "-1";
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

/**
 * @brief Build a formatted string with user's data.
 * 
 * @param loginResult 
 * @return std::string - userId:mail:name:lastname:password:skillId:isTechnician
 */
std::string BuildReturnString(sql::ResultSet *loginResult){
    std::string userInfo {""};
    userInfo.append(std::to_string(loginResult -> getInt("userId")));
    userInfo.append(":");
    userInfo.append(loginResult -> getString("mail"));
    userInfo.append(":");
    userInfo.append(loginResult -> getString("name"));
    userInfo.append(":");
    userInfo.append(loginResult -> getString("lastname"));
    userInfo.append(":");
    userInfo.append(loginResult -> getString("password"));
    userInfo.append(":");
    userInfo.append(std::to_string(loginResult -> getInt("skillId")));
    userInfo.append(":");
    userInfo.append(std::to_string(loginResult -> getInt("isTechnician")));
    return userInfo;
}

/**
 * @brief Select logged user's tickets.
 * 
 * @param connection 
 * @param userId 
 * @return sql::ResultSet* - ResultSet's "Raw format"
 */
sql::ResultSet *RetrieveOpenTickets(sql::Connection *connection, int userId){
    if(!connection -> isValid()){
        std::cout << "Connection lost..." << std::endl;
        exit(EXIT_FAILURE);
    }
    sql::ResultSet *ticketsSelectionResult;
    sql::PreparedStatement *ticketsSelectionStatement;
    try{
        ticketsSelectionStatement = connection -> prepareStatement(ticketSelectionQuery);
        ticketsSelectionStatement -> setInt(1, userId);
        ticketsSelectionResult = ticketsSelectionStatement -> executeQuery();
    }catch(sql::SQLException &e){
        std::cout << "# ERR: SQLException in " << __FILE__ << std::endl;
        std::cout << "# ERR: " << e.what() << std::endl;
        std::cout << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
    delete ticketsSelectionStatement;
    return ticketsSelectionResult;
}

/**
 * @brief Create new ticket.
 * 
 * @param connection 
 * @param ticket std::tuple<int userId, std::string ticketText>
 * @return true when ticket has been created.
 * @return false when creation operation fails.
 */
bool CreateNewTicket(sql::Connection *connection, std::tuple<int, std::string> ticket){
    if(!connection -> isValid()){
        std::cout << "Connection lost..." << std::endl;
        exit(EXIT_FAILURE);
    }
    sql::PreparedStatement *ticketCreationStatement;
    bool querySuccess {false};
    try{
        ticketCreationStatement = connection -> prepareStatement(ticketCreationQuery);
        ticketCreationStatement -> setString(1, std::get<1>(ticket));
        ticketCreationStatement -> setInt(2, 0);
        ticketCreationStatement -> setInt(3, std::get<0>(ticket));
        if(!ticketCreationStatement -> execute()){
            querySuccess = true;
        }
    }catch(sql::SQLException &e){
        std::cout << "# ERR: SQLException in " << __FILE__ << std::endl;
        std::cout << "# ERR: " << e.what() << std::endl;
        std::cout << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
    delete ticketCreationStatement;
    return querySuccess;
}

/**
 * @brief Get "closed" tickets for specified user.
 * 
 * @param connection 
 * @param userId 
 * @return sql::ResultSet* - Set of "closed" tickets (raw)
 */
sql::ResultSet *RetrieveArchive(sql::Connection *connection, int userId){
    if(!connection -> isValid()){
        std::cout << "Connection lost..." << std::endl;
        exit(EXIT_FAILURE);
    }
    sql::ResultSet *archiveResult;
    sql::PreparedStatement *archiveSelectionStatement;
    try{
        archiveSelectionStatement = connection -> prepareStatement(archiveSelectionQuery);
        archiveSelectionStatement -> setInt(1, userId);
        archiveResult = archiveSelectionStatement -> executeQuery();
    }catch(sql::SQLException &e){
        std::cout << "# ERR: SQLException in " << __FILE__ << std::endl;
        std::cout << "# ERR: " << e.what() << std::endl;
        std::cout << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
    delete archiveSelectionStatement;
    return archiveResult;
}

sql::ResultSet *ShowPool(sql::Connection *connection, int userId){
    if(!connection -> isValid()){
        std::cout << "Connection lost..." << std::endl;
        exit(EXIT_FAILURE);
    }
    sql::ResultSet *pool;
    sql::PreparedStatement *poolSelectionStatement;
    try{
        poolSelectionStatement = connection -> prepareStatement(poolSelectionQuery);
        pool = poolSelectionStatement -> executeQuery();
    }catch(sql::SQLException &e){
        std::cout << "# ERR: SQLException in " << __FILE__ << std::endl;
        std::cout << "# ERR: " << e.what() << std::endl;
        std::cout << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
    delete poolSelectionStatement;
    return pool;
}