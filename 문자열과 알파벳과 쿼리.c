#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 각 그룹(문자열)의 정보를 담는 구조체
typedef struct {
    int id;             // 생성 순서 (Time stamp)
    int alpha[26];      // 알파벳 구성 (a-z 개수)
    int total_count;    // 전체 문자 개수 (0이 되면 그룹 삭제)
    int exists;         // 그룹 존재 여부
} Group;

int parent[100001];     // 각 문자가 속한 그룹의 대표 번호
Group groups[300005];   // 생성될 수 있는 최대 그룹 수 (초기 1 + 쿼리 20만)
int group_count = 0;
int char_to_alphabet[100001]; // 각 인덱스의 알파벳 값 저장

// Find 연산: 문자가 현재 어느 그룹 대표 노드에 속하는지 찾음
int find(int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent[i]);
}

// 알파벳 구성 문자열 생성 함수
char* get_alphabet_config(int group_idx) {
    char* res = (char*)malloc(1000);
    res[0] = '\0';
    char temp[50];
    int first = 1;

    for (int i = 0; i < 26; i++) {
        if (groups[group_idx].alpha[i] > 0) {
            sprintf(temp, "%s%c %d", first ? "" : " ", i + 'a', groups[group_idx].alpha[i]);
            strcat(res, temp);
            first = 0;
        }
    }
    return res;
}

// 쿼리를 처리하는 핵심 로직 (Solution 함수 예시)
char** solve(const char* s, const char* query[], int query_len, int* return_size) {
    int n = (int)strlen(s);
    int active_group_ids[300005]; // 현재 존재하는 그룹 ID들
    int active_cnt = 0;

    // 초기화: 1번 그룹 생성
    group_count = 1;
    groups[group_count].id = group_count;
    groups[group_count].exists = 1;
    for (int i = 0; i < n; i++) {
        int alpha_idx = s[i] - 'a';
        char_to_alphabet[i + 1] = alpha_idx;
        groups[group_count].alpha[alpha_idx]++;
        groups[group_count].total_count++;
        parent[i + 1] = group_count; // 일단 모든 문자는 그룹 1에 속함 (간략화)
    }

    // 결과 저장을 위한 동적 배열
    char** result = (char**)malloc(sizeof(char*) * (query_len + 100));
    int res_idx = 0;

    // 쿼리 파싱 및 처리 (생략된 세부 구현은 쿼리 번호에 따라 switch-case 사용)
    // ... 
    // 예: 4번 쿼리 (합치기) 시에는 늦게 생성된 그룹의 문자를 먼저 생성된 그룹으로 이동

    *return_size = res_idx;
    return result;
}

int main() {
    // 테스트 코드 작성
    printf("Visual Studio C Environment Ready.\n");
    return 0;
}