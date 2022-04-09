#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_L 256


typedef struct Node Node;
struct Node
{
    char Username[MAX_L];
    char Password[MAX_L];
    float Score; 
    Node *leftChild;
    Node *rightChild;
};

Node *makeNode(char *username, char *password, float score){    
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->Username, username);
    strcpy(p->Password, password);
    p->Score = score;
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}

Node *insert(Node *r, char *username, char *password, float score){ 
    if (r == NULL){
        return makeNode(username, password, score);
    }
    if (strcmp(r->Username, username) == 0){
        printf("Username %s exists, do not insert\n", username);
        return r;
    }
    else if (strcmp(r->Username, username) < 0){
        r->rightChild = insert(r->rightChild, username, password, score);
        return r;   
    }
    else{
        r->leftChild = insert(r->leftChild, username, password, score);
        return r;
    }
}

Node *find(Node *r, char *username){ 
    if (r == NULL){
        return NULL;
    }
    if (strcmp(r->Username, username) == 0){
        return r;
    }
    if (strcmp(r->Username, username) < 0){
        return find(r->rightChild, username);
    }
    return find(r->leftChild, username);
}

void inOrder(Node *r){  
    if (r == NULL)
        return;
    inOrder(r->leftChild);
    printf("%s    %s    %.1f\n", r->Username, r->Password, r->Score);
    inOrder(r->rightChild);
}

void printOfAdmin(Node *r){  
    if (r == NULL)
        return;
    printOfAdmin(r->leftChild);
    if (strcmp(r->Username, "Admin") != 0){
        printf("%s    %s    %.1f\n", r->Username, r->Password, r->Score);
    }
    printOfAdmin(r->rightChild);
}

