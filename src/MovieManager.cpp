#include "MovieManager.h"
#include "MovieConstants.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

static bool readNumber(double& val) {
    cin >> val;
    if (cin.fail()) { cin.clear(); cin.ignore(MovieConstants::INPUT_BUFFER_SIZE, '\n'); return false; }
    cin.ignore(MovieConstants::INPUT_BUFFER_SIZE, '\n');
    return true;
}

bool MovieManager::movieExists(int id) const {
    return movieIndex.count(id) > 0;
}

Movie* MovieManager::findMovie(int id) {
    auto it = movieIndex.find(id);
    if (it == movieIndex.end()) return nullptr;
    return it->second;
}

void MovieManager::addMovie() {
    double id, year;
    string title, genre;

    cout << "영화 ID: ";
    if (!readNumber(id)) return;
    if (movieExists((int)id)) { cout << "이미 존재하는 ID입니다." << endl; return; }

    cout << "제목: ";    getline(cin, title);
    cout << "장르: ";    getline(cin, genre);
    cout << "개봉연도: ";
    if (!readNumber(year)) return;

    movies.push_back(Movie((int)id, title, genre, (int)year));
    movieIndex[movies.back().getId()] = &movies.back();
    cout << "영화가 추가되었습니다." << endl;
}

void MovieManager::searchMovie() const {
    if (movies.empty()) { cout << "등록된 영화가 없습니다." << endl; return; }

    string keyword;
    cout << "검색할 제목: ";
    getline(cin, keyword);

    bool found = false;
    for (const auto& m : movies) {
        if (m.getTitle().find(keyword) != string::npos) {
            cout << m << endl;  // Movie::operator<< 활용
            found = true;
        }
    }
    if (!found) cout << "검색 결과가 없습니다." << endl;
}

void MovieManager::displayAllMovies() const {
    if (movies.empty()) { cout << "등록된 영화가 없습니다." << endl; return; }
    cout << "\n[ 전체 영화 목록 ]" << endl;
    for (const auto& m : movies)
        cout << m << endl;  // Movie::operator<< 활용
}

void MovieManager::sortByRating() const {
    if (movies.empty()) { cout << "등록된 영화가 없습니다." << endl; return; }
    vector<Movie> sorted = movies;
    sort(sorted.begin(), sorted.end());    // Movie::operator< 활용
    reverse(sorted.begin(), sorted.end()); // 내림차순
    cout << "\n[ 평점 높은 순 ]" << endl;
    for (const auto& m : sorted)
        cout << m << endl;
}

void MovieManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) { std::cout << "파일을 열 수 없습니다: " << filename << std::endl; return; }

    std::string line;
    getline(file, line); // 헤더 스킵 (id,title,genre,year,rating)

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        int id, year;
        std::string title, genre;
        getline(ss, token, ','); id    = stoi(token);
        getline(ss, token, ','); title = token;
        getline(ss, token, ','); genre = token;
        getline(ss, token, ','); year  = stoi(token);
        getline(ss, token, ','); // rating 무시
        movies.push_back(Movie(id, title, genre, year));
    }
    // 인덱스 재구성
    movieIndex.clear();
    for (auto& m : movies)
        movieIndex[m.getId()] = &m;
    file.close();
    std::cout << "파일 로드 완료: " << filename << " (" << movies.size() << "건)" << std::endl;
}

void MovieManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) { std::cout << "파일을 열 수 없습니다: " << filename << std::endl; return; }
    file << "id,title,genre,year,rating" << std::endl;
    for (const auto& m : movies)
        file << m.getId() << "," << m.getTitle() << "," << m.getGenre()
             << "," << m.getYear() << "," << m.getAverageRating() << std::endl;
    file.close();
    std::cout << "파일 저장 완료: " << filename << std::endl;
}

int MovieManager::size() const {
    return (int)movies.size();
}