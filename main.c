#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

void push(Node **head, int data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}

int pop(Node **head) {
    Node* prev = NULL;
    int val;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    val = prev->value;
    (*head) = (*head)->next;
    free(prev);
    return val;
}

char* read_file_ascii(const char* path){
    FILE* fp = fopen(path, "r");
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* buf = (char*) malloc(sizeof(char) * (size+1));
    fread(buf, sizeof(char), size, fp);
    buf[size] = "\0";
    return buf;
}


int main() {
    Node *head = NULL;
    char *source = read_file_ascii("/Users/akabynda/CLionProjects/list_with_XML/programmers.xml");
    int k = 0;
    for (int i = 0; i < strlen(source) - 5; i++) {
        if (source[i] == '>') {
            if (source[i + 1] != '\n') {
                float number = 0;
                i++;
                float deg = 0;
                while (source[i] != '<') {
                    number = number * powf(10, deg) + (float) (source[i] - '0');
                    deg++;
                    i++;
                }
                push(&head, (int) number);
                k++;
            }
        }
    }
    Node* current = head;
    while(current != NULL){
        printf("%d ", current->value);
        current = current->next;
    }
    free(source);
    return 0;
}
