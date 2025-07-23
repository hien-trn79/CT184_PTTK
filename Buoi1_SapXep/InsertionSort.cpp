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
    FILE* file = fopen("data.txt", "r");
    int i=0;
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

void insertionSort(recordType a[], int n) {
    for(int i=0; i<n; i++) {
        int j = i+1;
        while(j > 0 && a[j].key < a[j-1].key) {
            swap(&a[j], &a[j-1]);
            j--;
        }
    }
}

int main() {
    int n;
    recordType a[1000];
    readFile(a, &n);
    printf("Thuat toan sap xep chen\n");
    printf("Danh sach truoc khi sap xep\n");
    printList(a, n);
    insertionSort(a, n);
    printf("Danh sach sau khi sap xep\n");
    printList(a, n);
}