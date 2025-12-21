#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 출근 희망 시각에 10분을 더한 '출근 인정 시각'을 계산하는 함수
int get_limit_time(int schedule) {
    int hour = schedule / 100;
    int minute = schedule % 100;

    minute += 10;
    if (minute >= 60) {
        hour += 1;
        minute -= 60;
    }

    return (hour * 100) + minute;
}

int solution(int schedules[], size_t schedules_len, int** timelogs, size_t timelogs_rows, size_t timelogs_cols, int startday) {
    int successful_employees = 0;

    for (size_t i = 0; i < schedules_len; i++) {
        int limit_time = get_limit_time(schedules[i]);
        bool is_late = false;

        for (size_t j = 0; j < 7; j++) {
            // 현재 요일 계산 (startday가 1~7이므로 j를 더한 뒤 처리)
            // (startday + j - 1) % 7 + 1 공식 사용
            int current_day = (startday + (int)j - 1) % 7 + 1;

            // 토요일(6)과 일요일(7)은 체크하지 않음
            if (current_day >= 6) {
                continue;
            }

            // 평일인데 출근 인정 시각보다 늦게 온 경우
            if (timelogs[i][j] > limit_time) {
                is_late = true;
                break;
            }
        }

        // 일주일 내내 평일에 늦지 않았다면 카운트 증가
        if (!is_late) {
            successful_employees++;
        }
    }

    return successful_employees;
}

// 비주얼 스튜디오에서 테스트하기 위한 메인 함수
int main() {
    // 입출력 예시 #1 테스트
    int schedules[] = { 700, 800, 1100 };
    int rows = 3;
    int cols = 7;
    int startday = 5;

    // 2차원 배열 동적 할당 (프로그래머스 환경과 유사하게 구성)
    int** timelogs = (int**)malloc(sizeof(int*) * rows);
    int data[3][7] = {
        {710, 2359, 1050, 700, 650, 631, 659},
        {800, 801, 805, 800, 759, 810, 809},
        {1105, 1001, 1002, 600, 1059, 1001, 1100}
    };

    for (int i = 0; i < rows; i++) {
        timelogs[i] = (int*)malloc(sizeof(int) * cols);
        for (int j = 0; j < cols; j++) {
            timelogs[i][j] = data[i][j];
        }
    }

    int result = solution(schedules, 3, timelogs, 3, 7, startday);
    printf("상품을 받을 직원 수: %d\n", result); // 예상 결과: 3

    // 메모리 해제
    for (int i = 0; i < rows; i++) free(timelogs[i]);
    free(timelogs);

    return 0;
}