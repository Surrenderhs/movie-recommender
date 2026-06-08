#pragma once
#include <vector>
#include "MovieManager.h"
#include "RatingManager.h"

class Recommender {
private:
    MovieManager&  movieManager;
    RatingManager& ratingManager;

public:
    Recommender(MovieManager& mm, RatingManager& rm);

    // targetUserId에게 상위 K명 기준 N개 영화 추천, movieId 벡터 반환
    std::vector<int> recommend(int targetUserId, int K = 2, int N = 3) const;
};