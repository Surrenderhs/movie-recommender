#include <iostream>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "Recommender.h"
#include "MovieConstants.h"
using namespace std;

int main() {
    MovieManager mm;
    UserManager um;
    RatingManager rm(mm, um);

    // CSV에서 초기 데이터 로드
    mm.loadFromFile("data/movies.csv");
    um.loadFromFile("data/users.csv");
    rm.loadFromFile("data/ratings.csv");

    Recommender rec(mm, rm, um);
    int choice;

    while (true) {
        cout << "\n[ 영화 추천 시스템 ]" << endl;
        cout << "1. 영화 추가       2. 영화 검색" << endl;
        cout << "3. 전체 영화 목록  4. 평점순 정렬" << endl;
        cout << "5. 사용자 추가     6. 전체 사용자 목록" << endl;
        cout << "7. 평점 입력       8. 영화별 평점 보기" << endl;
        cout << "9. 영화 추천 받기  0. 종료" << endl;
        cout << "선택: ";
        cin >> choice;
        if (cin.fail()) { cin.clear(); cin.ignore(MovieConstants::INPUT_BUFFER_SIZE, '\n'); continue; }
        cin.ignore(MovieConstants::INPUT_BUFFER_SIZE, '\n');

        if (choice == 0) {
            mm.saveToFile("data/movies.csv");
            um.saveToFile("data/users.csv");
            rm.saveToFile("data/ratings.csv");
            break;
        }

        switch (choice) {
            case 1: mm.addMovie(); break;
            case 2: mm.searchMovie(); break;
            case 3: mm.displayAllMovies(); break;
            case 4: mm.sortByRating(); break;
            case 5: um.addUser(); break;
            case 6: {
                vector<User> users = um.getAllUsers();
                if (users.empty()) { cout << "등록된 사용자가 없습니다." << endl; break; }
                cout << "\n[ 전체 사용자 목록 ]" << endl;
                for (const auto& u : users)
                    cout << "[" << u.getId() << "] " << u.getName()
                         << " | 평점 " << rm.getRatingCountByUser(u.getId()) << "개" << endl;
                break;
            }
            case 7: rm.addRating(); break;
            case 8: rm.displayMovieRatings(); break;
            case 9: {
                int userId;
                cout << "사용자 ID: ";
                cin >> userId;
                if (cin.fail()) { cin.clear(); cin.ignore(MovieConstants::INPUT_BUFFER_SIZE, '\n'); break; }
                User* u = um.findUserById(userId);
                string userName = u ? u->getName() : to_string(userId);
                cout << "\n" << userName << "에게 추천하는 영화:" << endl;
                vector<int> result = rec.recommend(userId);
                if (result.empty()) cout << "추천할 영화가 없습니다." << endl;
                break;
            }
            default: cout << "잘못된 입력입니다." << endl;
        }
    }
    return 0;
}