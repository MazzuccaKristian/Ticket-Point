#include "Person.h"

Person::Person(int id, std::string mail, std::string name, std::string lastname, std::string password){
    person_id = id;
    person_mail = mail;
    person_name = name;
    person_lastname = lastname;
    person_password = password;
}

int Person::getId(){
    return this -> person_id;
}

std::string Person::getMail(){
    return this -> person_mail;
}

std::string Person::getName(){
    return this -> person_name;
}

std::string Person::getLastname(){
    return this -> person_lastname;
}

std::string Person::getPassword(){
    return this -> person_password;
}