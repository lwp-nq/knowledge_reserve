#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct ListNode{
  int val;
  struct ListNode* next;
}Node;

//增加节点
Node* creatnode(int val){
  Node* newnode=(Node*)malloc(sizeof(Node));
  if(!newnode){
    perror("Mernery alloction faild");
    assert(0);
    return NULL;
  }
  else{
    newnode->val=val;
    newnode->next=NULL;
    return newnode;
  }
}

//头插法
void addnode_head(Node** head,int val){
  Node* newnode=creatnode(val);
  if(!*head){*head=newnode;}
  else{
    newnode->next=*head;
    *head=newnode;
  }
}
//尾插法
void addnode_tail(Node** tail,Node** list,int val){
  Node* newnode=creatnode(val);
  if(*tail==NULL){
  *tail=newnode;
  *list=*tail;
  }
  else{
  (*list)->next=newnode;
  *list=newnode;
  }
}

enum intolist{
  nofindlist,
  listlower,
  normal
};

//中间插入
enum intolist addnode_middle(Node** middle,int pos,int val){
  Node* newnode=creatnode(val);
  if(!*middle){
    //assert(false);
    printf("nofindlist");
    return nofindlist;
  }
  else{
    Node* current=*middle;
    pos=pos-1;
    while(pos){
      pos--;
      if(current->next==NULL)
      {
        //assert(false);
        printf("listlower: %d 不能加入，list后面缺少 %d 位",val,pos+1);
        printf("\n");
        return listlower;
      }
      current=current->next;
    }
    newnode->next=current->next;
    current->next=newnode;
    return normal;
  }
}

//反转链表
void turnlist(Node** list){
  Node* turn=NULL;
  Node* temp=NULL;
  while(*list){
  temp=*list;
  //temp=(*list)->next;temp->next改变导致链表下一个节点会丢失
  *list=(*list)->next;
  temp->next=turn;
  turn=temp;
  }
  *list=turn;
}
//打印链表
void printflist(Node** list){
  Node* current=*list;
  if(current == NULL)printf("空链表");
  while(current){
    printf("%d ",current->val);
    current=current->next;
  }
}
//清除链表释放内存
void clearlist(Node** list){
  Node* current=*list;
  while(current){
    *list=(*list)->next;
    free(current);
    current=*list;
  }
}

int main()
{
  Node* l1=NULL;
  Node* l1list=NULL;
  addnode_tail(&l1,&l1list,1);
  addnode_tail(&l1,&l1list,9);
  addnode_tail(&l1,&l1list,3);
  addnode_head(&l1,6);
  addnode_middle(&l1,2,8);
  addnode_tail(&l1,&l1list,1);
  addnode_middle(&l1,6,8);
  
  turnlist(&l1);
  printflist(&l1);
  clearlist(&l1);
  printflist(&l1);
  return 0;
}   
