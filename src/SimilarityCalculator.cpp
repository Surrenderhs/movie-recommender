#include "SimilarityCalculator.h"
#include "MovieConstants.h"
#include <cstdlib>
using namespace std;

int SimilarityCalculator::calculate(
    const vector<Rating>& user1,
    const vector<Rating>& user2)
{
    int commonCount  = 0;
    int scoreDiffSum = 0;

    for (const Rating& r1 : user1) {
        for (const Rating& r2 : user2) {
            if (r1.getMovieId() == r2.getMovieId()) {
                commonCount++;
                scoreDiffSum += abs((int)r1.getScore() - (int)r2.getScore());
            }
        }
    }

    if (commonCount == 0) return MovieConstants::NO_SIMILARITY;
    return commonCount * MovieConstants::SIMILARITY_WEIGHT - scoreDiffSum;
}