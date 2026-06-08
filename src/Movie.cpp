#include "Movie.h"
#include "MovieConstants.h"

Movie::Movie() : id(0), releaseYear(0), totalRating(0.0), ratingCount(0) {}

Movie::Movie(int id, const std::string& title, const std::string& genre, int year)
    : id(id), title(title), genre(genre), releaseYear(year), totalRating(0.0), ratingCount(0) {}

int Movie::getId() const { return id; }
std::string Movie::getTitle() const { return title; }
std::string Movie::getGenre() const { return genre; }
int Movie::getYear() const { return releaseYear; }
int Movie::getRatingCount() const { return ratingCount; }

double Movie::getAverageRating() const {
    if (ratingCount == 0) return 0.0;
    return totalRating / ratingCount;
}

void Movie::addRating(double r) {
    if (r >= MovieConstants::MIN_SCORE && r <= MovieConstants::MAX_SCORE) {
        totalRating += r;
        ratingCount++;
    }
}

// 연산자 오버로딩 구현
bool Movie::operator==(int targetId) const {
    return id == targetId;
}

bool Movie::operator<(const Movie& other) const {
    return getAverageRating() < other.getAverageRating();
}

std::ostream& operator<<(std::ostream& os, const Movie& movie) {
    os << "[" << movie.id << "] " << movie.title << " (" << movie.releaseYear << ") "
       << "| 장르: " << movie.genre << " | 평점: " << movie.getAverageRating();
    return os;
}