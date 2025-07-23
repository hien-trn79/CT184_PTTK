#include <stdio.h>
#include <malloc.h>

typedef struct {
    char tenDv[25];
    float TL, GT, DG;
    int SL, PA;
} dv;

dv* readFromFile(float *W, int *n) {
    dv* ds = (dv*) malloc (sizeof(dv));
    FILE* file = fopen("CBL2.txt", "r");
    fscanf(file, "%f", W);
    int i=0;
    if(file != NULL) {
        while(!feof(file)) {
            fscanf(file, "%f%f%d%[^\n]", &ds[i].TL, &ds[i].GT, &ds[i].SL, &ds[i].tenDv);
            ds[i].DG = ds[i].GT / ds[i].TL;
            ds[i].PA = 0;
            i++;
            ds = (dv*) realloc (ds, sizeof(dv) * (i+1));
        }
    }
    *n = i;
    return ds;
}

void swap(dv* a, dv* b) {
    dv temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(dv* ds, int n) {
    for(int i=0; i<n; i++) {
        for(int j=n-1; j>i; j--) {
            if(ds[j].DG > ds[j-1].DG) swap(&ds[j], &ds[j-1]);
        }
    }
}

void in_ds(dv* ds, int n, float W) {
    float TTL = 0.0f, TGT = 0.0f;
    printf("trong luong cua balo: %.2f\n", W);
    printf("| %3s | %-18s | %5s | %5s | %3s | %5s | %3s |\n", "STT", "Ten do vat", "TL", "GT", "SL", "DG", "PA");
    for(int i=0; i<n; i++) {
        TTL += ds[i].PA * ds[i].TL;
        TGT += ds[i].PA * ds[i].GT;
        printf("| %2d  | %-18s | %5.2f | %5.2f | %2d  | %5.2f | %2d  |\n", i+1, ds[i].tenDv, ds[i].TL, ds[i].GT, ds[i].SL, ds[i].DG, ds[i].PA);
    }
    printf("Tong trong luong trong balo: %.2f\n", TTL);
    printf("Tong gia tri cua balo: %.2f\n", TGT);
}

void tao_nut_goc(float *CT, float W, float DG_max, float *TGT, float *GLNTT, float *V) {
    *TGT = 0.0f;
    *V = W;
    *CT = *V * DG_max;
    *GLNTT = 0.0f;
}

void cap_nhat_can(float TGT, float *GLNTT, int x[], dv* ds, int n) {
    if(TGT > *GLNTT) {
        *GLNTT = TGT;
        for(int i=0; i<n; i++) {
            ds[i].PA = x[i];
        }
    }
}

void nhanh_can(int i,float* TGT, float* V, float *GLNTT, float *CT, int x[], dv* ds, int n) {
    int j;
    int yk = *V/ds[i].TL;
    if(yk > ds[i].SL) yk = ds[i].SL;
    for( j=yk ; j>=0 ;j--) {
        *TGT = *TGT + j*ds[i].GT;
        *V = *V - j*ds[i].TL;
        *CT = *TGT + *V * ds[i+1].DG;

        if(*CT > *GLNTT) {
            x[i] = j;
            if((i==n-1) && (*V == 0)) {
                cap_nhat_can(*TGT, GLNTT, x, ds, n);
            } else nhanh_can(i+1, TGT, V, GLNTT, CT, x, ds, n);
        }

        x[i] = j;
        *TGT = *TGT - j*ds[i].GT;
        *V = *V + j*ds[i].TL;
    }
}

int main() {
    float W, TGT, CT, GLNTT, V;
    int n;
    dv* ds = readFromFile(&W, &n);
    bubble_sort(ds, n);
    int x[n];

    tao_nut_goc(&CT, W, ds[0].DG, &TGT, &GLNTT, &V);
    nhanh_can(0, &TGT, &W, &GLNTT, &CT, x, ds, n);
    in_ds(ds, n, W);
}