#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#define MAX 1000000

int arr[MAX];

int menu()
{

    int choice;

    printf("\t      ----- MENU -----\n");
    printf("\tSorting Algorithms Comparison\n 1. Create dataset\n 2. Insertion Sort\n 3. Selection Sort\n 4. Bubble Sort\n 5. Heap Sort\n 6.Quick sort \n 7.Merge sort \n 8. Exit");
    printf("\n >> ");
    scanf("%d", &choice);
    while (choice < 1 || choice > 8)
    {
        printf(">> Please choose again >> ");
        scanf("%d", &choice);
    }
    return choice;
}

void Createdataset(int arr[MAX])
{

    srand((int)time(0));
    int r;
    for (int i = 0; i < MAX; ++i)
    {
        arr[i] = random(1, 1000000);
        // printf("%d ", arr[i]);
    }

    printf("\n");
}
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Hàm selection sort
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++)
    {

        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        int tmp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = tmp;
    }
}

void bubbleSort(int arr[], int n)
{
    int i, j;
    int haveSwap = 0;
    for (i = 0; i < n - 1; i++)
    {

        haveSwap = 0;
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {

                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                haveSwap = 1;
            }
        }

        if (haveSwap == 0)
        {
            break;
        }
    }
}

void max_heap(int arr[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        int tmp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = tmp;
        tmp;

        max_heap(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{

    for (int i = n / 2 - 1; i >= 0; i--)
        max_heap(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {

        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;

        max_heap(arr, i, 0);
    }
}

void quicksort(int list[], int left, int right)
{
    int pivot, i, j;
    int temp;
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
                   list[i] < pivot);
            do
                j--;
            while (j >= left &&
                   list[j] > pivot);
            if (i < j)
            {
                // SWAP(&list[i], &list[j]);
                int tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            }
        } while (i < j);
        // SWAP(&list[left], &list[j]);
        int tmp = list[left];
        list[left] = list[j];
        list[j] = tmp;
        quicksort(list, left, j - 1);
        quicksort(list, j + 1, right);
    }
}


void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
  
    int L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
   
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
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
 

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
     
        int m = l+(r-l)/2;
 
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}
 
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int random(int minN, int maxN)
{
    return minN + rand() % (maxN + 1 - minN);
}

int main()
{
    int choice;
    while (choice != 8)
    {
        choice = menu();
        switch (choice)
        {
        case 1:
        {

            Createdataset(arr);
            break;
            system("cls");
        }
        case 2:
        {
            clock_t start, end;
            double duration;

            start = clock();

            insertionSort(arr, MAX);
            end = clock();
            duration = (double)(end - start) / CLOCKS_PER_SEC;

            printf("%f \n", duration);
            // printArray(arr, MAX);
            break;
        }
        case 3:
        {
            clock_t start, end;
            double duration;

            start = clock();

            selectionSort(arr, MAX);

            end = clock();
            duration = (double)(end - start) / CLOCKS_PER_SEC;

            printf("%f \n", duration);
            // printArray(arr, MAX);

            break;
        }
        case 4:
        {
            clock_t start, end;
            double duration;

            start = clock();

            bubbleSort(arr, MAX);

            end = clock();
            duration = (double)(end - start) / CLOCKS_PER_SEC;

            printf("%f \n", duration);
            // printArray(arr, MAX);
            break;
        }
        case 5:
        {
            clock_t start, end;
            double duration;

            start = clock();

            heapSort(arr, MAX);

            end = clock();
            duration = (double)(end - start) / CLOCKS_PER_SEC;

            printf("%f \n", duration);
            // printArray(arr, MAX);
            break;
        }
        case 6:
        {
            clock_t start, end;
            double duration;

            start = clock();

            quicksort(arr, 0, MAX);

            end = clock();
            duration = (double)(end - start) / CLOCKS_PER_SEC;

            printf("%f \n", duration);
        }
        case 7:
        {
            clock_t start, end;
            double duration;

            start = clock();

            mergeSort(arr, 0, MAX-1);

            end = clock();
            duration = (double)(end - start) / CLOCKS_PER_SEC;
            // mergeSort(arr,0, MAX-1);
            // printArray(arr, MAX);
            printf("%f \n", duration);
        }
        default:
            break;
        }
    }

    // selectionSort(arr, MAX);
    // printArray(arr, MAX);
    // insertionSort(arr, MAX);
    // printArray(arr,MAX);
    // bubbleSort(arr, MAX);
    // printArray(arr, MAX);
    // heapSort(arr, MAX);
    // printArray(arr, MAX);
    
    getch();
    return 0;
}
