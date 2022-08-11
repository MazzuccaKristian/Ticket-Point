#include "Technician.h"

Technician::Technician(int id, std::string mail, std::string name, std::string lastname, std::string password, int skillId) : Person(id, mail, name, lastname, password){
    Technician_skillId = skillId;
}