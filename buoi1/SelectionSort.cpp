#include <stdio.h>

typedef int keyType;
typedef float otherType;

typedef struct {
    keyType key;
    otherType others;
} recordType;

void readFile(recordType* ds, int *n) {
    FILE* file = fopen("data.txt", "r");
    int i=0;
    if(file != NULL) {
        while(!feof(file)) {
            fscanf(file, "%d%f", &ds[i].key, &ds[i].others);
            i++;
        }
    }
    *n = i;
}

void swap(recordType *a, recordType *b) {
    recordType temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(recordType *ds, int n) {
    for(int i=0; i<n-1; i++) {
        int lowkey = ds[i].key;
        int lowIndex = i;
        for(int j=i+1; j<n; j++) {
            if(ds[j].key < lowkey) {
                lowkey = ds[j].key;
                lowIndex = j;
            }
        }
        swap(&ds[i], &ds[lowIndex]);
    }
}

void in_ds(recordType *ds, int n) {
    for(int i=0; i<n; i++) {
        printf("| %3d | %3d | %5.2f |\n", i+1, ds[i].key, ds[i].others);
    }
}

int main() {
    int n;
    recordType ds[1000];
    readFile(ds, &n);
    printf("Giai thuat sap xep Selection Sort\n\n");

    printf("Danh sach truoc khi duoc sap xep\n");
    in_ds(ds, n);

    selection_sort(ds, n);
    printf("Danh sach sau khi duoc sap xep\n");
    in_ds(ds, n);
}