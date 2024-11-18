#include <stdio.h>
#include <stdlib.h>
//MACRO for malloc
#define MALLOC(a,type)\
a=(type*)malloc(sizeof(type));\
if(a==NULL)\
{ printf("Insufficient memory\n");\
    exit(0);\
}
// Define structure for queue node
typedef struct Node {
    int info;
    struct Node* link;
} Node;

// Define structure for queue
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to create a new node
Node* createNode(int info) {
    Node* newNode = MALLOC(newNode,Node);
    newNode->info = info;
    newNode->link = NULL;
    return newNode;
}

// Function to create a new queue
Queue* createQueue() {
    Queue* queue = MALLOC(queue,Queue);
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Function to check if queue is empty
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Function to enqueue element
void enqueue(Queue* queue, int info) {
    Node* newNode = createNode(info);
    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->link = newNode;
        queue->rear = newNode;
    }
}

// Function to dequeue element
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int info = queue->front->info;
    Node* temp = queue->front;
    queue->front = queue->front->link;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return info;
}

// Function to get front element
int front(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->front->info;
}

// Function to print queue elements
void printQueue(Queue* queue) {
    Node* temp = queue->front;
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return ;
    }
    while (temp != NULL) {
        printf("%d ", temp->info);
        temp = temp->link;
    }
    printf("\n");
}

int main() {
    Queue* queue = createQueue();
    int choice, info;

    while (1) {
        printf("Queue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Front\n");
        printf("4. Print Queue\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter info to enqueue: ");
                scanf("%d", &info);
                enqueue(queue, info);
                break;
            case 2:
                printf("Dequeued element: %d\n", dequeue(queue));
                break;
            case 3:
                printf("Front element: %d\n", front(queue));
                break;
            case 4:
                printf("Queue elements: ");
                printQueue(queue);
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

