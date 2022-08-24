#include "../Database/Database.h"
#include "mysql_connection.h"

int main(){
    sql::Connection *connection {DatabaseSetup()};

    sql::ResultSet *result {RetrieveOpenTickets(connection, 0)};
    if(result -> next()){
        // Here if ResultSet contains - at least - one element.
        return 0;
    }else{
        return 1;
    }
}