#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "Rating.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "BaseManager.h"

class RatingManager : public BaseManager {
private:
    std::vector<Rating> ratings;
    std::unordered_map<int, std::vector<Rating>> ratingsByUser;  // userId → ratings 인덱스
    MovieManager* movieManager;
    UserManager* userManager;

    static const std::vector<Rating> emptyRatings;  // findByUser 미스 시 반환용

public:
    RatingManager();
    RatingManager(MovieManager& mm, UserManager& um);

    void addRating();
    void displayMovieRatings() const;

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;

    const std::vector<Rating>& findByUser(int userId) const;
    int getRatingCountByUser(int userId) const;
};