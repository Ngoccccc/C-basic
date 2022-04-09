#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct _
{
    char name[20];
    char tell[11];
    char email[25];
} phoneaddress;

void swap(phoneaddress *a, phoneaddress *b)
{
    phoneaddress c = *a;
    *a = *b;
    *b = c;
}

int count_heap = 0;

void adjust(phoneaddress *arr, int n, int i)
{
    count_heap++;
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && strcmp(arr[l].name, arr[largest].name) > 0)
        largest = l;

    if (r < n && strcmp(arr[r].name, arr[largest].name) > 0)
        largest = r;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        adjust(arr, n, largest);
    }
}

void heapSort(phoneaddress *arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        adjust(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        adjust(arr, i, 0);

    }
    printf("Danh sach sau khi sap xep:\n");
    for(int k=0;k<n;k++){
        printf("%s %s %s\n",arr[k].name,arr[k].tell,arr[k].email);
    }
}


int main(){
    phoneaddress PhoneArr[10]; // mang 10 phan tu
    FILE *source = fopen("phonedata.txt","r");
    if (source==NULL){ // bao loi neu khong mo duoc file
        printf("Error!!!\n");
        return 0;
    }
    int i =0; // bien dem cua mang
    printf("Danh sach truoc khi sap xep:\n");
    while(fscanf(source,"%s %s %s\n",PhoneArr[i].name,PhoneArr[i].tell,PhoneArr[i].email)!=EOF){  // doc tung dong
        fflush(stdin);                        // xoa bo nho dem
        printf("%s %s %s\n",PhoneArr[i].name,PhoneArr[i].tell,PhoneArr[i].email); // in ra man hinh
        i+=1;
    }
    heapSort(PhoneArr,10);  

}