#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// players: 시간대별 이용자 수 배열
// players_len: 배열의 길이 (항상 24)
// m: 서버 1대당 감당 가능한 이용자 수
// k: 증설된 서버의 운영 시간
int solution(int players[], size_t players_len, int m, int k) {
    int answer = 0;
    int active_servers[24] = { 0, }; // 각 시간대에 반납될 서버의 수를 저장하는 배열

    int current_running_servers = 0; // 현재 운영 중인 증설 서버 총합

    for (int i = 0; i < 24; i++) {
        // 1. 현재 시간(i)에 운영이 종료되는 서버를 반납 처리
        current_running_servers -= active_servers[i];

        // 2. 현재 시간대(i)에 필요한 총 증설 서버 대수 계산
        // n * m명 이상 (n + 1) * m명 미만일 때 n대의 증설 서버 필요
        int required_servers = players[i] / m;

        // 3. 현재 운영 중인 서버가 필요한 대수보다 적다면 증설
        if (current_running_servers < required_servers) {
            int need_to_add = required_servers - current_running_servers;

            answer += need_to_add; // 총 증설 횟수 누적
            current_running_servers += need_to_add; // 현재 운영 서버 수 증가

            // 4. k시간 뒤에 반납될 수 있도록 기록 (배열 범위를 벗어나지 않게 체크)
            if (i + k < 24) {
                active_servers[i + k] += need_to_add;
            }
        }
    }

    return answer;
}

// Visual Studio에서 테스트를 위한 main 함수
int main() {
    // 예시 1번 데이터
    int players[] = { 0, 2, 3, 3, 1, 2, 0, 0, 0, 0, 4, 2, 0, 6, 0, 4, 2, 13, 3, 5, 10, 0, 1, 5 };
    int m = 3;
    int k = 5;

    int result = solution(players, 24, m, k);
    printf("최종 증설 횟수: %d\n", result); // 결과: 7

    return 0;
}