#include <stdio.h>

typedef int keyType;
typedef float othertype;

typedef struct {
    keyType key;
    othertype otherFields;
} recordType;

void swap(recordType *a, recordType *b) {
    recordType temp = *a;
    *a = *b;
    *b = temp;
}

void readFile(recordType a[], int *n) {
    int i=0; 
    FILE *file = fopen("data.txt", "r");
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

void SelectionSort(recordType a[], int n) {
    for(int i=0; i<n-1; i++) {
        int lowkey = a[i].key;
        int lowindex = i;
        for(int j=i+1; j<n; j++) {
            if(a[j].key < lowkey) {
                lowindex = j;
                lowkey = a[j].key;
            }
        }
        swap(&a[i], &a[lowindex]);
    }
}

int main() {
    printf("Thuat toan sap xep chon\n");
    int n;
    recordType a[1000];
    readFile(a, &n);
    printf("Danh sach truoc khi sap xep\n");
    printList(a, n);

    SelectionSort(a, n);
    printf("Danh sach sau khi sap xep\n");
    printList(a, n);
}