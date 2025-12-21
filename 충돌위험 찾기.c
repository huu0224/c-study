#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 포인트의 r, c 좌표를 저장하기 위한 배열 (최대 100개)
int map_r[101];
int map_c[101];

// 각 로봇의 시간대별 위치를 저장 (스택 오버플로우 방지를 위해 static 전역 변수 선언)
// [로봇번호][시간][0:r, 1:c]
static int robot_path[100][20001][2];
int path_len[100]; // 각 로봇이 운송을 마치는 시간 저장

int solution(int** points, size_t points_rows, size_t points_cols, int** routes, size_t routes_rows, size_t routes_cols) {
    int num_robots = (int)routes_rows;
    int num_stops = (int)routes_cols;

    // 1. 포인트 좌표 정보 매핑 (1번 포인트부터 시작)
    for (int i = 0; i < (int)points_rows; i++) {
        map_r[i + 1] = points[i][0];
        map_c[i + 1] = points[i][1];
    }

    int max_total_time = 0;

    // 2. 모든 로봇의 이동 경로 미리 계산 (시뮬레이션)
    for (int i = 0; i < num_robots; i++) {
        int time = 0;
        // 첫 번째 포인트에서 시작 (0초)
        int curr_r = map_r[routes[i][0]];
        int curr_c = map_c[routes[i][0]];
        robot_path[i][time][0] = curr_r;
        robot_path[i][time][1] = curr_c;

        for (int j = 1; j < num_stops; j++) {
            int target_r = map_r[routes[i][j]];
            int target_c = map_c[routes[i][j]];

            // 최단 경로 규칙: r 좌표부터 이동 후 c 좌표 이동
            while (curr_r != target_r) {
                if (curr_r < target_r) curr_r++;
                else curr_r--;
                time++;
                robot_path[i][time][0] = curr_r;
                robot_path[i][time][1] = curr_c;
            }

            while (curr_c != target_c) {
                if (curr_c < target_c) curr_c++;
                else curr_c--;
                time++;
                robot_path[i][time][0] = curr_r;
                robot_path[i][time][1] = curr_c;
            }
        }
        path_len[i] = time + 1; // 0초를 포함한 전체 경로 길이
        if (time > max_total_time) max_total_time = time;
    }

    // 3. 시간대별로 좌표를 전수조사하여 충돌 위험(2대 이상) 계산
    int total_danger_count = 0;
    for (int t = 0; t <= max_total_time; t++) {
        // 격자판(100x100)에 현재 시간 로봇 위치 표시
        int board[101][101] = { 0 };
        for (int i = 0; i < num_robots; i++) {
            if (t < path_len[i]) { // 아직 운송 중인 로봇만 계산
                int r = robot_path[i][t][0];
                int c = robot_path[i][t][1];
                board[r][c]++;
            }
        }

        // 같은 좌표에 2대 이상의 로봇이 있다면 위험 상황으로 판단
        for (int r = 1; r <= 100; r++) {
            for (int c = 1; c <= 100; c++) {
                if (board[r][c] >= 2) {
                    total_danger_count++;
                }
            }
        }
    }

    return total_danger_count;
}

int main() {
    // 입출력 예 #1 테스트 데이터
    // points: [[3, 2], [6, 4], [4, 7], [1, 4]]
    int p1[] = { 3, 2 }, p2[] = { 6, 4 }, p3[] = { 4, 7 }, p4[] = { 1, 4 };
    int* points_data[] = { p1, p2, p3, p4 };

    // routes: [[4, 2], [1, 3], [2, 4]]
    int r1[] = { 4, 2 }, r2[] = { 1, 3 }, r3[] = { 2, 4 };
    int* routes_data[] = { r1, r2, r3 };

    // 함수 호출
    int result = solution(points_data, 4, 2, routes_data, 3, 2);

    // 결과 출력
    printf("최종 충돌 위험 횟수: %d\n", result); // 예상 결과: 1

    return 0;
}