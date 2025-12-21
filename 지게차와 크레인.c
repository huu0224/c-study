#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// BFS를 위한 좌표 구조체
typedef struct {
    int r, c;
} Point;

int solution(const char* storage[], size_t storage_len, const char* requests[], size_t requests_len) {
    int n = (int)storage_len;
    int m = (int)strlen(storage[0]);

    // 1. 창고 확장 (상하좌우 1칸씩 여유를 둠)
    // padding을 주면 (0,0)에서 시작해 모든 외부 빈공간을 탐색하기 편합니다.
    char map[52][52];
    bool is_accessible[52][52]; // 외부와 연결된 빈 공간인지 확인

    for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < m + 2; j++) {
            map[i][j] = '0'; // '0'은 빈 공간 혹은 외부를 의미
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            map[i + 1][j + 1] = storage[i][j];
        }
    }

    int dr[] = { -1, 1, 0, 0 };
    int dc[] = { 0, 0, -1, 1 };

    for (int r_idx = 0; r_idx < requests_len; r_idx++) {
        char target = requests[r_idx][0];
        bool is_crane = (strlen(requests[r_idx]) == 2);

        // 매번 외부에서 접근 가능한 빈 공간( '0' )을 찾는 BFS
        for (int i = 0; i < n + 2; i++) memset(is_accessible[i], 0, sizeof(bool) * (m + 2));

        Point queue[2704]; // 52 * 52
        int head = 0, tail = 0;
        queue[tail++] = (Point){ 0, 0 };
        is_accessible[0][0] = true;

        while (head < tail) {
            Point curr = queue[head++];
            for (int i = 0; i < 4; i++) {
                int nr = curr.r + dr[i];
                int nc = curr.c + dc[i];
                if (nr >= 0 && nr < n + 2 && nc >= 0 && nc < m + 2) {
                    if (!is_accessible[nr][nc] && map[nr][nc] == '0') {
                        is_accessible[nr][nc] = true;
                        queue[tail++] = (Point){ nr, nc };
                    }
                }
            }
        }

        // 제거할 위치 저장
        Point to_remove[2500];
        int remove_count = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (map[i][j] == target) {
                    if (is_crane) {
                        // 크레인: 무조건 제거
                        to_remove[remove_count++] = (Point){ i, j };
                    }
                    else {
                        // 지게차: 인접한 곳 중 하나라도 외부와 연결된 빈 공간('0')이면 제거
                        for (int k = 0; k < 4; k++) {
                            if (is_accessible[i + dr[k]][j + dc[k]]) {
                                to_remove[remove_count++] = (Point){ i, j };
                                break;
                            }
                        }
                    }
                }
            }
        }

        // 실제로 지도에서 제거 ('0'으로 변경)
        for (int i = 0; i < remove_count; i++) {
            map[to_remove[i].r][to_remove[i].c] = '0';
        }
    }

    // 남은 컨테이너 개수 세기
    int answer = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (map[i][j] != '0') answer++;
        }
    }

    return answer;
}

// 비주얼 스튜디오 테스트용 main 함수
int main() {
    const char* storage[] = { "AZWQU", "CAABX", "BBDDA", "ACACA" };
    const char* requests[] = { "A", "BB", "A" };
    int result = solution(storage, 4, requests, 3);
    printf("남은 컨테이너: %d\n", result); // 예상 출력: 11
    return 0;
}