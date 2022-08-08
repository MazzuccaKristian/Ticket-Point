#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include "Person.h"

class User : private Person{
    public:
        User(int id, std::string username, std::string password);
};

#endif