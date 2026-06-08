#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "User.h"
#include "BaseManager.h"

class UserManager : public BaseManager {
private:
    std::vector<User> users;
    std::unordered_map<int, User*> userIndex;  // id → User* 인덱스

public:
    void addUser();
    void displayAllUsers() const;
    bool userExists(int id) const;
    const std::vector<User>& getAllUsers() const;  // 복사 → 참조 반환
    User* findUserById(int id);

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};