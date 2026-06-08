#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>

using namespace std;

int main() {
    mkdir("data", 0755);
    cout << "data/ 디렉토리 준비 완료" << endl;

    // data/movies.csv — 40건
    {
        ofstream file("data/movies.csv");
        file << "id,title,genre,year,rating" << endl;
        file << "1,Inception,SF,2010,8.8" << endl;
        file << "2,Parasite,드라마,2019,8.6" << endl;
        file << "3,Interstellar,SF,2014,8.7" << endl;
        file << "4,The Matrix,SF,1999,8.7" << endl;
        file << "5,Oldboy,스릴러,2003,8.4" << endl;
        file << "6,Avengers,액션,2012,8.0" << endl;
        file << "7,Joker,스릴러,2019,8.5" << endl;
        file << "8,1917,전쟁,2019,8.3" << endl;
        file << "9,Dune,SF,2021,8.0" << endl;
        file << "10,Oppenheimer,드라마,2023,8.9" << endl;
        file << "11,The Dark Knight,액션,2008,9.0" << endl;
        file << "12,Spirited Away,애니메이션,2001,8.6" << endl;
        file << "13,Whiplash,드라마,2014,8.5" << endl;
        file << "14,Arrival,SF,2016,7.9" << endl;
        file << "15,Gravity,SF,2013,7.7" << endl;
        file << "16,Her,SF,2013,8.0" << endl;
        file << "17,Gone Girl,스릴러,2014,8.1" << endl;
        file << "18,The Revenant,어드벤처,2015,8.0" << endl;
        file << "19,Mad Max Fury Road,액션,2015,8.1" << endl;
        file << "20,La La Land,뮤지컬,2016,8.0" << endl;
        file << "21,Get Out,공포,2017,7.7" << endl;
        file << "22,Blade Runner 2049,SF,2017,8.0" << endl;
        file << "23,Hereditary,공포,2018,7.3" << endl;
        file << "24,Roma,드라마,2018,7.7" << endl;
        file << "25,Us,공포,2019,6.8" << endl;
        file << "26,Midsommar,공포,2019,7.1" << endl;
        file << "27,Tenet,SF,2020,7.3" << endl;
        file << "28,Soul,애니메이션,2020,8.1" << endl;
        file << "29,Nomadland,드라마,2020,7.3" << endl;
        file << "30,The Father,드라마,2020,8.2" << endl;
        file << "31,No Time to Die,액션,2021,7.3" << endl;
        file << "32,The Power of the Dog,드라마,2021,6.9" << endl;
        file << "33,CODA,드라마,2021,7.9" << endl;
        file << "34,Everything Everywhere,SF,2022,7.8" << endl;
        file << "35,The Banshees,드라마,2022,7.7" << endl;
        file << "36,Tar,드라마,2022,7.5" << endl;
        file << "37,All Quiet on the Front,전쟁,2022,7.8" << endl;
        file << "38,Poor Things,드라마,2023,8.0" << endl;
        file << "39,Killers of the Flower Moon,드라마,2023,7.7" << endl;
        file << "40,Past Lives,로맨스,2023,7.9" << endl;
        file.close();
        cout << "data/movies.csv 생성 완료 (40건)" << endl;
    }

    // data/users.csv — 10명
    {
        ofstream file("data/users.csv");
        file << "id,name,age" << endl;
        file << "1,김민준,25" << endl;
        file << "2,이서준,30" << endl;
        file << "3,박지후,22" << endl;
        file << "4,최수아,27" << endl;
        file << "5,정하은,24" << endl;
        file << "6,강도윤,29" << endl;
        file << "7,윤서연,23" << endl;
        file << "8,임현우,31" << endl;
        file << "9,한지원,26" << endl;
        file << "10,오승민,28" << endl;
        file.close();
        cout << "data/users.csv 생성 완료 (10건)" << endl;
    }

    // data/ratings.csv — 유저마다 10개씩 총 100건
    {
        ofstream file("data/ratings.csv");
        file << "userId,movieId,score" << endl;

        // 김민준: SF/스릴러 선호
        file << "1,1,5" << endl; file << "1,3,5" << endl; file << "1,4,4" << endl;
        file << "1,7,4" << endl; file << "1,9,3" << endl; file << "1,10,5" << endl;
        file << "1,11,5" << endl; file << "1,13,4" << endl; file << "1,14,4" << endl;
        file << "1,22,3" << endl;

        // 이서준: 액션/블록버스터 선호
        file << "2,4,5" << endl; file << "2,6,5" << endl; file << "2,8,4" << endl;
        file << "2,10,4" << endl; file << "2,11,5" << endl; file << "2,19,5" << endl;
        file << "2,27,3" << endl; file << "2,31,3" << endl; file << "2,34,4" << endl;
        file << "2,38,4" << endl;

        // 박지후: 드라마/아트하우스 선호
        file << "3,2,5" << endl; file << "3,12,5" << endl; file << "3,16,4" << endl;
        file << "3,20,4" << endl; file << "3,24,5" << endl; file << "3,28,4" << endl;
        file << "3,29,3" << endl; file << "3,30,5" << endl; file << "3,33,4" << endl;
        file << "3,40,5" << endl;

        // 최수아: 공포/스릴러 선호
        file << "4,5,4" << endl; file << "4,7,5" << endl; file << "4,17,4" << endl;
        file << "4,21,4" << endl; file << "4,23,5" << endl; file << "4,25,3" << endl;
        file << "4,26,4" << endl; file << "4,32,3" << endl; file << "4,35,4" << endl;
        file << "4,36,3" << endl;

        // 정하은: SF 선호 (김민준과 취향 유사)
        file << "5,1,5" << endl; file << "5,3,4" << endl; file << "5,4,5" << endl;
        file << "5,9,4" << endl; file << "5,10,5" << endl; file << "5,11,4" << endl;
        file << "5,14,5" << endl; file << "5,15,3" << endl; file << "5,22,4" << endl;
        file << "5,27,3" << endl;

        // 강도윤: 최신영화 선호
        file << "6,10,5" << endl; file << "6,34,4" << endl; file << "6,35,3" << endl;
        file << "6,36,4" << endl; file << "6,37,4" << endl; file << "6,38,5" << endl;
        file << "6,39,4" << endl; file << "6,40,5" << endl; file << "6,33,3" << endl;
        file << "6,28,4" << endl;

        // 윤서연: 드라마 선호 (박지후와 취향 유사)
        file << "7,2,4" << endl; file << "7,12,5" << endl; file << "7,16,5" << endl;
        file << "7,20,5" << endl; file << "7,24,4" << endl; file << "7,28,5" << endl;
        file << "7,30,4" << endl; file << "7,33,5" << endl; file << "7,38,4" << endl;
        file << "7,40,4" << endl;

        // 임현우: 고전/명작 선호
        file << "8,4,5" << endl; file << "8,5,4" << endl; file << "8,11,5" << endl;
        file << "8,12,5" << endl; file << "8,13,5" << endl; file << "8,18,4" << endl;
        file << "8,19,4" << endl; file << "8,22,4" << endl; file << "8,3,5" << endl;
        file << "8,1,4" << endl;

        // 한지원: 다양한 장르
        file << "9,2,3" << endl; file << "9,6,4" << endl; file << "9,10,4" << endl;
        file << "9,15,3" << endl; file << "9,20,4" << endl; file << "9,25,2" << endl;
        file << "9,30,4" << endl; file << "9,35,3" << endl; file << "9,38,4" << endl;
        file << "9,39,3" << endl;

        // 오승민: 액션 선호 (이서준과 취향 유사)
        file << "10,4,5" << endl; file << "10,6,4" << endl; file << "10,8,5" << endl;
        file << "10,11,5" << endl; file << "10,19,4" << endl; file << "10,27,4" << endl;
        file << "10,31,3" << endl; file << "10,34,4" << endl; file << "10,37,4" << endl;
        file << "10,38,3" << endl;

        file.close();
        cout << "data/ratings.csv 생성 완료 (100건)" << endl;
    }

    // 건수 확인
    string filenames[] = {"data/movies.csv", "data/users.csv", "data/ratings.csv"};
    for (const string& fname : filenames) {
        ifstream file(fname);
        string line;
        int lineNum = 0;
        while (getline(file, line)) lineNum++;
        cout << fname << ": " << (lineNum-1) << "건" << endl;
    }

    return 0;
}