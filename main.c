#include <stdio.h>

#define SIZE 10   // 배열 크기 상수 정의

/* ============================
   프로그램 설명 함수
   프로그램의 목적과 기능을 출력
============================ */
void explainProgram()
{
    printf("이 프로그램은 배열과 함수를 이용하여 수를 입력받고,\n");
    printf("홀짝을 구분하거나 가장 큰 수 또는 가장 작은 수를 구하는 프로그램입니다.\n\n");
}

/* ============================
   홀수 출력 함수
   매개변수: 정수 배열
   기능: 배열 요소 중 홀수만 출력
============================ */
void printOdd(int arr[])
{
    printf("홀수: ");
    for (int i = 0; i < SIZE; i++)
    {
        if (arr[i] % 2 == 1)
        {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

/* ============================
   짝수 출력 함수
   매개변수: 정수 배열
   기능: 배열 요소 중 짝수만 출력
============================ */
void printEven(int arr[])
{
    printf("짝수: ");
    for (int i = 0; i < SIZE; i++)
    {
        if (arr[i] % 2 == 0)
        {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

/* ============================
   가장 큰 수를 찾는 함수
   매개변수: 정수 배열
   반환값: 배열 내 최댓값
============================ */
int findMax(int arr[])
{
    int max = arr[0];   // 첫 번째 값을 최댓값으로 초기화

    for (int i = 1; i < SIZE; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

/* ============================
   가장 작은 수를 찾는 함수
   매개변수: 정수 배열
   반환값: 배열 내 최솟값
============================ */
int findMin(int arr[])
{
    int min = arr[0];   // 첫 번째 값을 최솟값으로 초기화

    for (int i = 1; i < SIZE; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}

/* ============================
   main 함수
   프로그램 실행 시작점
============================ */
int main()
{
    int arr[SIZE];
    int menu;

    // 프로그램 설명 출력
    explainProgram();

    // 배열에 10개의 수 입력
    printf("10개의 수를 입력하세요:\n");
    for (int i = 0; i < SIZE; i++)
    {
        scanf_s("%d", &arr[i]);
    }

    // 메뉴 반복 실행
    while (1)
    {
        printf("\n");
        printf("홀짝을 구분하여라.\n");
        printf("가장 큰 수를 찾아라.\n");
        printf("가장 작은 수를 찾아라.\n");
        printf("종료는 0입니다.\n");
        printf("메뉴를 선택해주세요: ");
        scanf_s("%d", &menu);

        if (menu == 0)
        {
            printf("프로그램을 종료합니다.\n");
            break;
        }
        else if (menu == 1)
        {
            printOdd(arr);
            printEven(arr);
        }
        else if (menu == 2)
        {
            int max = findMax(arr);
            printf("가장 큰 값은 %d입니다.\n", max);
        }
        else if (menu == 3)
        {
            int min = findMin(arr);
            printf("가장 작은 값은 %d입니다.\n", min);
        }
        else
        {
            printf("잘못된 메뉴입니다. 다시 선택하세요.\n");
        }
    }

    return 0;
}