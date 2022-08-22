#include "../Database/Database.h"
#include "mysql_connection.h"

int main(){
    sql::Connection *connection {DatabaseSetup()};
    if(connection -> isValid()){
        return 0;
    }else{
        return 1;
    }
}