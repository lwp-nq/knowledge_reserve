
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct ListNode {
    int val;
    struct ListNode* next;
}Node;

typedef struct longlist{
  int count;
  Node* list;
}longer;

//增加节点
Node* creatnode(int val) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    if (!newnode) {
        perror("Mernery alloction faild");
        assert(0);
        return NULL;
    }
    else {
        newnode->val = val;
        newnode->next = NULL;
        return newnode;
    }
}

//头插法
void addnode_head(longer* list, int val) {
    Node* newnode = creatnode(val);
    Node** head=&(*list).list;//longer结构体中指向链表头地址的指针的地址传入二级指针
    list->count+=1;
    if (!*head) { *head = newnode; }
    else {
        newnode->next = *head;
        *head = newnode;
    }
}
//尾插法
void addnode_tail(longer* tal, Node** list, int val) {
    Node* newnode = creatnode(val);
    Node** tail=&(*tal).list;
    tal->count+=1;
    if (*tail == NULL) {
        *tail = newnode;
        *list = *tail;
    }
    else {
        (*list)->next = newnode;
        *list = newnode;
    }
}

enum intolist {
    nofindlist,
    listlower,
    normal
};

//中间插入
enum intolist addnode_middle(longer* middl, int pos, int val) {
    Node* newnode = creatnode(val);
    Node** middle=&(*middl).list;
    if (!*middle) {
        //assert(false);
        printf("nofindlist");
        return nofindlist;
    }
    else {
        Node* current = *middle;
        pos = pos - 1;
        while (pos) {
            pos--;
            if (current->next == NULL)
            {
                //assert(false);
                printf("listlower: %d 不能加入，list后面缺少 %d 位", val, pos + 1);
                printf("\n");
                return listlower;
            }
            current = current->next;
        }
        newnode->next = current->next;
        current->next = newnode;
        middl->count+=1;
        return normal;
    }
}

//反转链表
void turnlist(Node** list) {
    Node* turn = NULL;
    Node* temp = NULL;
    while (*list) {
        temp = *list;
        //temp=(*list)->next;temp->next改变导致链表下一个节点会丢失
        *list = (*list)->next;
        temp->next = turn;
        turn = temp;
    }
    *list = turn;
}
//打印链表
void printflist(Node** list) {
    Node* current = *list;
    if (current == NULL)printf("空链表");
    while (current) {
        printf("%d ", current->val);
        current = current->next;
    }
}
//清除链表释放内存
void clearlist(Node** list) {
    Node* current = *list;
    while (current) {
        *list = (*list)->next;
        free(current);
        current = *list;
    }
}
/*
typedef struct listlonger {
    int count;
    Node list;
}longer;

//计数链表长度
longer listcount(const Node* list)//传入链表的头地址
{
    longer* listcount = (longer*)malloc(sizeof(longer));
    int count = 0;
    listcount->list = *list;//将链表值复制给list count结构体后，是不是应该把list在外面free了
    while (list) {
        list = list->next;//为啥链表头地址发生了变化，外部的链表没有发生改变，这个地方没有想明白
        count++;
    }
    listcount->count = count;
    return *listcount;//返回结构体值而不是地址
}
*/


int main()
{
    longer l1={0,NULL} ;
    Node* l1list = NULL;
    addnode_tail(&l1, &l1list, 1);
    addnode_tail(&l1, &l1list, 9);
    addnode_tail(&l1, &l1list, 3);
    addnode_head(&l1, 6);
    addnode_middle(&l1, 2, 8);
    addnode_tail(&l1, &l1list, 1);
    addnode_middle(&l1, 6, 8);

 //   turnlist(&l1.list);
    printflist(&l1.list);
    printf("   链表长%d ",l1.count);
/*    Node l2 = listcount(l1).list;
    Node* l3 = &l2;
    //Node* l3 = &(listcount(l1).list);为什么不能这样子写
    printflist(&l3);
    clearlist(&l1);
    printflist(&l1);
    */
    return 0;
}
