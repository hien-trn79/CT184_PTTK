#include <stdio.h>

typedef int keyType;
typedef float otherType;

typedef struct {
    keyType key;
    otherType others;
} recordType;

void swap(recordType* a, recordType* b) {
    recordType temp = *a;
    *a = *b;
    *b = temp;
}

void readFile(recordType ds[], int *n) {
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

void in_ds(recordType *ds, int n) {
    for(int i=0; i<n; i++) {
        printf("| %3d | %3d | %5.2f |\n", i+1, ds[i].key, ds[i].others);
    }
}

// Thuat toan Heapsort
// Truong hop sap xep tang dan
void pushDown1(recordType *a, int first, int last) {
    int r = first;
    while(r < (last-1)/2) {
        // Truong hop chi co 1 con trai
        if(last == (2*r + 1)) {
            if(a[last].key < a[r].key) {
                swap(&a[last], &a[r]);
                r = last;
            }
        } else {    //Co du 2 con
            // Lon hon con trai va con trai < con phai
            if(a[r].key < a[2*r + 1].key && a[2*r+1].key >= a[2*r+2].key) {
                swap(&a[r], &a[2*r+1]);
                r = 2*r + 1;
            }
            // Lon hon con phai va con phai < con trai
            else if(a[r].key < a[2*r + 2].key && a[2*r+2].key >= a[2*r+1].key) {
                swap(&a[r], &a[2*r + 2]);
                r = 2*r + 2;
            } else {
                r = last;
            }
        }
    }
}
// Truong hop giam dan
void pushDown(recordType *a, int first, int last) {
    int r = first;
    while(r < (last-1)/2) {
        if(last == r) {
            if(a[r].key > a[last].key) {
                swap(&a[r], &a[last]);
                r = last;
            }
        } else {
            if(a[r].key > a[2*r + 1].key && a[2*r + 1].key <= a[2*r+2].key) {
                swap(&a[r], &a[2*r+1]);
                r = 2*r + 1;
            } else if(a[r].key > a[2*r + 2].key && a[2*r + 2].key <= a[2*r+1].key) {
                swap(&a[r], &a[2*r+2]);
                r = 2*r + 2;
            } else {
                r = last;
            }
        }
    }
}

void Heapsort(recordType *a, int n) {
    // Tao heap ban dau
    for(int i=(n-2)/2; i>=0; i--) {
        pushDown(a, i, n-1);
    }
    // Hoan goc va dinh cuoi
    for(int i=n-1; i>=2; i--) {
        swap(&a[i], &a[0]);
        // Sap xep lai cay Heap
        pushDown(a, 0, i);
    }
    // Hoan doi 2 nut cuoi
    swap(&a[0], &a[1]);
}

int main() {
    int n;
    recordType ds[100];
    printf("Thuat toan sap xep vun dong (Heapsort)\n\n");
    readFile(ds, &n);
    printf("Danh sach truoc khi sap xep\n");
    in_ds(ds, n);

    Heapsort(ds, n);
    printf("Danh sach sau khi duoc sap xep\n");
    in_ds(ds, n);
}