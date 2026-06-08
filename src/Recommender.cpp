#include "Recommender.h"
#include "SimilarityCalculator.h"
#include "MovieConstants.h"
#include <algorithm>
#include <set>
#include <map>
#include <iostream>
using namespace std;

Recommender::Recommender(MovieManager& mm, RatingManager& rm, UserManager& um)
    : movieManager(mm), ratingManager(rm), userManager(um) {}

vector<int> Recommender::recommend(int targetUserId, int K, int N) const {

    // 1단계: 내 평점 가져오기
    vector<Rating> myRatings = ratingManager.findByUser(targetUserId);
    if (myRatings.empty()) {
        cout << "평점 데이터가 없어 추천이 불가능합니다." << endl;
        return {};
    }

    // 내가 본 영화 ID set으로 관리
    set<int> myMovieIds;
    for (const auto& r : myRatings)
        myMovieIds.insert(r.getMovieId());

    // 2단계: 모든 사용자와 유사도 계산 (자기 자신 제외)
    vector<pair<int,int>> similarities; // (userId, 유사도)
    for (const auto& u : userManager.getAllUsers()) {
        if (u.getId() == targetUserId) continue;
        vector<Rating> otherRatings = ratingManager.findByUser(u.getId());
        int sim = SimilarityCalculator::calculate(myRatings, otherRatings);
        similarities.push_back({u.getId(), sim});
    }

    // 3단계: 유사도 -100(공통 영화 없음) 제외 후 내림차순 정렬, 상위 K명 선택
    similarities.erase(
        remove_if(similarities.begin(), similarities.end(),
            [](const pair<int,int>& p) { return p.second == MovieConstants::NO_SIMILARITY; }),
        similarities.end());

    if (similarities.empty()) {
        cout << "공통으로 평가한 영화가 없어 추천이 불가능합니다." << endl;
        return {};
    }

    sort(similarities.begin(), similarities.end(),
         [](const pair<int,int>& a, const pair<int,int>& b) {
             return a.second > b.second;
         });

    int k = min(K, (int)similarities.size());

    // 4단계: K명의 평점에서 내가 안 본 영화 점수 누적
    map<int,int> movieScores; // movieId → 추천 점수
    for (int i = 0; i < k; i++) {
        int userId = similarities[i].first;
        for (const auto& r : ratingManager.findByUser(userId)) {
            int mId = r.getMovieId();
            if (myMovieIds.find(mId) == myMovieIds.end()) // 내가 안 본 영화
                movieScores[mId] += (int)r.getScore();
        }
    }

    // 추천할 영화가 없음 (엣지 케이스)
    if (movieScores.empty()) {
        cout << "추천할 영화가 없습니다." << endl;
        return {};
    }

    // 5단계: 점수 내림차순 정렬 후 상위 N개 반환
    vector<pair<int,int>> sorted(movieScores.begin(), movieScores.end());
    sort(sorted.begin(), sorted.end(),
         [](auto& a, auto& b) { return a.second > b.second; });

    vector<int> result;
    int n = min(N, (int)sorted.size());
    for (int i = 0; i < n; i++) {
        result.push_back(sorted[i].first);
        Movie* m = movieManager.findMovie(sorted[i].first);
        if (m) cout << "추천 영화: [" << m->getId() << "] " << m->getTitle() << endl;
    }

    return result;
}