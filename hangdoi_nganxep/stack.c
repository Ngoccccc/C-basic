#include <stdio.h>
#include <stdlib.h>
 
#define Infinity -2000000000 
 
typedef struct _StackNode {
    int item;
    struct _StackNode *next;
} StackNode;
 
typedef struct _Stack {
    StackNode *top;
}Stack;
 

Stack *createStack(){
    Stack *s=(Stack*)malloc(sizeof(Stack));
    if(s==NULL) {printf("Error in memory allocation\n");exit(0);}
    s->top=NULL;
    return s;
}
 
int isEmpty(Stack *s){
    if(s==NULL) return 1;
    if(s->top==NULL) return 1;
    else return 0;
}
 
 
void push(Stack *s,int X){
    if(s==NULL) return;
    StackNode *newnode = (StackNode*)malloc(sizeof(StackNode));
    if(newnode==NULL) {printf("Error in memory allocation\n");exit(0);}
    newnode->item=X;
    newnode->next=NULL;

    newnode->next=s->top;
    s->top=newnode;
}
 

int pop(Stack *s){
    if(s==NULL) return Infinity;
    if(isEmpty(s)) return Infinity;
    int X = s->top->item;
    StackNode *tg = s->top;
    s->top=s->top->next;

    free(tg);
    return X;
}
 
void StackDestroy(Stack *s) {
    while (!isEmpty(s)) {
        pop(s);
    }
    free(s);
}
void chuyendoicoso(int n, int b){
    Stack *s=NULL;
    s = createStack();

    while(n != 0){
        push(s,n%b);
        n = n/b;
    }

    while(!isEmpty(s))
        printf("%d",pop(s));

    StackDestroy(s);
}
 
 
int main(){
    Stack *s=NULL;
    s = createStack();
    push(s,5);
    push(s,2);
    push(s,7);

    while(!isEmpty(s))
        printf("%d\n",pop(s));
 
    chuyendoicoso(3553,8);
    StackDestroy(s);
    return 1;
}