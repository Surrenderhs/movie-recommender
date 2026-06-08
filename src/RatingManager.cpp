#include "RatingManager.h"
#include "MovieConstants.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const vector<Rating> RatingManager::emptyRatings;  // findByUser 미스 시 반환용

static bool readNumber(double& val) {
    cin >> val;
    if (cin.fail()) { cin.clear(); cin.ignore(MovieConstants::INPUT_BUFFER_SIZE, '\n'); return false; }
    cin.ignore(MovieConstants::INPUT_BUFFER_SIZE, '\n');
    return true;
}

RatingManager::RatingManager()
    : movieManager(nullptr), userManager(nullptr) {}

RatingManager::RatingManager(MovieManager& mm, UserManager& um)
    : movieManager(&mm), userManager(&um) {}

void RatingManager::addRating() {
    if (!movieManager || !userManager) { cout << "매니저가 연결되지 않았습니다." << endl; return; }
    double uId, mId, score;

    cout << "사용자 ID: ";
    if (!readNumber(uId)) return;
    if (!userManager->userExists((int)uId)) { cout << "존재하지 않는 사용자입니다." << endl; return; }

    cout << "영화 ID: ";
    if (!readNumber(mId)) return;
    if (!movieManager->movieExists((int)mId)) { cout << "존재하지 않는 영화입니다." << endl; return; }

    cout << "평점 (" << MovieConstants::MIN_SCORE << " ~ " << MovieConstants::MAX_SCORE << "): ";
    if (!readNumber(score)) return;

    ratings.push_back(Rating((int)uId, (int)mId, score));
    ratingsByUser[(int)uId].push_back(Rating((int)uId, (int)mId, score));

    Movie* movie = movieManager->findMovie((int)mId);
    if (movie) movie->addRating(score);

    cout << "평점이 등록되었습니다." << endl;
}

void RatingManager::displayMovieRatings() const {
    double mId;
    cout << "영화 ID: ";
    if (!readNumber(mId)) return;
    if (!movieManager->movieExists((int)mId)) { cout << "존재하지 않는 영화입니다." << endl; return; }

    Movie* m = movieManager->findMovie((int)mId);
    cout << "\n[ " << m->getTitle() << " | 평균 평점: " << m->getAverageRating() << " | 평점 수: " << m->getRatingCount() << " ]" << endl;

    bool found = false;
    for (const auto& r : ratings) {
        if (r.getMovieId() == (int)mId) {
            cout << "  userId: " << r.getUserId() << " | 평점: " << r.getScore() << endl;
            found = true;
        }
    }
    if (!found) cout << "등록된 평점이 없습니다." << endl;
}

void RatingManager::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "파일을 열 수 없습니다: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // 헤더 스킵 (userId,movieId,score)

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        int userId, movieId;
        double score;

        getline(ss, token, ','); userId  = stoi(token);
        getline(ss, token, ','); movieId = stoi(token);
        getline(ss, token, ','); score   = stod(token);

        ratings.push_back(Rating(userId, movieId, score));
        ratingsByUser[userId].push_back(Rating(userId, movieId, score));

        // Movie 객체에 평점 반영
        if (movieManager) {
            Movie* m = movieManager->findMovie(movieId);
            if (m) m->addRating(score);
        }
    }
    file.close();
    cout << "파일 로드 완료: " << filename << " (" << ratings.size() << "건)" << endl;
}

const vector<Rating>& RatingManager::findByUser(int userId) const {
    auto it = ratingsByUser.find(userId);
    if (it == ratingsByUser.end()) return emptyRatings;
    return it->second;
}

int RatingManager::getRatingCountByUser(int userId) const {
    auto it = ratingsByUser.find(userId);
    if (it == ratingsByUser.end()) return 0;
    return (int)it->second.size();
}

void RatingManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) { std::cout << "파일을 열 수 없습니다: " << filename << std::endl; return; }
    file << "userId,movieId,score" << std::endl;
    for (const auto& r : ratings)
        file << r.getUserId() << "," << r.getMovieId() << "," << r.getScore() << std::endl;
    file.close();
    std::cout << "파일 저장 완료: " << filename << std::endl;
}

int RatingManager::size() const {
    return (int)ratings.size();
}