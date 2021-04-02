#include <stdio.h>
#include <stdlib.h>

//预定义数据结构
typedef struct stuInfo {
    char stuName[20]; /*学生姓名*/
    int Age; /*年龄*/
} ElemType;

typedef struct node {
    ElemType data;
    struct node *next;
} ListNode, *ListPtr;


ListPtr ListHead = NULL;
ListPtr CreateList()
{
    ListPtr newHead = malloc(sizeof(ListNode));
    newHead->next = NULL;
    return newHead;
}

void PrintList(ListPtr head)
{
    if(head==NULL)
    {
        return;
    }
    ListPtr cur = head->next;
    while(cur != NULL)
    {
        printf("(%s,%d) ", cur->data.stuName, cur->data.Age);
        cur = cur->next;
    }
    printf("\n");
    return;
}

ListPtr InsertList(ListPtr pos)
{
    ListPtr before = pos;
    ListPtr after = before->next;
    ListPtr curNode = malloc(sizeof(ListNode));

    scanf("%s%d", curNode->data.stuName, &curNode->data.Age);
    before->next = curNode;
    curNode->next = after;
    return curNode;
}

int main(int argc, char* argv[])
{
    ListPtr currentNode = NULL;

    printf("1 Create List\n");
    printf("2 Printf List\n");
    printf("3 Insert List\n");
    printf("4 Quit\n");
    while(1)
    {
        char command = getchar();
        switch (command)
        {
        case '1': 
            ListHead = CreateList();
            currentNode = ListHead;
            break;
        case '2': PrintList(ListHead);
            break;
        case '3': currentNode = InsertList(ListHead);
            break;
        case '4':
            return 0;
        }
    }
    return 0;
}