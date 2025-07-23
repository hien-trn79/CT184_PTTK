#include <stdio.h>
#include <malloc.h>

typedef struct {
    char tenDV[25];
    int TL, GT, PA;
} dv;

typedef int bang[50][100];

dv* readFromFile(int *n, int *W) {
    dv* ds = (dv*) malloc (sizeof(dv));
    FILE * file = fopen("CBL1_3.txt", "r");
    int i=0;
    if(file == NULL) printf("Co loi mo file\n");
    else {
        fscanf(file, "%d", W);
        while(!feof(file)) {
            fscanf(file, "%d%d%[^\n]", &ds[i].TL, &ds[i].GT, &ds[i].tenDV);
            ds[i].PA = 0;
            i++;

            ds = (dv*) realloc (ds, sizeof(dv) * (i+1));
        } 
    }
    *n = i;
    return ds;
} 

void in_ds_dv(dv* ds, int n, int W) {
    printf("Trong luong ban dau cua do vat: %d\n", W);
    int TTL = 0;
    printf("| %3s | %-20s | %3s | %3s | %3s |\n", "STT", "Ten do vat", "SL", "TL", "PA");
    for(int i=0; i<n; i++) {
        TTL += ds[i].PA * ds[i].TL; 
        printf("| %2d  | %-20s | %2d  | %2d  | %2d  |\n", i+1, ds[i].tenDV, ds[i].TL, ds[i].GT, ds[i].PA);
    }
}

void taoBang(dv *ds, int n, int W, bang F, bang X) {
    for(int V = 0; V<=W; V++) {
        X[0][V] = V / ds[0].TL;
        F[0][V] = X[0][V] * ds[0].GT;
    }
    for(int k = 1; k<n; k++) {
        for(int V = 0; V <= W; V++) {
            int fmax = F[k-1][V];
            int xmax = 0;
            int yk = V / ds[k].TL;
            for(int xk = 0; xk <= yk; xk++) {
                if(F[k-1][V - xk*ds[k].TL] + xk*ds[k].GT > fmax) {
                    fmax = F[k-1][V - xk*ds[k].TL] + xk*ds[k].GT;
                    xmax = xk;
                }
            }
            F[k][V] = fmax;
            X[k][V] = xmax;
        }
    }
}

void traBang(dv* ds, int n, int W, bang X) {
    int V = W;
    int k = n-1;
    while(V>=0 && k >=0) {
        ds[k].PA = X[k][V];
        V -= X[k][V] * ds[k].TL;
        k--;
    }
}

void in_phuong_an(dv* ds, int n, int W) {
    int TTL = 0, TGT = 0;
    printf("Phuong an: (");
    for(int i=0; i<n-1; i++) {
        printf("%d; ", ds[i].PA);
        TTL += ds[i].PA * ds[i].TL;
        TGT += ds[i].PA * ds[i].GT;
    }
    printf(")\n");
    printf("Tong trong luong bo vao balo: %d\n", TTL);
    printf("Tong gia tri cua balo: %d\n", TGT);
}

void in_bang(int n, int W, bang F, bang X) {
    for(int i=0; i<n; i++) {
        printf("| %2d  ||", i+1);
        for(int j=0; j<=W; j++) {
            printf(" %2d  | %2d  | ", F[i][j], X[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n, W;
    dv* ds = readFromFile(&n, &W);
    bang F, X;
    taoBang(ds, n, W, F, X);
    in_bang(n, W, F, X);
    traBang(ds, n, W, X);
    in_ds_dv(ds, n, W);
    in_phuong_an(ds, n, W);
}