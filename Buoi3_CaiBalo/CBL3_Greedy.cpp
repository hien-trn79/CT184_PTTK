#include <stdio.h>
#include <malloc.h>

typedef struct {
    char tenDV[25];
    float TL, GT, DG;
    int SL, PA;
} DV;

DV* readFromFile(float* W, int *n) {
    DV* dsdv;
    FILE *file = fopen("CBL3.txt", "r");
    dsdv = (DV*) malloc (sizeof(DV));
    fscanf(file, "%f", W);
    int i=0;
    if(file != NULL) {
        while(!feof(file)) {
            fscanf(file, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].tenDV);
            dsdv[i].DG =  dsdv[i].GT / dsdv[i].TL;
            dsdv[i].PA = 0;
            i++;
            dsdv = (DV*) realloc (dsdv, sizeof(DV) * (i+1));
        }
    }
    *n = i;
    return dsdv;
}

void in_dsdv(DV* dsdv, int n) {
    float TTL=0, TGT = 0;
    printf("| %3s | %-18s | %5s | %5s | %5s | %3s |\n", "STT", "Ten do vat", "TL", "GT", "DG", "PA");
    for(int i=0; i<n; i++) {
        TTL += dsdv[i].PA * dsdv[i].TL;
        TGT += dsdv[i].PA * dsdv[i].GT;
        printf("| %2d  | %-18s | %5.2f | %5.2f | %5.2f | %3d |\n", i+1, dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].PA);
    }

    printf("Tong trong luong trong balo: %.2f\n", TTL);
    printf("Tong gia tri do vat: %.2f\n", TGT);
}

void swap(DV* a, DV* b) {
    DV temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(DV* dsdv, int n) {
    for(int i=0; i<n; i++) {
        for(int j=n-1; j>i; j--) {
            if(dsdv[j].DG > dsdv[j-1].DG) swap(&dsdv[j], &dsdv[j-1]);
        }
    }
}

void greedy(DV* ds, float W, int n) {
    for(int i=0; i<n; i++) {
        ds[i].PA = W / ds[i].TL;
        if(ds[i].PA > 1) ds[i].PA = 1;
        W -= ds[i].PA * ds[i].TL;
    }
}

int main() {
    float W;
    int n;
    DV* dsdv = readFromFile(&W, &n);
    bubble_sort(dsdv, n);

    greedy(dsdv, W, n);
    in_dsdv(dsdv, n);
}