#include<stdio.h>
#include<string.h>
struct PhoneData
{
    char Name[30];
    char PhoneNumber[12];
    char Email[30];
};
typedef struct PhoneData PhoneData;
void Inserting_Sort(PhoneData arr[], int n){
    int i, j;
    int count =0;
    PhoneData next;
    for (i=1; i<n; i++) {
        next= arr[i];
        for (j=i-1;j>=0 && strcmp(arr[j].Name,next.Name)<0; j--){
            count +=1;
            arr[j+1] = arr[j];
        }
        arr[j+1] = next;
    }
    printf("Danh sach sau khi sap xep:\n");
    for(int k=0;k<n;k++){
        printf("%s %s %s\n",arr[k].Name,arr[k].PhoneNumber,arr[k].Email);
    }
    printf("So lan so sanh la %d\n",count);
}
void Selection_Sort(PhoneData arr[], int n){
    int i, j, min,count=0;
    PhoneData tmp;
    for (i = 0; i < n-1; i++){
        min = i;
        for (j = i+1; j <=n-1 ; j++){
            if (strcmp(arr[min].Name,arr[j].Name)<0){
                count +=1;
                min = j;
            }
        }
        tmp= arr[i];
        arr[i]= arr[min];
        arr[min] = tmp;
    }
    printf("Danh sach sau khi sap xep:\n");
    for(int k=0;k<n;k++){
        printf("%s %s %s\n",arr[k].Name,arr[k].PhoneNumber,arr[k].Email);
    }
    printf("So lan so sanh la %d\n",count);
}

void merge(PhoneData arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
  
    PhoneData L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
 
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2)
    {
        if (strcmp(L[i].Name,R[j].Name)<=0) 
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
   
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 

void mergeSort(PhoneData arr[], int l, int r)
{
    if (l < r)
    {
       
        int m = l+(r-l)/2;
 
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
    
}

void quicksort(PhoneData list[], int left, int right)
{
    PhoneData pivot;
    int i, j;
   
    if (left < right)
    {
        i = left;
        j = right + 1;
        pivot = list[left];
        do
        {
            do
                i++;
            while (i <= right &&
                   strcmp(list[i].Name,pivot.Name)<0);
            do
                j--;
            while (j >= left &&
                   strcmp(list[j].Name,pivot.Name)>0);
            if (i < j)
            {
                // SWAP(&list[i], &list[j]);
                PhoneData tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            }
        } while (i < j);
        // SWAP(&list[left], &list[j]);
        PhoneData tmp = list[left];
        list[left] = list[j];
        list[j] = tmp;
        quicksort(list, left, j - 1);
        quicksort(list, j + 1, right);
    }
}





int main(){
    PhoneData PhoneArr[10]; // mang 10 phan tu
    FILE *source = fopen("phonedata.txt","r");
    if (source==NULL){ // bao loi neu khong mo duoc file
        printf("Error!!!\n");
        return 0;
    }
    int i =0; // bien dem cua mang
    printf("Danh sach truoc khi sap xep:\n");
    while(fscanf(source,"%s %s %s\n",PhoneArr[i].Name,PhoneArr[i].PhoneNumber,PhoneArr[i].Email)!=EOF){  // doc tung dong
        fflush(stdin);                        // xoa bo nho dem
        printf("%s %s %s\n",PhoneArr[i].Name,PhoneArr[i].PhoneNumber,PhoneArr[i].Email); // in ra man hinh
        i+=1;
    }
    // Sap xep bang inserting sort
   //Inserting_Sort(PhoneArr,10);
    // Sap xep bang selection sort
    // Selection_Sort(PhoneArr,10);
    // mergeSort(PhoneArr,0,10-1);
    quicksort(PhoneArr,0,10);
    printf("Danh sach sau khi sap xep:\n");
    for(int k=0;k<9;k++){
        printf("%s %s %s\n",PhoneArr[k].Name,PhoneArr[k].PhoneNumber,PhoneArr[k].Email);
    }
    fclose(source);
}
