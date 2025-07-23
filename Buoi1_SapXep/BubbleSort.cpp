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

void BubbleSort(recordType a[], int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=n-1; j>i; j--) {
            if(a[j-1].key > a[j].key) {
                swap(&a[j], &a[j-1]);
            }
        }
    }
}

int main() {
    int n;
    recordType a[1000];
    readFile(a, &n);
    printf("Thuat toan sap xep noi bot\n");
    printf("Danh sach truoc khi sap xep\n");
    printList(a, n);

    BubbleSort(a, n);
    printf("Danh sach sau khi sap xep\n");
    printList(a, n);
}