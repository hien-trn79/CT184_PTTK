#include <stdio.h>

typedef int keyType;
typedef float otherType;

typedef struct {
    keyType key;
    otherType otherFields;
} recordType;

void swap(recordType *a, recordType *b) {
    recordType temp = *a;
    *a = *b;
    *b = temp;
}

void readFile(recordType a[], int *n) {
    int i=0; 
    FILE* file = fopen("data.txt", "r");
    if(file != NULL) {
        while(!feof(file)) {
            fscanf(file, "%d%f", &a[i].key, &a[i].otherFields);
            i++;
        }
    }
    *n = i;
}

void printList(recordType a[], int n) {
    for(int i=0; i<n; i++) printf("%3d%5d%8.2f\n", i+1, a[i].key, a[i].otherFields);
}
// Thuat toan sap xep Quicksort
int findPivot(recordType a[], int i, int j) {
    int k = i+1;
    while(a[i].key == a[k].key && k<=j) {
        k++;
    }
    if(k > j) return -1;
    else {
        if(a[k].key > a[i].key) return k;
        else return i;
    }
}

int partition(recordType a[], int i, int j, keyType pivot) {
    int L = i, R = j;
    while(L <= R) {
        while(a[L].key < pivot) L++;
        while(a[R].key >= pivot) R--;
        if(L < R) {
            swap(&a[L], &a[R]);
        }
    }
    return L;
}

void QuickSort(recordType a[], int i, int j) {
    keyType pivotIndex = findPivot(a, i, j);
    if(pivotIndex != -1) {
        int pivot = a[pivotIndex].key;
        int k = partition(a, i, j, pivot);
        QuickSort(a, i, k-1);
        QuickSort(a, k, j);
    }
}

int main() {
    int n;
    recordType a[1000];
    readFile(a, &n);
    printf("Thuat toan sap xep Quicksort\n");
    printf("Danh sach truoc khi sap xep\n");
    printList(a, n);

    QuickSort(a, 0, n-1);
    printf("Danh sach sau khi sap xep\n");
    printList(a, n);
}