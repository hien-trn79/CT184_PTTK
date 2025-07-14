#include <stdio.h>

typedef int keyType;
typedef float otherType;

typedef struct {
    keyType key;
    otherType others;
} recordType;

void swap(recordType* a, recordType *b) {
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

void bubble_sort(recordType *ds, int n) {
    for(int i=0; i<n; i++) {
        for(int j=n-1; j>i; j--) {
            if(ds[j].key < ds[j-1].key) {
                swap(&ds[j], &ds[j-1]);
            }
        }
    }
}

void in_ds(recordType *ds, int n) {
    for(int i=0; i<n; i++) printf("| %2d  | %3d | %5.2f |\n", i+1, ds[i].key, ds[i].others);
}

int main() {
    int n;
    recordType ds[100];
    readFile(ds, &n);
    printf("Thuat toan sap xep noi bot (Bubble Sort)\n\n");
    printf("Danh sach truoc khi duoc sap xep\n");
    in_ds(ds, n);

    bubble_sort(ds, n);
    printf("Danh sach sau khi duoc sap xep\n");
    in_ds(ds, n);
}