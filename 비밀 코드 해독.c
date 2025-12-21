#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 특정 조합이 모든 질문(q)과 응답(ans) 조건에 맞는지 확인하는 함수
bool check(int* current_comb, int** q, int* ans, size_t q_rows) {
    for (size_t i = 0; i < q_rows; i++) {
        int count = 0;
        // 현재 조합의 숫자 5개와 질문 i번째의 숫자 5개를 비교
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (current_comb[j] == q[i][k]) {
                    count++;
                    break;
                }
            }
        }
        // 일치하는 개수가 시스템 응답(ans)과 다르면 탈락
        if (count != ans[i]) return false;
    }
    return true;
}

int solution(int n, int** q, size_t q_rows, size_t q_cols, int ans[], size_t ans_len) {
    int answer = 0;
    int current_comb[5];

    // 1부터 n까지 숫자 중 5개를 고르는 5중 반복문 (조합 탐색)
    for (int i = 1; i <= n - 4; i++) {
        for (int j = i + 1; j <= n - 3; j++) {
            for (int k = j + 1; k <= n - 2; k++) {
                for (int l = k + 1; l <= n - 1; l++) {
                    for (int m = l + 1; m <= n; m++) {
                        current_comb[0] = i;
                        current_comb[1] = j;
                        current_comb[2] = k;
                        current_comb[3] = l;
                        current_comb[4] = m;

                        if (check(current_comb, q, ans, q_rows)) {
                            answer++;
                        }
                    }
                }
            }
        }
    }

    return answer;
}

// 비주얼 스튜디오에서 테스트하기 위한 main 함수
int main() {
    int n = 10;
    int q_rows = 5;
    int q_cols = 5;

    // 2차원 배열 동적 할당 (문제의 q 매개변수 형식)
    int** q = (int**)malloc(sizeof(int*) * q_rows);
    int data[5][5] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {3, 7, 8, 9, 10},
        {2, 5, 7, 9, 10},
        {3, 4, 5, 6, 7}
    };
    for (int i = 0; i < q_rows; i++) {
        q[i] = (int*)malloc(sizeof(int) * 5);
        for (int j = 0; j < 5; j++) q[i][j] = data[i][j];
    }

    int ans[] = { 2, 3, 4, 3, 3 };

    int result = solution(n, q, q_rows, q_cols, ans, 5);
    printf("결과: %d\n", result); // 예상 출력: 3

    // 메모리 해제
    for (int i = 0; i < q_rows; i++) free(q[i]);
    free(q);

    return 0;
}