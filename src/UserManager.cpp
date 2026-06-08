#include "UserManager.h"
#include "MovieConstants.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

static bool readNumber(double& val) {
    cin >> val;
    if (cin.fail()) { cin.clear(); cin.ignore(MovieConstants::INPUT_BUFFER_SIZE, '\n'); return false; }
    cin.ignore(MovieConstants::INPUT_BUFFER_SIZE, '\n');
    return true;
}

bool UserManager::userExists(int id) const {
    for (const auto& u : users)
        if (u == id) return true;  // User::operator==(int) 활용
    return false;
}

void UserManager::addUser() {
    double id;
    string name, email;

    cout << "사용자 ID: ";
    if (!readNumber(id)) return;
    if (userExists((int)id)) { cout << "이미 존재하는 ID입니다." << endl; return; }

    cout << "이름: ";   getline(cin, name);
    cout << "이메일: "; getline(cin, email);

    users.push_back(User((int)id, name, email));
    cout << "사용자가 추가되었습니다." << endl;
}

void UserManager::displayAllUsers() const {
    if (users.empty()) { cout << "등록된 사용자가 없습니다." << endl; return; }
    cout << "\n[ 전체 사용자 목록 ]" << endl;
    for (const auto& u : users)
        cout << u << endl;
}

void UserManager::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) { cout << "파일을 열 수 없습니다: " << filename << endl; return; }

    string line;
    getline(file, line); // 헤더 스킵

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        int id;
        string name;
        getline(ss, token, ','); id   = stoi(token);
        getline(ss, token, ','); name = token;
        getline(ss, token, ','); // age 무시
        users.push_back(User(id, name, ""));
    }
    file.close();
    cout << "파일 로드 완료: " << filename << " (" << users.size() << "건)" << endl;
}

void UserManager::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) { cout << "파일을 열 수 없습니다: " << filename << endl; return; }
    file << "id,name,email" << endl;
    for (const auto& u : users)
        file << u.getId() << "," << u.getName() << "," << u.getEmail() << endl;
    file.close();
    cout << "파일 저장 완료: " << filename << endl;
}

int UserManager::size() const {
    return (int)users.size();
}

vector<User> UserManager::getAllUsers() const {
    return users;
}

User* UserManager::findUserById(int id) {
    for (auto& u : users)
        if (u == id) return &u;
    return nullptr;
}