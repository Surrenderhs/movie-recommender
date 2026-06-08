#pragma once
#include <string>
#include <iostream>
using namespace std;

class User {
private:
    int id; 
    string name;
    string email;

public:
    User();
    User(int i,string n,string e);
    int getId() const;
    string getName() const;
    string getEmail() const;
    void display() const;
    bool operator==(int targetId) const;
    friend std::ostream& operator<<(std::ostream& os, const User& user);


};