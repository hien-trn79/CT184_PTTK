#include <stdio.h>
#include <malloc.h>

typedef struct {
    char tenDV[25];
    int SL, TL, GT, PA;
} dv;

typedef int bang [50][100];

dv* readFromFile(int *n, int* W) {
    dv* ds = (dv*) malloc (sizeof(dv));
    int i=0;
    FILE *file = fopen("CBL2.txt", "r");
    if(file == NULL) printf("Loi mo file");
    else {
        fscanf(file, "%d", W);
        while(!feof(file)) {
            fscanf(file, "%d%d%d%[^\n]", &ds[i].TL, &ds[i].GT, &ds[i].SL, &ds[i].tenDV);
            ds[i].PA = 0;
            i++;

            ds = (dv*) realloc (ds, sizeof(dv) * (i+1));
        }
    }
    *n = i;
    return ds;
}

void in_ds_dv(dv* ds, int n, int W) {
    printf("Trong luong ban dau cua balo: %d\n", W);
    printf("| %3s | %-20s | %3s | %3s | %3s | %3s |\n", "STT", "Ten do vat", "TL", "GT", "SL", "PA");
    for(int i=0; i<n; i++) {
        printf("| %2d  | %-20s | %2d  | %2d  | %2d  | %2d  |\n", i+1, ds[i].tenDV, ds[i].TL, ds[i].GT, ds[i].SL, ds[i].PA);
    }
}

void tao_bang(dv* ds, int n, int W, bang f, bang x) {
    for(int V = 0; V<=W; V++) {
        x[0][V] = V / ds[0].TL;
        if(x[0][V] > ds[0].SL ) x[0][V] = ds[0].SL;
        f[0][V] = x[0][V] * ds[0].GT;  
    }
    for(int k=1; k<n; k++) {
        for(int V = 0; V<=W; V++) {
            int fmax = f[k-1][V];
            int xmax = 0;
            int yk = V / ds[k].TL;
            if(yk > ds[k].SL) yk = ds[k].SL;
            for(int xk = 0; xk <= yk; xk++) {
                if(f[k-1][V - xk*ds[k].TL] + xk * ds[k].GT > fmax) {
                    fmax = f[k-1][V - xk*ds[k].TL] + xk * ds[k].GT;
                    xmax = xk;
                }
            }
            f[k][V] = fmax;
            x[k][V] = xmax;
        }
    }
}

void in_bang(bang f, bang x, int n, int W) {
    for(int i=0; i<n; i++) {
        printf("| %2d  || ", i+1);
        for(int j=0; j<=W; j++) {
            printf("%2d  | %2d  || ", f[i][j], x[i][j]);
        }
        printf("\n");
    }
}

void tra_bang(dv* ds, int n, bang x, int W) {
    int V = W;
    int k = n-1;
    while(V>=0 && k>=0) {
        ds[k].PA = x[k][V];
        V -= ds[k].PA * ds[k].TL;
        k--;
    }
}

void in_phuong_an(dv* ds, int n) {
    int TTL = 0, TGT = 0;
    printf("Phuong an tot nhat: (");
    for(int i=0; i<n-1; i++) {
        TTL += ds[i].PA * ds[i].TL;
        TGT += ds[i].PA * ds[i].GT;
        printf("%d; ", ds[i].PA);
    }
    printf("%d)\n", ds[n-1].PA);
    printf("Tong trong luong cua balo: %d\n", TTL);
    printf("Tong gia tri ben trong balo: %d\n", TGT);
}

int main() {
    int n, W;
    dv* ds = readFromFile(&n, &W);
    bang f, x;
    tao_bang(ds, n, W, f, x);
    in_bang(f, x, n, W);
    tra_bang(ds, n, x, W);
    in_ds_dv(ds, n, W);
    in_phuong_an(ds, n);
}