#define _CRT_SECURE_NO_WARNINGS // C4996 오류 해결
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 1. 테스트를 위한 가상 submit 함수 (LNK2019 submit 오류 해결)
char* submit(int guess) {
    static char res[10];
    int answer = 1357; // 테스트용 비밀번호
    int s = 0, b = 0;
    int a_arr[4], g_arr[4];
    int temp_a = answer, temp_g = guess;

    for (int i = 3; i >= 0; i--) {
        a_arr[i] = temp_a % 10; temp_a /= 10;
        g_arr[i] = temp_g % 10; temp_g /= 10;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (a_arr[i] == g_arr[j]) {
                if (i == j) s++;
                else b++;
            }
        }
    }
    sprintf(res, "%dS %dB", s, b);
    return res;
}

// 2. 스트라이크/볼 판정 보조 함수
void get_hint(int target, int guess, int* s, int* b) {
    int t_arr[4], g_arr[4];
    for (int i = 3; i >= 0; i--) {
        t_arr[i] = target % 10; target /= 10;
        g_arr[i] = guess % 10; guess /= 10;
    }
    *s = 0; *b = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (t_arr[i] == g_arr[j]) {
                if (i == j) (*s)++;
                else (*b)++;
            }
        }
    }
}

// 3. 문제 해결 핵심 함수
int solution(int n) {
    static int candidates[3024];
    static bool is_valid[3024];
    int count = 0;

    // 후보군 생성 (1~9 서로 다른 4자리 수)
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (i == j) continue;
            for (int k = 1; k <= 9; k++) {
                if (k == i || k == j) continue;
                for (int l = 1; l <= 9; l++) {
                    if (l == i || l == j || l == k) continue;
                    candidates[count] = i * 1000 + j * 100 + k * 10 + l;
                    is_valid[count] = true;
                    count++;
                }
            }
        }
    }

    for (int t = 0; t < n; t++) {
        int guess = -1;
        for (int i = 0; i < count; i++) {
            if (is_valid[i]) {
                guess = candidates[i];
                break;
            }
        }

        char* res_str = submit(guess);
        int s, b;
        sscanf(res_str, "%dS %dB", &s, &b);

        if (s == 4) return guess;

        // 필터링: 결과가 일치하지 않는 후보 제거
        for (int i = 0; i < count; i++) {
            if (is_valid[i]) {
                int ts, tb;
                get_hint(candidates[i], guess, &ts, &tb);
                if (ts != s || tb != b) is_valid[i] = false;
            }
        }
    }
    return -1;
}

// 4. 메인 함수 (LNK2019 main 오류 해결)
int main() {
    int n = 3024; // 시도 가능 횟수
    int result = solution(n);
    if (result != -1) printf("정답을 찾았습니다: %d\n", result);
    else printf("정답을 찾지 못했습니다.\n");
    return 0;
}