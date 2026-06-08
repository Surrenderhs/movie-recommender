#pragma once
#include <vector>
#include <string>
#include "User.h"
#include "BaseManager.h"

class UserManager : public BaseManager {
private:
    std::vector<User> users;

public:
    void addUser();
    void displayAllUsers() const;
    bool userExists(int id) const;
    std::vector<User> getAllUsers() const;
    User* findUserById(int id);

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};