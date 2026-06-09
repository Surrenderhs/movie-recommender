#include "Statistics.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
using namespace std;

Statistics::Statistics(const MovieManager& mm, const RatingManager& rm, const UserManager& um)
    : movieManager(mm), ratingManager(rm), userManager(um) {}

void Statistics::display() const {
    int choice;
    while (true) {
        cout << "\n[ 통계 메뉴 ]" << endl;
        cout << "1. 전체 현황" << endl;
        cout << "2. 장르별 현황" << endl;
        cout << "3. 유저별 평점 수 랭킹" << endl;
        cout << "4. 평점 높은 영화 Top 5" << endl;
        cout << "0. 돌아가기" << endl;
        cout << "선택: ";
        cin >> choice;
        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        cin.ignore(1000, '\n');

        if (choice == 0) break;
        switch (choice) {
            case 1: displayOverall();     break;
            case 2: displayByGenre();     break;
            case 3: displayUserRanking(); break;
            case 4: displayTopMovies();   break;
            default: cout << "잘못된 입력입니다." << endl;
        }
    }
}

void Statistics::displayOverall() const {
    if (ratingManager.size() == 0) { cout << "\n등록된 평점이 없습니다." << endl; return; }

    const auto& users = userManager.getAllUsers();
    double scoreSum = 0.0;
    int    scoreCount = 0;
    for (const auto& u : users) {
        for (const auto& r : ratingManager.findByUser(u.getId())) {
            scoreSum += r.getScore();
            scoreCount++;
        }
    }

    cout << "\n[ 전체 현황 ]" << endl;
    cout << "  총 평점 수    : " << scoreCount << "개" << endl;
    if (scoreCount > 0)
        cout << fixed << setprecision(2)
             << "  전체 평균 평점: " << scoreSum / scoreCount << "점" << endl;
}

void Statistics::displayByGenre() const {
    map<string, int>              movieCount;
    map<string, pair<double,int>> ratingSum;

    for (const auto& m : movieManager.getMovies()) {
        movieCount[m.getGenre()]++;
        if (m.getRatingCount() > 0) {
            ratingSum[m.getGenre()].first  += m.getAverageRating() * m.getRatingCount();
            ratingSum[m.getGenre()].second += m.getRatingCount();
        }
    }

    // map → vector로 변환 후 영화 수 내림차순 정렬
    vector<pair<string,int>> genreList(movieCount.begin(), movieCount.end());
    sort(genreList.begin(), genreList.end(),
         [](const auto& a, const auto& b){ return a.second > b.second; });

    cout << "\n[ 장르별 현황 ]" << endl;
    cout << "  " << "장르            " << "영화 수  " << "평균 평점" << endl;
    cout << "  " << string(34, '-') << endl;

    for (const auto& [genre, cnt] : genreList) {
        double avg = 0.0;
        auto it = ratingSum.find(genre);
        if (it != ratingSum.end() && it->second.second > 0)
            avg = it->second.first / it->second.second;

        // 한글(3바이트)과 영문(1바이트) 혼용 처리
        int byteLen = (int)genre.size();
        int koreanChars = 0;
        for (int i = 0; i < byteLen; ) {
            unsigned char c = genre[i];
            if (c >= 0xE0) { koreanChars++; i += 3; }  // UTF-8 한글
            else i++;
        }
        int asciiChars = byteLen - koreanChars * 3;
        int displayWidth = koreanChars * 2 + asciiChars;  // 한글=2칸, 영문=1칸
        int padNeeded = 12 - displayWidth;
        string genreCol = genre + string(padNeeded > 0 ? padNeeded : 1, ' ');

        string cntCol = to_string(cnt) + "편";
        cntCol += string(4, ' ');

        cout << fixed << setprecision(2)
             << "  " << genreCol << cntCol
             << (avg > 0 ? to_string(avg).substr(0,4) + "점" : "-") << endl;
    }
}

void Statistics::displayTopMovies() const {
    const auto& allMovies = movieManager.getMovies();

    // 평점 수 1개 이상인 영화만 추출
    vector<pair<double, const Movie*>> rated;
    for (const auto& m : allMovies)
        if (m.getRatingCount() > 0)
            rated.push_back({m.getAverageRating(), &m});

    if (rated.empty()) { cout << "\n평점이 등록된 영화가 없습니다." << endl; return; }

    sort(rated.begin(), rated.end(),
         [](const auto& a, const auto& b){ return a.first > b.first; });

    int top = min(5, (int)rated.size());
    cout << "\n[ 평점 높은 영화 Top " << top << " ]" << endl;
    for (int i = 0; i < top; i++) {
        const Movie* m = rated[i].second;
        string rank = to_string(i+1) + "위";
        cout << fixed << setprecision(2)
             << "  " << left << setw(6) << rank
             << left << setw(28) << m->getTitle()
             << "| " << m->getGenre()
             << " | 평점: " << m->getAverageRating() << endl;
    }
}

void Statistics::displayUserRanking() const {
    vector<pair<string,int>> ranking;
    for (const auto& u : userManager.getAllUsers())
        ranking.push_back({u.getName(), ratingManager.getRatingCountByUser(u.getId())});

    sort(ranking.begin(), ranking.end(),
         [](const auto& a, const auto& b){ return a.second > b.second; });

    cout << "\n[ 유저별 평점 수 랭킹 ]" << endl;
    for (int i = 0; i < (int)ranking.size(); i++) {
        string rank = to_string(i+1) + "위";
        cout << "  " << left << setw(6) << rank
             << left << setw(12) << ranking[i].first
             << "— " << ranking[i].second << "개" << endl;
    }
}