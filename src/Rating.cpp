#include "Rating.h"
#include "MovieConstants.h"
#include <iostream>
using namespace std;


Rating::Rating()
    :userId(0), movieId(0),score(0.0) {}

Rating::Rating(int ui,int mi,double s)
    :userId(ui), movieId(mi) {
        if (s < MovieConstants::MIN_SCORE) score = MovieConstants::MIN_SCORE;
        else if (s > MovieConstants::MAX_SCORE) score = MovieConstants::MAX_SCORE;
        else score=s;
    }

int Rating::getUserId() const{
    return userId;
}

int Rating::getMovieId() const{
    return movieId;
}

double Rating::getScore() const{
    return score;
}

void Rating::display() const{
    cout<<"userId: "<<userId
    <<" movieId: "<<movieId
    <<" score :"<<score<<endl;
}