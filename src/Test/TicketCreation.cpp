#include "../Database/Database.h"
#include "mysql_connection.h"

int main(){
    sql::Connection *connection {DatabaseSetup()};

    std::tuple<int, std::string> ticket {std::make_tuple<int, std::string>(0, "CTEST...OK")};

    bool creationResult = CreateNewTicket(connection, ticket);
    if(creationResult){
        exit(EXIT_SUCCESS);
    }else{
        exit(EXIT_FAILURE);
    }
}