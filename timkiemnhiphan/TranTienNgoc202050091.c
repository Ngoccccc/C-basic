#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100000
#define MAX_L 256
typedef struct Node{   
    int maso;
    char name[MAX_L];
    struct Node *leftChild;
    struct Node *rightChild;  
} Node;
Node *root;
struct info
{
    int maso;
    char name[MAX_L];
};
typedef struct info info;
info Array[100];
Node *makeNode(int maso, char *name){    
    Node *p = (Node *)malloc(sizeof(Node));
    p->maso = maso;
    strcpy(p->name, name);
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}
Node *insert(Node *r, int maso, char *name){ 
    if (r == NULL){
        return makeNode(maso, name);
    }
    if (maso == r->maso){
        printf("Children maso %s exists, do not insert\n", maso);
        return r;
    }
    else if (maso > r->maso){
        r->rightChild = insert(r->rightChild, maso, name);
        return r;   
    }
    else{
        r->leftChild = insert(r->leftChild, maso, name);
        return r;
    }
}
void inOrder(Node *r){  
    if (r == NULL)
        return;
    inOrder(r->leftChild);
    printf("%d    %s\n", r->maso, r->name);
    inOrder(r->rightChild);
}
void duyetdochoi(Node *r){
    if (r == NULL)
        return;

    inOrder(r->leftChild);
    inOrder(r->rightChild);
}
void ingiamdan(Node *r){  
    if (r == NULL)
        return;
    ingiamdan(r->rightChild);
    printf("%d    %s\n", r->maso, r->name);
    ingiamdan(r->leftChild);
}
Node *find(Node *r, int maso){ 
    if (r == NULL){
        return NULL;
    }
    if (maso == r->maso){
        return r;
    }
    if (maso > r->maso){
        return find(r->rightChild, maso);
    }
    return find(r->leftChild, maso);
}

Node *findMin(Node *r){ 
    if (r == NULL){
        return NULL;
    }
    Node *lmin = findMin(r->leftChild);
    if (lmin != NULL){
        return lmin;
    }
    return r;
}
Node *removeChildren(Node *r, int maso){ 
    if (r == NULL){
        return NULL;
    }
    if (maso < r->maso){
        r->leftChild = removeChildren(r->leftChild, maso);
    }
    else if (maso < r->maso)
        r->rightChild = removeChildren(r->rightChild, maso);
    else{  
        if (r->leftChild != NULL && r->rightChild != NULL){
            Node *tmp = findMin(r->rightChild);
            r->maso = tmp->maso;
            strcpy(r->name, tmp->name);
            r->rightChild = removeChildren(r->rightChild, tmp->maso);
        }
        else{
            Node *tmp = r;
            if (r->leftChild == NULL)
                r = r->rightChild;
            else
                r = r->leftChild;
            free(tmp);
        }
    }
    return r;
}
int count = 0;
int masox = 0;
int main(){
    root = NULL;
    int choice =0;
    while (choice!=6){
        printf("MENU\n");
        printf("1. Load file A\n");
        printf("2. Load file B\n");
        printf("3. Tim kiem\n");
        printf("4. Tong hop\n");
        printf("5. Thong ke\n");
        printf("6. Thoat\n");
        printf("Nhap lua chon: ");
        scanf("%d",&choice);
        
        switch (choice)
        {
        case 1:{
            printf("\n");
            FILE *data = fopen("A.txt","r");
            if (data == NULL)
                printf("Error!!!\n");
            int maso;
            char name[MAX_L];
            while (fscanf(data,"%d    %s",&maso,name)!=EOF){
                root = insert(root, maso, name);
            }
            printf("\n");
            inOrder(root);
            fclose(data);
        }
            break;
        case 2:{
            printf("Nhap thong tin tu file B\n");
            FILE *data = fopen("B.txt","r");
            if (data == NULL)
                printf("Error!!!\n");
            
            int maso;
            char name[MAX_L];
            while (fscanf(data,"%d    %s",&Array[masox].maso,Array[masox].name)!=EOF){
                masox += 1;
            }
            printf("\n");
            for (int i=0;i<masox;i++){
                printf("%d    %s\n",Array[i].maso,Array[i].name);
            }
            fclose(data);
            
        }
            break;
        case 3:{
            for (int i=0;i<masox;i++){
                Node* temp = find(root,Array[i].maso);
                if (temp!=NULL){
                    printf("Co ma so: %d bi trung !!!\n",temp->maso);
                    root = removeChildren(root,temp->maso);
                }
            }
            printf("Cay sau khi da xoa :\n");
            inOrder(root);
        }
            break;
        case 4:{
            for (int i=0;i<masox;i++){
                root = insert(root, Array[i].maso, Array[i].name);
            }
            ingiamdan(root);
        }
        case 5:{
            printf("\n");
            
        }
            break;
        default:
            printf("tam biet\n");
            choice =6;
            break;
        }
    }
}