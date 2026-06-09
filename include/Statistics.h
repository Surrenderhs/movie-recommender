#pragma once
#include <string>
#include <vector>
#include <utility>
#include "MovieManager.h"
#include "RatingManager.h"
#include "UserManager.h"

class Statistics {
private:
    const MovieManager&  movieManager;
    const RatingManager& ratingManager;
    const UserManager&   userManager;

public:
    Statistics(const MovieManager& mm, const RatingManager& rm, const UserManager& um);

    void display() const;  // 전체 통계 출력

private:
    void displayOverall()       const;  // 전체 평균 평점 / 총 평점 수
    void displayByGenre()       const;  // 장르별 영화 수 + 평균 평점
    void displayUserRanking()   const;  // 유저별 평점 수 랭킹
    void displayTopMovies()     const;  // 평점 높은 영화 Top 5
};