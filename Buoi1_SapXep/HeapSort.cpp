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

// Thuat toan heap sort
void pushDown(recordType a[], int first, int last) {
    int r = first;
    while(r < (last - 1)/2) {
        if(last == (2*r +1)) {
            if(a[r].key > a[last].key) {
                swap(&a[r], &a[last]);
                r = last;
            }
        } else if(a[r].key > a[2*r+1].key && a[2*r+1].key <= a[2*r+2].key) {
            swap(&a[r], &a[2*r+1]);
            r = 2*r + 1;
        } else if(a[r].key > a[2*r+2].key && a[2*r+2].key <= a[2*r+1].key) {
            swap(&a[r], &a[2*r+2]);
            r = 2*r + 2;
        } else {
            r = last;
        }
    }
}

void heapsort(recordType a[], int n) {
    for(int i=(n-2)/2; i>=0; i--) {
        pushDown(a, i, n-1);
    }
    for(int i=n-1; i>=2; i--) {
        swap(&a[0], &a[i]);
        pushDown(a, 0, i);
    }
    swap(&a[0], &a[1]);
}

int main() {
    int n;
    recordType a[1000];
    readFile(a, &n);
    printf("Thuat toan sap xep vun dong (heapsort)\n");
    printf("Danh sach truoc khi sap xep\n");
    printList(a, n);

    heapsort(a, n);
    printf("Danh sach sau khi sap xep\n");
    printList(a, n);
}