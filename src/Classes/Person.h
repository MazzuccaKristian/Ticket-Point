#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person{
    private:
        int person_id;
        std::string person_username, person_password;

    public:
        Person(int id, std::string username, std::string password);
};


#endif