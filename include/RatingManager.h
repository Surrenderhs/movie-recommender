#pragma once
#include <vector>
#include <string>
#include "Rating.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "BaseManager.h"

class RatingManager : public BaseManager {
private:
    std::vector<Rating> ratings;
    MovieManager* movieManager;
    UserManager* userManager;

public:
    RatingManager();
    RatingManager(MovieManager& mm, UserManager& um);

    void addRating();
    void displayMovieRatings() const;

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;

    std::vector<Rating> findByUser(int userId) const;
    std::vector<int> getAllUserIds() const;
    int getRatingCountByUser(int userId) const;
};