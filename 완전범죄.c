#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define INF 1e9 // 충분히 큰 값으로 초기화

int solution(int** info, size_t info_rows, size_t info_cols, int n, int m) {
    // dp[j]는 B의 누적 흔적이 j일 때, A의 누적 흔적의 최솟값을 저장합니다.
    // 메모리 절약을 위해 1차원 배열을 사용합니다 (이전 단계의 값을 덮어쓰는 방식)
    int* dp = (int*)malloc(sizeof(int) * m);

    // 초기화: 모두 INF로 채우고, 시작점(흔적 0)만 0으로 설정
    for (int i = 0; i < m; i++) dp[i] = INF;
    dp[0] = 0;

    for (size_t i = 0; i < info_rows; i++) {
        int costA = info[i][0];
        int costB = info[i][1];

        // 뒤에서부터 계산해야 이전 물건(i-1)의 DP 값을 안전하게 참조할 수 있습니다.
        for (int j = m - 1; j >= 0; j--) {
            // 1. i번째 물건을 B가 가져가는 경우
            int caseB = INF;
            if (j >= costB) {
                caseB = dp[j - costB];
            }

            // 2. i번째 물건을 A가 가져가는 경우
            int caseA = dp[j] + costA;

            // 두 경우 중 작은 값을 선택 (단, n 이상인 A의 흔적은 고려하지 않음)
            int minVal = (caseA < caseB) ? caseA : caseB;

            // A의 흔적이 n 이상이 되면 무의미하므로 INF 처리
            dp[j] = (minVal >= n) ? INF : minVal;
        }
    }

    int answer = INF;
    // B의 흔적이 m 미만인 모든 경우 중 A의 흔적 최솟값을 찾음
    for (int j = 0; j < m; j++) {
        if (dp[j] < answer) {
            answer = dp[j];
        }
    }

    free(dp);
    return (answer >= n || answer == INF) ? -1 : answer;
}

// 테스트를 위한 메인 함수
int main() {
    // 입출력 예 #1 테스트
    int row1[3][2] = { {1, 2}, {2, 3}, {2, 1} };
    int* info1[3] = { row1[0], row1[1], row1[2] };

    int result = solution(info1, 3, 2, 4, 4);
    printf("Result: %d\n", result); // Expected: 2

    return 0;
}