#pragma once
#include <vector>
#include <string>
#include "Movie.h"
#include "BaseManager.h"

class MovieManager : public BaseManager {
private:
    std::vector<Movie> movies;

public:
    void addMovie();
    void searchMovie() const;
    void displayAllMovies() const;
    void sortByRating() const;

    bool movieExists(int id) const;
    Movie* findMovie(int id);

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};