#include <stdio.h>

int main() {
    int choice, height;

    // 프로그램 제목 출력
    printf("허윤정 프로그램\n");
    printf("출력할 도형을 고르시오.\n");
    printf(" 1) 직각삼각형\n");
    printf(" 2) 역직각삼각형\n");
    printf(" 3) 피라미드\n");
    printf(" 4) 역피라미드\n");
    printf("본인의 선택은?(1~4중 선택): ");
    scanf_s("%d", &choice);

    // 예외 처리 : 메뉴 선택
    if (choice < 1 || choice > 4) {
        printf("잘못된 선택입니다.\n");
        return 0;
    }

    // 층수 입력
    printf("출력할 층수를 입력하세요: ");
    scanf_s("%d", &height);

    // 예외 처리 : 층수
    if (height <= 0) {
        printf("층수는 1 이상이어야 합니다.\n");
        return 0;
    }

    // 직각삼각형
    if (choice == 1) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j <= i; j++) {
                printf("%c", 'A' + i);
            }
            printf("\n");
        }
    }

    // 역직각삼각형
    else if (choice == 2) {
        for (int i = 0; i < height; i++) {
            for (int j = height; j > i; j--) {
                printf("%c", 'A' + i);
            }
            printf("\n");
        }
    }

    // 피라미드
    else if (choice == 3) {
        for (int i = 0; i < height; i++) {
            // 공백 출력
            for (int j = height - i - 1; j > 0; j--) {
                printf(" ");
            }
            // 문자 출력
            for (int k = 0; k < 2 * i + 1; k++) {
                printf("%c", 'A' + i);
            }
            printf("\n");
        }
    }

    // 역피라미드
    else if (choice == 4) {
        for (int i = 0; i < height; i++) {
            // 공백 출력
            for (int j = 0; j < i; j++) {
                printf(" ");
            }
            // 문자 출력
            for (int k = 2 * (height - i) - 1; k > 0; k--) {
                printf("%c", 'A' + i);
            }
            printf("\n");
        }
    }

    return 0;
}