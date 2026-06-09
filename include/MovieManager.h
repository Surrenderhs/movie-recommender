#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "Movie.h"
#include "BaseManager.h"

class MovieManager : public BaseManager {
private:
    std::vector<Movie> movies;
    std::unordered_map<int, Movie*> movieIndex;  // id → Movie* 인덱스

public:
    void addMovie();
    void searchMovie() const;
    void displayAllMovies() const;
    void sortByRating() const;

    bool movieExists(int id) const;
    Movie* findMovie(int id);
    const std::vector<Movie>& getMovies() const;

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};