#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h> // size_t 및 C2059 오류 해결을 위해 필수

#define MAX_N 14
#define MAX_M 100
#define INF 1000000000 // C4244 경고 해결: 1e9 대신 정수 사용

// 최대값을 구하는 매크로
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 문제 풀이 함수
int solution(int** visible, size_t visible_rows, size_t visible_cols,
    int** hidden, size_t hidden_rows, size_t hidden_cols, int k) {

    int n = (int)visible_rows;
    int m = (int)visible_cols;
    int max_final_result = -INF;

    int current_grid[MAX_N][MAX_M];
    int dp[MAX_N][MAX_M];

    for (int row_mask = 0; row_mask < (1 << n); row_mask++) {
        int row_flip_count = 0;
        for (int i = 0; i < n; i++) {
            if ((row_mask >> i) & 1) row_flip_count++;
        }

        int col_flip_count = 0;
        for (int j = 0; j < m; j++) {
            int normal_sum = 0;
            int flipped_sum = 0;

            for (int i = 0; i < n; i++) {
                bool row_is_flipped = (row_mask >> i) & 1;
                int val_if_col_not_flipped = row_is_flipped ? hidden[i][j] : visible[i][j];
                int val_if_col_flipped = row_is_flipped ? visible[i][j] : hidden[i][j];

                normal_sum += val_if_col_not_flipped;
                flipped_sum += val_if_col_flipped;
            }

            if (flipped_sum - k > normal_sum) {
                col_flip_count++;
                for (int i = 0; i < n; i++) {
                    bool row_is_flipped = (row_mask >> i) & 1;
                    current_grid[i][j] = row_is_flipped ? visible[i][j] : hidden[i][j];
                }
            }
            else {
                for (int i = 0; i < n; i++) {
                    bool row_is_flipped = (row_mask >> i) & 1;
                    current_grid[i][j] = row_is_flipped ? hidden[i][j] : visible[i][j];
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0) dp[i][j] = current_grid[i][j];
                else {
                    int from_top = (i > 0) ? dp[i - 1][j] : -INF;
                    int from_left = (j > 0) ? dp[i][j - 1] : -INF;
                    dp[i][j] = current_grid[i][j] + MAX(from_top, from_left);
                }
            }
        }

        int total_cost = (row_flip_count + col_flip_count) * k;
        max_final_result = MAX(max_final_result, dp[n - 1][m - 1] - total_cost);
    }

    return max_final_result;
}

// LNK2019 오류 해결을 위해 반드시 필요한 main 함수
int main() {
    // 예시 데이터 세팅 (입출력 예 1번 기준)
    int n = 2, m = 2, k = 0;

    int** visible = (int**)malloc(sizeof(int*) * n);
    int** hidden = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        visible[i] = (int*)malloc(sizeof(int) * m);
        hidden[i] = (int*)malloc(sizeof(int) * m);
    }

    // visible: [[1, 2], [3, 4]]
    visible[0][0] = 1; visible[0][1] = 2;
    visible[1][0] = 3; visible[1][1] = 4;

    // hidden: [[5, 6], [7, 8]]
    hidden[0][0] = 5; hidden[0][1] = 6;
    hidden[1][0] = 7; hidden[1][1] = 8;

    int result = solution(visible, n, m, hidden, n, m, k);
    printf("최대 결과값: %d\n", result); // 예상 결과: 20

    // 메모리 해제
    for (int i = 0; i < n; i++) {
        free(visible[i]);
        free(hidden[i]);
    }
    free(visible);
    free(hidden);

    return 0;
}