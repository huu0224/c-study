#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int solution(int n, int w, int num) {
    int warehouse[101][11] = { 0 }; // 상자 배치를 위한 2차원 배열
    int current_num = 1;
    int target_row, target_col;
    int row = 0;

    // 1. 상자 배치하기
    while (current_num <= n) {
        if (row % 2 == 0) {
            // 짝수 행 (0, 2, 4...): 왼쪽 -> 오른쪽 (0 to w-1)
            for (int col = 0; col < w; col++) {
                if (current_num <= n) {
                    if (current_num == num) {
                        target_row = row;
                        target_col = col;
                    }
                    warehouse[row][col] = current_num++;
                }
            }
        }
        else {
            // 홀수 행 (1, 3, 5...): 오른쪽 -> 왼쪽 (w-1 to 0)
            for (int col = w - 1; col >= 0; col--) {
                if (current_num <= n) {
                    if (current_num == num) {
                        target_row = row;
                        target_col = col;
                    }
                    warehouse[row][col] = current_num++;
                }
            }
        }
        row++;
    }

    // 2. 위로 쌓인 상자 개수 세기
    int answer = 0;
    int max_row = row; // 상자가 쌓인 마지막 층

    for (int r = target_row; r < max_row; r++) {
        if (warehouse[r][target_col] != 0) {
            answer++;
        }
    }

    return answer;
}

// 테스트를 위한 메인 함수
int main() {
    printf("%d\n", solution(22, 6, 8)); // 예상 결과: 3
    printf("%d\n", solution(13, 3, 6)); // 예상 결과: 4
    return 0;
}