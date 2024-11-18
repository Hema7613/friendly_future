#include <stdio.h>
#include <stdlib.h>
//MACRO for malloc
#define MALLOC(a,type)\
a=(type*)malloc(sizeof(type));\
if(a==NULL)\
{ printf("Insufficient memory\n");\
    exit(0);\
}
// Define structure for stack node
typedef struct Node {
    int info;
    struct Node* link;
}Node;


// Function to push element onto stack
Node* push(int item,Node* first)
{
    Node* temp;
    MALLOC(temp,struct Node);
    temp->info=item;
    temp->link=first;
    return temp;
}

// Function to pop element from stack
Node* pop(Node* first)
{
    Node* temp;
    if(first==NULL)
    {
        printf("list is empty\n");
        return first;
    }
    temp=first;
    temp=temp->link;
    printf("item poped %d \n",first->info);
    free(first);
    return temp;
}

// Function to get top element of stack
int top(Node* first)
{
    if(first==NULL)
    {
        printf("list is empty\n");
        return -1;
    }
    return first->info;
}

// Function to print stack elements
void display(Node* first)
{
    if(first==NULL)
    {
        printf("list is empty\n");
        return;
    }
    Node* temp;
    temp=first;
    while(temp!=NULL)
    {
        printf("%d\t",temp->info);
        temp=temp->link;
    }
}

int main() {
    Node* first;
    int choice, item;

    while (1) {
        printf("Stack Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Top\n");
        printf("4. Print Stack\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter item to push: ");
                scanf("%d", &item);
                first=push(item,first);
                break;
            case 2:
                first=pop(first);
                break;
            case 3:
                printf("Top element: %d\n", top(first));
                break;
            case 4:
                printf("Stack elements: ");
                display(first);
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
