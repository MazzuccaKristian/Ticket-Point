#ifndef TECHNICIAN_H
#define TECHNICIAN_H

#include "Person.h"

class Technician : public Person{
    private:
        int Technician_skillId;

    public:
        Technician(int id, std::string mail, std::string name, std::string lastname, std::string password, int skillId);
};

#endif