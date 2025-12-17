#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// 프로그램 설명 함수
void explainProgram(void) {
    printf("이 프로그램은 문자열을 입력받아\n");
    printf("대문자는 소문자로, 소문자는 대문자로 변환한 후\n");
    printf("문자열을 역순으로 출력하는 프로그램입니다.\n\n");
}

// 문자열 입력 함수
void inputString(char* str, size_t size) {
    while (1) {
        printf("영어 문장을 입력하세요: ");
        fgets(str, size, stdin);

        // 엔터 제거
        str[strcspn(str, "\n")] = '\0';

        // 빈 문자열 검사
        if (strlen(str) == 0) {
            printf("문자열이 입력되지 않았습니다. 다시 입력하세요.\n");
            continue;
        }

        // 숫자 포함 여부 검사
        int hasNumber = 0;
        for (size_t i = 0; str[i] != '\0'; i++) {
            if (isdigit((unsigned char)str[i])) {
                hasNumber = 1;
                break;
            }
        }

        if (hasNumber) {
            printf("잘못 입력되었습니다. 문자열에 숫자가 포함되어 있습니다. 다시 입력하세요.\n");
            continue;
        }

        break;
    }
}

// 대소문자 변환 함수
void changeCase(char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isupper((unsigned char)str[i]))
            str[i] = (char)tolower((unsigned char)str[i]);
        else if (islower((unsigned char)str[i]))
            str[i] = (char)toupper((unsigned char)str[i]);
    }
}

// 문자열 역순 출력 함수
void printReverse(const char* str) {
    size_t len = strlen(str);

    for (size_t i = len; i > 0; i--) {
        printf("%c", str[i - 1]);
    }
    printf("\n");
}

// 출력 함수 (최종 출력은 여기서만)
void outputResult(const char* original, const char* converted) {
    printf("\n입력한 문장: %s\n", original);
    printf("변환된 문장: ");
    printReverse(converted);
}

int main(void) {
    char input[MAX];
    char converted[MAX];

    explainProgram();

    inputString(input, sizeof(input));

    // 원본 문자열 복사 (보안 함수 사용)
    strcpy_s(converted, sizeof(converted), input);

    // 대소문자 변환
    changeCase(converted);

    // 결과 출력
    outputResult(input, converted);

    return 0;
}