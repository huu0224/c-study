#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

// 특정 문자열이 삭제 전 원본 주문서에서 몇 번째인지 계산하는 함수
ll get_index(const char* s) {
    int len = strlen(s);
    ll idx = 0;

    // 1. 길이가 len보다 짧은 모든 문자열의 개수를 더함
    for (int i = 1; i < len; i++) {
        ll count = 1;
        for (int j = 0; j < i; j++) count *= 26;
        idx += count;
    }

    // 2. 길이가 len인 문자열 중 사전순으로 s보다 앞선 것들의 개수
    for (int i = 0; i < len; i++) {
        ll diff = s[i] - 'a';
        ll rem_pos = 1;
        for (int j = 0; j < len - 1 - i; j++) rem_pos *= 26;
        idx += diff * rem_pos;
    }

    return idx + 1; // 1-based index
}

// 원본 주문서의 idx번째 문자열을 생성하는 함수
void get_string(ll idx, char* res) {
    int len = 1;
    while (1) {
        ll count = 1;
        for (int i = 0; i < len; i++) count *= 26;
        if (idx <= count) break;
        idx -= count;
        len++;
    }

    idx -= 1; // 0-based로 변경하여 계산 편의성 제공
    res[len] = '\0';
    for (int i = len - 1; i >= 0; i--) {
        res[i] = (idx % 26) + 'a';
        idx /= 26;
    }
}

// bans 배열 내의 인덱스들을 정렬하기 위한 비교 함수
int compare_ll(const void* a, const void* b) {
    ll arg1 = *(const ll*)a;
    ll arg2 = *(const ll*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

char* solution(long long n, const char* bans[], size_t bans_len) {
    // 1. bans 리스트를 원본 인덱스(숫자)로 변환하여 정렬
    ll* ban_indices = (ll*)malloc(sizeof(ll) * bans_len);
    for (size_t i = 0; i < bans_len; i++) {
        ban_indices[i] = get_index(bans[i]);
    }
    qsort(ban_indices, bans_len, sizeof(ll), compare_ll);

    // 2. 이진 탐색으로 실제 정답의 원본 인덱스(low)를 찾음
    ll low = 1, high = 2e16; // n이 10^15이므로 넉넉하게 설정
    ll final_idx = high;

    while (low <= high) {
        ll mid = low + (high - low) / 2;

        // mid보다 작거나 같은 삭제된 주문의 개수 계산 (Binary Search)
        ll count_deleted = 0;
        int l = 0, r = (int)bans_len - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (ban_indices[m] <= mid) {
                count_deleted = m + 1;
                l = m + 1;
            }
            else {
                r = m - 1;
            }
        }

        // 삭제된 개수를 뺀 순서가 n 이상인지 확인
        if (mid - count_deleted >= n) {
            final_idx = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    // 3. 찾은 인덱스를 문자열로 변환
    char* answer = (char*)malloc(12 * sizeof(char)); // 최대 11글자 + null
    get_string(final_idx, answer);

    free(ban_indices);
    return answer;
}

// 비주얼 스튜디오 테스트를 위한 main 함수
int main() {
    const char* bans1[] = { "d", "e", "bb", "aa", "ae" };
    char* result1 = solution(30, bans1, 5);
    printf("Result 1: %s\n", result1); // Expected: ah
    free(result1);

    const char* bans2[] = { "gqk", "kdn", "jxj", "jxi", "fug", "jxg", "ewq", "len", "bhc" };
    char* result2 = solution(7388, bans2, 9);
    printf("Result 2: %s\n", result2); // Expected: jxk
    free(result2);

    return 0;
}