#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include "Person.h"

class User : public Person{
    public:
        User(int id, std::string mail, std::string name, std::string lastname, std::string password);
};

#endif