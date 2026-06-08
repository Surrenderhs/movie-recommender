#include "User.h"
#include <iostream>
using namespace std;

User::User()
    :id(0),name("Default"),email("Defaultmail@gmail.com"){}

User::User(int i,string n,string e)
    :id(i),name(n),email(e) {}


int User::getId() const{
    return id;
}

string User::getName() const{
    return name;
}

string User::getEmail() const{
    return email;
}

bool User::operator==(int targetId) const {
    return id == targetId;
}

ostream& operator<<(ostream& os, const User& user) {
    os << "[" << user.id << "] " << user.name << " | 이메일: " << user.email;
    return os;
}

void User::display() const{
    cout<<"user Id: "<<id
    <<" name: "<<name
    <<" email: "<<email<<endl;
}