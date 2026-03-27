#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node * next;
};

    void display(struct node * head){
        struct node * temp= head; // review why *head needed wny not head
        while(temp->next!=NULL){
            printf("[%d]-> ",temp->data);
            temp=temp->next;
        }
        printf("NULL\n");
    }

int main(){
    struct node *head, * second, * third;

    struct node * newnode;
    newnode=malloc(sizeof(struct node));
    second=malloc(sizeof(struct node));
    third=malloc(sizeof(struct node));

    newnode->data=1;
    newnode->next=second;

    second->data=2;
    second->next=third;

    third->data=3;
    third->next=NULL;
    head=newnode;

    display(head);

    return 0;


}