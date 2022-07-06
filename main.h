#ifndef MAIN_H
#define MAIN_H
#include <iostream>

void ShowLoginMenu();
int GetLoginChoice();

void ShowLoginMenu(){
    std::cout << "--- LOGIN ---" << std::endl;
    std::cout << "1. User;" << std::endl;
    std::cout << "2. Technician;" << std::endl;
    std::cout << "0. Exit." << std::endl; 
}

int GetLoginChoice(){
    int choice{0};
    bool isValid{true};
    do{
    std::cout << "Enter your option: ";
    std::cin >> choice;
    if(choice < 0 || choice > 2){
        std::cout << "Option not allowed. Please, try again..." << std::endl;
        isValid = false;
    }
    }while(!isValid);
    return choice;
}

#endif