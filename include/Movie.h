#pragma once
#include <string>
#include <iostream>

class Movie {
private:
    int id;
    std::string title;
    std::string genre;
    int releaseYear;
    double totalRating;
    int ratingCount;

public:
    Movie();
    Movie(int id, const std::string& title, const std::string& genre, int year);

    int getId() const;
    std::string getTitle() const;
    std::string getGenre() const;
    int getYear() const;
    double getAverageRating() const;
    int getRatingCount() const;
    void addRating(double r);

    // M2 필수 연산자 오버로딩
    bool operator==(int targetId) const;            // ID 비교
    bool operator<(const Movie& other) const;       // 평점 비교 (정렬용)
    friend std::ostream& operator<<(std::ostream& os, const Movie& movie); // 출력
};