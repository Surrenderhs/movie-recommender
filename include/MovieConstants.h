#pragma once

namespace MovieConstants {
    // 평점 범위
    constexpr double MIN_SCORE         = 0.0;
    constexpr double MAX_SCORE         = 5.0;

    // 유사도 계산
    constexpr int    NO_SIMILARITY     = -100;  // 공통 영화 없음
    constexpr int    SIMILARITY_WEIGHT = 10;    // 공통 영화 1편당 가중치

    // 추천 파라미터
    constexpr int    TOP_K_USERS       = 2;     // 유사 사용자 상위 K명
    constexpr int    TOP_N_MOVIES      = 3;     // 추천 영화 상위 N개

    // 입력 버퍼
    constexpr int    INPUT_BUFFER_SIZE = 1000;
}