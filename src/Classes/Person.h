#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person{
    private:
        int person_id;
        std::string person_mail, person_name, person_lastname, person_password;

    public:
        Person(int id, std::string mail, std::string name, std::string lastname, std::string password);
        int getId();
        std::string getMail();
        std::string getName();
        std::string getLastname();
        std::string getPassword();
};


#endif