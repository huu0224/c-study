#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 인접 리스트를 위한 구조체
typedef struct Node {
    int val;
    struct Node* next;
} Node;

Node** adj;
int* degree;
bool* visited;
int* comp_nodes;

// 간선 추가 함수 (무방향 그래프)
void add_edge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

// BFS를 이용해 하나의 트리에 속한 모든 노드를 탐색
void bfs(int start_node, int* count) {
    int* queue = (int*)malloc(sizeof(int) * 1000001); // 넉넉한 큐 할당
    int head = 0, tail = 0;

    queue[tail++] = start_node;
    visited[start_node] = true;

    while (head < tail) {
        int curr = queue[head++];
        comp_nodes[(*count)++] = curr;

        Node* temp = adj[curr];
        while (temp) {
            if (!visited[temp->val]) {
                visited[temp->val] = true;
                queue[tail++] = temp->val;
            }
            temp = temp->next;
        }
    }
    free(queue);
}

// 문제 해결 핵심 함수
int* solution(int nodes[], size_t nodes_len, int** edges, size_t edges_rows, size_t edges_cols) {
    int max_node = 0;
    for (size_t i = 0; i < nodes_len; i++) {
        if (nodes[i] > max_node) max_node = nodes[i];
    }

    // 전역 변수 메모리 할당
    adj = (Node**)calloc(max_node + 1, sizeof(Node*));
    degree = (int*)calloc(max_node + 1, sizeof(int));
    visited = (bool*)calloc(max_node + 1, sizeof(bool));
    comp_nodes = (int*)malloc(sizeof(int) * (max_node + 1));

    // 그래프 인접 리스트 구성 및 차수(degree) 계산
    for (size_t i = 0; i < edges_rows; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        add_edge(u, v);
        add_edge(v, u);
        degree[u]++;
        degree[v]++;
    }

    int hol_jjak_cnt = 0;
    int rev_hol_jjak_cnt = 0;

    // 포레스트 내의 각 트리 탐색
    for (size_t i = 0; i < nodes_len; i++) {
        int curr_node = nodes[i];
        if (visited[curr_node]) continue;

        int count = 0;
        bfs(curr_node, &count);

        int type_a = 0; // 홀짝 노드 후보: (번호 % 2 == 차수 % 2)
        int type_b = 0; // 역홀짝 노드 후보: (번호 % 2 != 차수 % 2)

        for (int j = 0; j < count; j++) {
            int u = comp_nodes[j];
            if ((u % 2) == (degree[u] % 2)) type_a++;
            if ((u % 2) != (degree[u] % 2)) type_b++;
        }

        // 트리에 조건을 만족하는 노드가 '단 하나'일 때 해당 트리로 인정
        if (type_a == 1) hol_jjak_cnt++;
        if (type_b == 1) rev_hol_jjak_cnt++;
    }

    // 결과 담기
    int* answer = (int*)malloc(sizeof(int) * 2);
    answer[0] = hol_jjak_cnt;
    answer[1] = rev_hol_jjak_cnt;

    // 사용한 메모리 정리
    for (int i = 0; i <= max_node; i++) {
        Node* curr = adj[i];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(adj); free(degree); free(visited); free(comp_nodes);

    return answer;
}

// Visual Studio 실행을 위한 main 함수
int main() {
    // 입출력 예 #1 테스트 데이터
    int nodes_arr[] = { 11, 9, 3, 2, 4, 6 };
    size_t nodes_len = 6;

    int e1[] = { 9, 11 }, e2[] = { 2, 3 }, e3[] = { 6, 3 }, e4[] = { 3, 4 };
    int* edges_arr[] = { e1, e2, e3, e4 };
    size_t edges_rows = 4;

    int* result = solution(nodes_arr, nodes_len, edges_arr, edges_rows, 2);

    printf("Result: [%d, %d]\n", result[0], result[1]); // 예상 결과: [1, 0]

    free(result);
    return 0;
}