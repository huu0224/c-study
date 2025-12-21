#define _CRT_SECURE_NO_WARNINGS // Visual Studio 보안 경고 해결
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// n진법 문자열을 10진수 정수로 변환
int to_decimal(const char* s, int base) {
    int res = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        res = res * base + (s[i] - '0');
    }
    return res;
}

// 10진수 정수를 n진법 문자열로 변환
void from_decimal(int n, int base, char* res) {
    if (n == 0) {
        strcpy(res, "0");
        return;
    }
    char temp[20];
    int idx = 0;
    while (n > 0) {
        temp[idx++] = (n % base) + '0';
        n /= base;
    }
    for (int i = 0; i < idx; i++) {
        res[i] = temp[idx - 1 - i];
    }
    res[idx] = '\0';
}

char** solution(const char* expressions[], size_t expressions_len) {
    bool possible_base[10];
    for (int i = 2; i <= 9; i++) possible_base[i] = true;

    // 1. 등장하는 숫자 중 최댓값을 찾아 최소 진법 제한
    int max_digit = 0;
    for (size_t i = 0; i < expressions_len; i++) {
        for (int j = 0; expressions[i][j] != '\0'; j++) {
            if (expressions[i][j] >= '0' && expressions[i][j] <= '9') {
                int digit = expressions[i][j] - '0';
                if (digit > max_digit) max_digit = digit;
            }
        }
    }
    for (int i = 2; i <= max_digit; i++) possible_base[i] = false;

    // 2. 결과값이 있는 수식으로 진법 후보 필터링
    for (size_t i = 0; i < expressions_len; i++) {
        char s1[10], op[2], s2[10], eq[2], s3[10];
        sscanf(expressions[i], "%s %s %s %s %s", s1, op, s2, eq, s3);

        if (strcmp(s3, "X") != 0) {
            for (int b = 2; b <= 9; b++) {
                if (!possible_base[b]) continue;
                int n1 = to_decimal(s1, b);
                int n2 = to_decimal(s2, b);
                int target = to_decimal(s3, b);
                int calc = (op[0] == '+') ? (n1 + n2) : (n1 - n2);
                if (calc != target) possible_base[b] = false;
            }
        }
    }

    // 3. 'X' 수식 복원
    char** answer = (char**)malloc(sizeof(char*) * expressions_len);
    int ans_cnt = 0;

    for (size_t i = 0; i < expressions_len; i++) {
        char s1[10], op[2], s2[10], eq[2], s3[10];
        sscanf(expressions[i], "%s %s %s %s %s", s1, op, s2, eq, s3);

        if (strcmp(s3, "X") == 0) {
            char first_val[20] = "";
            bool is_uncertain = false;
            bool first_found = false;

            for (int b = 2; b <= 9; b++) {
                if (!possible_base[b]) continue;
                int n1 = to_decimal(s1, b);
                int n2 = to_decimal(s2, b);
                int calc = (op[0] == '+') ? (n1 + n2) : (n1 - n2);
                char current_val[20];
                from_decimal(calc, b, current_val);

                if (!first_found) {
                    strcpy(first_val, current_val);
                    first_found = true;
                }
                else if (strcmp(first_val, current_val) != 0) {
                    is_uncertain = true;
                    break;
                }
            }
            char* buf = (char*)malloc(100);
            if (is_uncertain) sprintf(buf, "%s %s %s = ?", s1, op, s2);
            else sprintf(buf, "%s %s %s = %s", s1, op, s2, first_val);
            answer[ans_cnt++] = buf;
        }
    }
    return answer;
}

// 비주얼 스튜디오 실행을 위한 main 함수 추가 (LNK2019 오류 해결)
int main() {
    const char* test_expressions[] = { "14 + 3 = 17", "13 - 6 = X", "51 - 5 = 44" };
    size_t len = 3;

    char** result = solution(test_expressions, len);

    printf("--- 복원 결과 ---\n");
    for (int i = 0; i < 1; i++) { // 예시 1번은 지워진 수식이 1개
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}