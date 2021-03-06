#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 26
#define BEGIN_LETTER 'a'

typedef struct Node{
    int flag;
    struct  Node *next[BASE], *fail;
}Node;

typedef struct Queue{
    Node **data;
    int head,tail, size;
    }Queue;

Node *getNewNode(){
    Node *p = (Node *) calloc(sizeof (Node), 1);
    return p;
}

Queue *init_queue(int n){
    Queue *q = (Queue *) calloc(sizeof (Queue), 1);
    q -> data = (Node **) malloc(sizeof (Node *) * n);
    q -> tail = q -> head = 0;
    return q;
}

Node *front(Queue *q){
    return q -> data[q -> head];

}
int isEmpty(Queue *q){
    return q -> head == q -> tail;
}
void push(Queue *q, Node *node){
    q -> data[q -> tail ++] = node;
    return;
}

void pop(Queue *q){
    if(isEmpty(q)) return;
    q -> head ++;
}

void clear_queue(Queue *q){
    if(q ==NULL)return;
    free(q -> data);
    free(q);
    return;
}

void clear(Node *node){
    if(node == NULL)return;
    for (int i = 0; i < BASE; ++i) {
        clear(node -> next[i]);
    }
    free(node);
    return;
}

int insert(Node *root, const char *str){
    Node *p = root;
    int cnt = 0;
    for (int i = 0; str[i]; ++i) {
        int index = str[i] - BEGIN_LETTER;
        if(p -> next[index] == NULL) p -> next[index] = getNewNode(),  ++ cnt ;
        p = p -> next[index];
    }
    p -> flag = 1;

    return cnt;
}

void build_AC(Node *root, int n){
    Queue  *q = init_queue(n + 10);
    root -> fail = NULL;
    push(q, root);
    while (!isEmpty(q)){
        Node *now_node = front(q);
        pop(q);
        for (int i = 0; i < BASE; ++i) {
            if(now_node -> next[i] == NULL) continue;
            Node *p = now_node -> fail;
            while (p && p-> next[i] ==NULL) p = p -> fail;
            if(p == NULL) now_node -> next[i] -> fail = root;
            else now_node -> next[i] -> fail = p -> next[i];
            push(q , now_node -> next[i]);
        }
    }
    return;
}

int match(Node *root, char *str){
    int cnt = 0;
    Node  *p = root;
    for (int i = 0; str[i]; ++i) {
        int index = str[i] - BEGIN_LETTER;
        while (p && p -> next[index] == NULL) p = p-> fail;
        if (p == NULL) p = root;
        else p = p ->next[index];
        Node *q = p;
        while (q) cnt += q -> flag, q = q -> fail;
    }
    return cnt;
}

int main() {
   Node *root = getNewNode();
   int n, cnt = 0;
   char str[1000];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", str);
        cnt += insert(root, str);
    }
    build_AC(root, cnt);
    scanf("%s", str);
    printf("match word cnt : %d\n", match(root, str));
    return 0;
}

//ac??????????????
// 3
//libai
// dufu
//baijuyi
// tianlibaidufu
//match word cnt : 2
