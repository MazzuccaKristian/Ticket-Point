#ifndef TECHNICIAN_H
#define TECHNICIAN_H

#include "Person.h"

class Technician : private Person{
    public:
        Technician(int id, std::string username, std::string password);
};

#endif