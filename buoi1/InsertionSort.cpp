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
    FILE* file = fopen("data.txt", "r");
    if(file != NULL) {
        while(!feof(file)) {
            fscanf(file, "%d%f", &ds[i].key, &ds[i].others);
            i++;
        }
    }
    *n = i;
}

void insertion_sort(recordType *ds, int n) {
    for(int i=0; i<n; i++) {
        int j = i;
        while(j>0 && ds[j-1].key > ds[j].key) {
            swap(&ds[j], &ds[j-1]);
            j--;
        }
    }
}

void in_ds(recordType* ds, int n) {
    for(int i=0; i<n ; i++) {
        printf("| %3d | %3d | %5.2f |\n", i+1, ds[i].key, ds[i].others);
    }
}

int main() {
    int n;
    recordType ds[100];
    readFile(ds, &n);
    printf("Thuat toan sap xep chen (Insertion Sort)\n\n");
    printf("Danh sach truoc khi duoc sap xep\n");
    in_ds(ds, n);

    insertion_sort(ds, n);
    printf("Danh sach sau khi da duoc sap xep\n");
    in_ds(ds, n);
}