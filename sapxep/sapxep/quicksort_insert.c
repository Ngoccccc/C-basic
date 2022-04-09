#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void swap(int *a, int *b){
    int tmp=*a;
    *a=*b; *b=tmp;
}

int partition(int arr[], int left, int right){
    int pivot, i, j;
    int t=1;
    i=left; j=right+1;
    pivot=arr[left];
    while(t=1){
        while(i<=right && arr[i]<pivot) i++;
        while(j>=left && arr[j]>pivot) j--;
        if(i>=j) break;
        swap(&arr[i],&arr[j]);
        i++; j--;
    }
    swap(&arr[left],&arr[j]);
    return j;
}

void quickSort(int arr[], int left, int right){
    if(left<right){
        int par= partition(arr,left,right);
        quickSort(arr, left, par-1);
        quickSort(arr, par+1, right);
    }
}

void insertionSort(int arr[], int n){
    int i,j;
    int par;
    for(i=1;i<n;i++){
        par=arr[i];
        for(j=i-1; j>=0 && arr[j]>par; j--){
            arr[j+1]=arr[j];
        }
        arr[j+1]=par;
    }
}

int main(int argc, char * argv[]){
    if(argc!=2) return 0;
    int N;
    clock_t start1,end1,start2,end2;
    srand(time(NULL));
    printf("So luong so trong mang random: "); scanf("%d",&N);
    int arr1[N], arr2[N], i;
    for(i=0;i<N;i++){
        int rand_num = 1 + rand()%N;
        arr1[i]=rand_num;
        arr2[i]=rand_num;
    }
    int x = atoi(argv[1]);
    // Quick Sort
    if(N>x){
        start1 = clock();
        quickSort(arr1,0,N-1);
        end1 = clock();
        double time1 = (double)(end1-start1)/CLOCKS_PER_SEC;
        printf("\nUsing Quick Sort (%.3lfs): ", time1);
    }
    // Insertion Sort
    if(N<=x){
        start2 = clock();
        insertionSort(arr2,N);
        end2 = clock();
        double time2 = (double)(end2-start2)/CLOCKS_PER_SEC;
        printf("\nUsing Insertion Sort (%.3lfs): ", time2);
    }
    return 0;
}