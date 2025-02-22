#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct ListNode {
    int val;
    struct ListNode* next;
}Node;

//���ӽڵ�
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

//ͷ�巨
void addnode_head(Node** head, int val) {
    Node* newnode = creatnode(val);
    if (!*head) { *head = newnode; }
    else {
        newnode->next = *head;
        *head = newnode;
    }
}
//β�巨
void addnode_tail(Node** tail, Node** list, int val) {
    Node* newnode = creatnode(val);
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

//�м����
enum intolist addnode_middle(Node** middle, int pos, int val) {
    Node* newnode = creatnode(val);
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
                printf("listlower: %d ���ܼ��룬list����ȱ�� %d λ", val, pos + 1);
                printf("\n");
                return listlower;
            }
            current = current->next;
        }
        newnode->next = current->next;
        current->next = newnode;
        return normal;
    }
}

//��ת����
void turnlist(Node** list) {
    Node* turn = NULL;
    Node* temp = NULL;
    while (*list) {
        temp = *list;
        //temp=(*list)->next;temp->next�ı䵼��������һ���ڵ�ᶪʧ
        *list = (*list)->next;
        temp->next = turn;
        turn = temp;
    }
    *list = turn;
}
//��ӡ����
void printflist(Node** list) {
    Node* current = *list;
    if (current == NULL)printf("������");
    while (current) {
        printf("%d ", current->val);
        current = current->next;
    }
}
//��������ͷ��ڴ�
void clearlist(Node** list) {
    Node* current = *list;
    while (current) {
        *list = (*list)->next;
        free(current);
        current = *list;
    }
}

typedef struct listlonger {
    int count;
    Node list;
}longer;

//����������
longer listcount(Node* list)//���������ͷ��ַ��ͷ��ֱַ�Ӹ��Ƶ��𣬻ᷢ���ı���
{
    longer* listcount = (longer*)malloc(sizeof(longer));
    int count = 0;
    listcount->list = *list;//������ֵ���Ƹ�list count�ṹ����ǲ���Ӧ�ð�list������free��
    while (list) {
        list = list->next;//Ϊɶ����ͷ��ַ�����˱仯���ⲿ������û�з����ı䣬����ط�û��������
        count++;
    }
    listcount->count = count;
    return *listcount;//���ؽṹ��ֵ�����ǵ�ַ
}

int main()
{
    Node* l1 = NULL;
    Node* l1list = NULL;
    addnode_tail(&l1, &l1list, 1);
    addnode_tail(&l1, &l1list, 9);
    addnode_tail(&l1, &l1list, 3);
    addnode_head(&l1, 6);
    addnode_middle(&l1, 2, 8);
    addnode_tail(&l1, &l1list, 1);
    addnode_middle(&l1, 6, 8);

    turnlist(&l1);
    printflist(&l1);
    listcount(l1);
    printf("   ����%d ", listcount(l1).count);
    Node l2 = listcount(l1).list;
    Node* l3 = &l2;
    //Node* l3 = &(listcount(l1).list);Ϊʲô����������д
    printflist(&l3);
    clearlist(&l1);
    printflist(&l1);
    return 0;
}
