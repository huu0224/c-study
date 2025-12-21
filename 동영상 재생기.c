#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// "mm:ss" 형식의 문자열을 총 초(second) 단위 정수로 변환
int time_to_seconds(const char* time_str) {
    int m, s;
    sscanf(time_str, "%d:%d", &m, &s);
    return m * 60 + s;
}

// 초 단위 정수를 "mm:ss" 형식의 문자열로 변환
void seconds_to_time(int total_seconds, char* result) {
    int m = total_seconds / 60;
    int s = total_seconds % 60;
    sprintf(result, "%02d:%02d", m, s);
}

char* solution(const char* video_len, const char* pos, const char* op_start, const char* op_end, const char* commands[], size_t commands_len) {
    // 1. 모든 시간 데이터를 초 단위 정수로 변환하여 계산 준비
    int video_limit = time_to_seconds(video_len);
    int current_pos = time_to_seconds(pos);
    int start_op = time_to_seconds(op_start);
    int end_op = time_to_seconds(op_end);

    // 2. [오프닝 건너뛰기] 시작 위치가 오프닝 구간 내에 있는지 먼저 확인
    if (current_pos >= start_op && current_pos <= end_op) {
        current_pos = end_op;
    }

    // 3. 명령어(commands)를 하나씩 처리
    for (size_t i = 0; i < commands_len; i++) {
        if (strcmp(commands[i], "prev") == 0) {
            // [10초 전으로 이동] 10초 미만일 경우 0초로 고정
            current_pos -= 10;
            if (current_pos < 0) current_pos = 0;
        }
        else if (strcmp(commands[i], "next") == 0) {
            // [10초 후로 이동] 남은 시간이 10초 미만일 경우 마지막 위치로 이동
            current_pos += 10;
            if (current_pos > video_limit) current_pos = video_limit;
        }

        // [오프닝 건너뛰기] 명령어 수행 후 위치가 오프닝 구간이면 op_end로 이동
        if (current_pos >= start_op && current_pos <= end_op) {
            current_pos = end_op;
        }
    }

    // 4. 최종 위치를 "mm:ss" 형식의 문자열로 변환하여 반환
    char* answer = (char*)malloc(6 * sizeof(char));
    seconds_to_time(current_pos, answer);

    return answer;
}

// === 아래는 비주얼 스튜디오에서 결과를 확인하기 위한 테스트 코드입니다 ===
int main() {
    // 입출력 예 #1 테스트
    const char* cmd1[] = { "next", "prev" };
    char* res1 = solution("34:33", "13:00", "00:55", "02:55", cmd1, 2);
    printf("예제 1 결과: %s\n", res1); // 예상: "13:00"
    free(res1);

    // 입출력 예 #2 테스트
    const char* cmd2[] = { "prev", "next", "next" };
    char* res2 = solution("10:55", "00:05", "00:15", "06:55", cmd2, 3);
    printf("예제 2 결과: %s\n", res2); // 예상: "06:55"
    free(res2);

    // 입출력 예 #3 테스트
    const char* cmd3[] = { "next" };
    char* res3 = solution("07:22", "04:05", "00:15", "04:07", cmd3, 1);
    printf("예제 3 결과: %s\n", res3); // 예상: "04:17"
    free(res3);

    return 0;
}