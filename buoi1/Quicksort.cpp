#include <stdio.h>

typedef int keyType;
typedef float otherType;

typedef struct {
    keyType key;
    otherType others;
} recordType;

void swap(recordType *a, recordType *b) {
    recordType temp = *a;
    *a = *b;
    *b = temp;
}

void readFile(recordType *ds, int *n) {
    int i=0; 
    FILE *file = fopen("data.txt", "r");
    if(file != NULL) {
        while(!feof(file)) {
            fscanf(file, "%d%f", &ds[i].key, &ds[i].others);
            i++;
        }
    }
    *n = i;
}

void in_ds(recordType ds[], int n) {
    for(int i=0; i<n; i++) {
        printf("| %3d | %3d | %5.2f|\n", i+1, ds[i].key, ds[i].others);
    }
}

int findPivot(recordType ds[] ,int l, int r) {
    int k = l+1;
    while(ds[l].key == ds[k].key && k <= r) {
        k++;
    }
    if(k > r) return -1;
    else if(ds[l].key < ds[k].key) return k;
    else return l;
}

int partition(recordType ds[], int l, int r, int pivot) {
    int L = l;
    int R = r;
    while(L <= R) {
        while(ds[L].key < pivot) L++;
        while(ds[R].key >= pivot) R--;
        if(L < R) swap(&ds[L], &ds[R]);
    }
    return L;
}

void quicksort(recordType ds[], int l, int r) {
    int pivotIndex = findPivot(ds, l, r);
    if(pivotIndex != -1) {
        int pivot = ds[pivotIndex].key;
        int k = partition(ds, l, r, pivot);
        quicksort(ds, l, k-1);
        quicksort(ds, k, r);
    }
}

int main() {
    printf("Thuat toan sap xep nhanh (Quicksort)\n\n");
    int n;
    recordType ds[100];
    readFile(ds, &n);

    printf("Danh sach truoc khi duoc sap xep \n");
    in_ds(ds, n);

    printf("Danh sach sau khi duoc sap xep\n");
    quicksort(ds, 0, n-1);
    in_ds(ds, n);
}