void print2File(FILE *dest, Node * r){
    if (r == NULL)
        return;
    print2File(dest, r->leftChild);
    fprintf(dest,"%s    %s    %.1f\n", r->Username, r->Password, r->Score);
    print2File(dest, r->rightChild);
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

Node *removeUser(Node *r, char *username){ 
    if (r == NULL){
        return NULL;
    }
    if (strcmp(r->Username, username) > 0){
        r->leftChild = removeUser(r->leftChild, username);
    }
    else if (strcmp(r->Username, username) < 0){
        r->rightChild = removeUser(r->rightChild, username);
    }else{  
        if (r->leftChild != NULL && r->rightChild != NULL){
            Node *tmp = findMin(r->rightChild);
            strcpy(r->Username, tmp->Username);
            strcpy(r->Password, tmp->Password);
            r->rightChild = removeUser(r->rightChild, tmp->Username);
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

void freeTree(Node *r){
    if (r == NULL){
        return;
    }
    freeTree(r->leftChild);
    freeTree(r->rightChild);
    printf("Free User %s\n",r->Username);
    free(r);
}

int main(){
    Node *root = NULL;
    int choice = 0;
    int flag = 0;
    FILE *source = fopen("De2014.txt","r");
    char tempu[MAX_L], tempp[MAX_L];
    float temps;
    while (fscanf(source,"%s    %s    %f\n", tempu, tempp, &temps) != EOF){    
        fflush(stdin);
        // printf("%s    %s    %f\n", tempu, tempp, temps);
        root = insert(root, tempu, tempp, temps);
    }
    fclose(source);
    while(choice!=2){    
        printf("Menu dang nhap\n");
        printf("1. Dang nhap\n");
        printf("2. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:{
            // inOrder(root);
            int countErr = 0;
            char user[MAX_L];
            char pass[MAX_L];
            printf("Nhap Username: ");
            scanf("%s",user);
            Node *Found = find(root, user);
            if (Found == NULL){
                printf("Khong tin thay Username ma ban nhap!!!\n");
                break;
            }else{
                printf("Nhap Password: ");
                scanf("%s",pass);
                while (strcmp(Found->Password, pass) != 0){
                    printf("Nhap sai roi!!!\n");
                    countErr += 1;
                    if (countErr == 3){
                        printf("Nhap sai mat khau qua 3 lan!!! Chuong trinh tu tat!!\n");
                        return 1;
                    }
                    printf("Nhap lai Password: ");
                    scanf("%s",pass);
                }
                if (strcmp(user, "Admin") != 0){
                    int choiceSV = 0;
                    while (choiceSV != 3){
                        printf("Menu cho Sinh vien\n");
                        printf("1. Xem diem\n");
                        printf("2. Thay doi mat khau\n");
                        printf("3. Ghi lai thong tin va thoat\n");
                        printf("Lua chon cua ban: ");
                        scanf("%d", &choiceSV);
                        switch (choiceSV)
                        {
                        case 1:{
                            printf("Diem cua ban la: %.1f\n", Found->Score);
                        }
                            break;
                        case 2:{
                            int flagMK = 0;
                            char MatKhau[MAX_L];
                            char ConfirmPass[MAX_L];
                            printf("Nhap mat khau moi: ");
                            fflush(stdin);
                            scanf("%[^\n]", MatKhau);
                            fflush(stdin);
                            for (int i =0;i<strlen(MatKhau);i++){
                                if (isspace(MatKhau[i])){
                                    printf("Mat khau moi chua khoang trang khong hop le\n");
                                    flag = 1;
                                    break;
                                }
                            }
                            if (strlen(MatKhau)<6){
                                printf("Mat khau moi qua ngan!!!\n");
                                break;
                            }
                            if (flag ==1){
                                break;
                            }
                            printf("Nhap mat khau moi 1 lan nua: ");
                            scanf("%s", ConfirmPass);
                            if (strcmp(MatKhau, ConfirmPass) == 0){
                                printf("Thay doi mat khau thanh cong\n");
                                strcpy(Found->Password, MatKhau);
                            }else{
                                printf("Thay doi mat khau that bai!!!\n");
                            }
                        }
                            break;
                        case 3:{
                            FILE *dest = fopen("De2014.txt", "w");
                            print2File(dest, root);
                            fclose(dest);
                        }
                            break;
                        default:
                            choiceSV = 3;
                            printf("Nhap linh tinh ha??? Thoat day\n");
                            break;
                        }
                    }
                }else{
                    int choiceAd = 0;
                    while (choiceAd != 4){
                        printf("Menu cho Admin\n");
                        printf("1. Them Sinh Vien\n");
                        printf("2. In ra danh sach sinh vien\n");
                        printf("3. Xoa Sinh vien theo Username\n");
                        printf("4. Ghi thong tin vao file va thoat\n");
                        printf("Lua chon cua ban: ");
                        scanf("%d", &choiceAd);
                        switch (choiceAd)
                        {
                        case 1:{
                            int flag = 0;
                            char newUser[MAX_L];
                            char newPass[MAX_L];
                            float newScore;
                            fflush(stdin);
                            printf("Nhap ten Username can them: ");
                            scanf("%[^\n]", newUser);
                            fflush(stdin);
                            for (int i =0;i<strlen(newUser);i++){
                                if (isspace(newUser[i])){
                                    printf("Username chua khoang trang khong hop le\n");
                                    flag = 1;
                                    break;
                                }
                            }
                            while (flag == 1){
                                printf("Nhap lai Username: ");
                                scanf("%[^\n]", newUser);
                                fflush(stdin);
                                int k = 0;
                                printf("%d\n",strlen(newUser));
                                for (k;k<strlen(newUser);k++){
                                    if (isspace(newUser[k])){
                                        printf("Username chua khoang trang khong hop le\n");
                                        flag = 1;
                                        break;
                                    }
                                }
                                printf("%d\n",k);
                                if (k == strlen(newUser)){
                                    flag = 0;
                                }
                            }
                            printf("Nhap Password di: ");
                            scanf("%[^\n]", newPass);
                            fflush(stdin);
                            for (int i =0;i<strlen(newPass);i++){
                                if (isspace(newPass[i])){
                                    printf("Password chua khoang trang khong hop le\n");
                                    break;
                                }
                            }
                            if (strlen(newPass)<6){
                                printf("Mat khau moi qua ngan!!!\n");
                                break;
                            }
                            printf("Nhap diem di: ");
                            scanf("%f", &newScore);
                            root = insert(root, newUser, newPass, newScore);
                            printf("Da them Username %s thanh cong!!!\n", newUser);
                        }
                            break;
                        case 2:{
                            printf("Danh sach cac sinh vien:\n");
                            printOfAdmin(root);
                        }
                            break;
                        case 3:{
                            char trace[MAX_L];
                            printf("Danh sach cac sinh vien:\n");
                            printOfAdmin(root);
                            printf("Nhap Username ma ban muon xoa: ");
                            scanf("%s", trace);
                            if (strcmp(trace, "Admin")==0){
                                printf("Ban khong the xoa Admin!!!\n");
                                break;
                            }
                            printf("%s\n",trace);
                            root = removeUser(root, trace);
                            printf("Danh sach cac sinh vien:\n");
                            printOfAdmin(root);
                        }
                            break;
                        case 4:{
                            FILE *dest = fopen("De2014.txt", "w");
                            print2File(dest, root);
                            fclose(dest);
                        }
                            break;
                        default:
                            choiceAd = 4;
                            printf("Nhap linh tinh ha??? Thoat day\n");
                            break;
                        }
                    }
                }
            }
        }
            break;
        default:
            choice = 2;
            freeTree(root);
            printf("Ket thuc! Chuc ban mot ngay tot lanh\n");
            break;
        }
    }
}