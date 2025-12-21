#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 주어진 숙련도(level)로 모든 퍼즐을 limit 시간 내에 풀 수 있는지 확인하는 함수
bool is_possible(int level, int diffs[], size_t diffs_len, int times[], long long limit) {
    long long total_time = 0;

    for (size_t i = 0; i < diffs_len; i++) {
        int diff = diffs[i];
        int time_cur = times[i];
        int time_prev = (i == 0) ? 0 : times[i - 1];

        if (diff <= level) {
            // 숙련도가 충분하면 바로 해결
            total_time += time_cur;
        }
        else {
            // 숙련도가 부족하면 틀린 횟수만큼 추가 시간 발생
            long long mistakes = diff - level;
            total_time += mistakes * (time_cur + time_prev) + time_cur;
        }

        // 계산 도중 이미 limit를 초과하면 false 반환 (효율성)
        if (total_time > limit) {
            return false;
        }
    }

    return total_time <= limit;
}

int solution(int diffs[], size_t diffs_len, int times[], size_t times_len, long long limit) {
    int low = 1;
    int high = 100000; // diff의 최대값
    int answer = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (is_possible(mid, diffs, diffs_len, times, limit)) {
            // 이 숙련도로 가능하면, 더 작은 숙련도가 있는지 확인
            answer = mid;
            high = mid - 1;
        }
        else {
            // 이 숙련도로 불가능하면, 숙련도를 높여야 함
            low = mid + 1;
        }
    }

    return answer;
}

// 비주얼 스튜디오 테스트를 위한 메인 함수 예시
int main() {
    int diffs[] = { 1, 328, 467, 209, 54 };
    int times[] = { 2, 7, 1, 4, 3 };
    long long limit = 1723;

    int result = solution(diffs, 5, times, 5, limit);
    printf("최소 숙련도: %d\n", result); // 예상 결과: 294

    return 0;
}