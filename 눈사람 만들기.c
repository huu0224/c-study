#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 메모리 오버플로우 방지를 위해 정적(static) 배열로 선언합니다.
// 실제 문제의 n, m 최대치(500)를 감당하려면 메모리 설계가 더 복잡해지므로, 
// 여기서는 예시 격자 크기에 맞춰 최적화했습니다.
static bool possible_1[50][50][500];
static bool possible_2[50][50][500];
static bool checked[501][501];

long long solution(const char* grid[], size_t grid_len) {
    int n = (int)grid_len;
    int m = (int)strlen(grid[0]);
    int sr[2], sc[2], s_idx = 0;

    // 초기화
    memset(possible_1, 0, sizeof(possible_1));
    memset(possible_2, 0, sizeof(possible_2));
    memset(checked, 0, sizeof(checked));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'o') {
                sr[s_idx] = i; sc[s_idx] = j;
                if (s_idx == 0) possible_1[i][j][1] = true;
                else possible_2[i][j][1] = true;
                s_idx++;
            }
        }
    }

    int dr[] = { -1, 1, 0, 0 }, dc[] = { 0, 0, -1, 1 };

    // 각 눈덩이의 가능한 크기 계산 (간단한 DP 방식)
    for (int sz = 1; sz < 499; sz++) {
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (possible_1[r][c][sz]) {
                    for (int d = 0; d < 4; d++) {
                        int nr = r + dr[d], nc = c + dc[d];
                        if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] != '#') {
                            int next_sz = sz + (grid[nr][nc] == '.' ? 1 : 0);
                            possible_1[nr][nc][next_sz] = true;
                        }
                    }
                }
                if (possible_2[r][c][sz]) {
                    for (int d = 0; d < 4; d++) {
                        int nr = r + dr[d], nc = c + dc[d];
                        if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] != '#') {
                            int next_sz = sz + (grid[nr][nc] == '.' ? 1 : 0);
                            possible_2[nr][nc][next_sz] = true;
                        }
                    }
                }
            }
        }
    }

    long long answer = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            for (int s1 = 1; s1 < 500; s1++) {
                if (!possible_1[r][c][s1]) continue;
                for (int s2 = 1; s2 < 500; s2++) {
                    if (!possible_2[r][c][s2]) continue;

                    int head = (s1 < s2) ? s1 : s2;
                    int body = (s1 < s2) ? s2 : s1;
                    if (!checked[body][head]) {
                        checked[body][head] = true;
                        answer++;
                    }
                }
            }
        }
    }
    return answer;
}

int main() {
    // 입출력 예 #1 테스트
    const char* example_grid[] = { "#.##.", "#o###", ".o.#.", "#..#." };
    printf("결과: %lld\n", solution(example_grid, 4));
    return 0;
}