#pragma once
#include <string>
#include <iostream>
using namespace std;

class Rating {
private:
    int userId;
    int movieId;
    double score;

public:
    Rating();
    Rating(int ui,int mi, double s);

    int getUserId() const;
    int getMovieId() const;
    double getScore() const;

    void display() const;
};
