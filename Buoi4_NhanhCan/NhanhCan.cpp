#include <stdio.h>
#define size 100

typedef struct {
    float doDai;
    int dau, cuoi, daDung;
} canh;

void swap(canh* a, canh* b) {
    canh temp = *a;
    *a = *b;
    *b = temp;
}

void readFromFile(canh ds[][size], int *n) {
    FILE* file = fopen("TSP1.txt", "r");
    if(file != NULL) {
        fscanf(file, "%d", n);
        for(int i=0; i<*n; i++) {
            for(int j=0; j<*n; j++) {
                fscanf(file, "%f", &ds[i][j].doDai);
                ds[i][j].dau = i;
                ds[i][j].cuoi = j;
                ds[i][j].daDung = 0;
            }
        }
    }
}

void in_Bang(canh ds[][size], int n) {
    printf("Danh sach cac canh trong do thi\n");
    for(int i=0; i<n; i++) {
        for(int j=i; j<n; j++) {
            printf("%c%c = %.2f\t", ds[i][j].dau + 97, ds[i][j].cuoi + 97, ds[i][j].doDai);
        }
        printf("\n");
    }
}

float canhMin(canh ds[][size], int n) {
    float min = 999999;
    for(int i=0; i<n; i++) {
        for(int j=i; j<n; j++) {
            if(i!=j && min > ds[i][j].doDai && !ds[i][j].daDung) {
                min = ds[i][j].doDai;
            }
        }
    }
    return min;
}

int co_chu_trinh(canh x[], int k, int ketiep) {
    int cycle = 0;
    int i=0;
    while(i<k && !cycle) {
        if(x[i].dau == ketiep) cycle = 1; 
        else i++;
    }
    return cycle;
}

float can_duoi(canh ds[][size], int n, int i, float TGT) {
    return TGT + (n-i)*canhMin(ds, n);
}

void cap_nhat_GNNTT(canh ds[][size],int n, float TGT, float *GNNTT, canh x[], canh pa[]) {
    x[n-1] = ds[x[n-2].cuoi][x[0].dau];
    TGT = TGT + x[n-1].doDai;
    if(TGT < *GNNTT) {
        *GNNTT = TGT;
        for(int i=0; i<n; i++) {
            pa[i] = x[i];
        }
    }
}

void nhanh_can(canh ds[][size], int n,int i, int dau, float *TGT, float *GNNTT, float *CD, canh x[], canh pa[]) {
    int j;      // j la dinh tiep theo
    for(int j=0; j<n; j++) {
        if(!co_chu_trinh(x, i, j) && !ds[dau][j].daDung && dau != j) {
            *TGT = *TGT + ds[dau][j].doDai;
            *CD = can_duoi(ds, n, i+1, *TGT);
            if(*CD < *GNNTT) {
                x[i] = ds[dau][j];
                ds[dau][j].daDung = 1;
                ds[j][dau].daDung = 1;
                 
                if(i == n-2) {
                    cap_nhat_GNNTT(ds, n, *TGT, GNNTT, x, pa);
                } else {
                    nhanh_can(ds, n, i+1, j, TGT, GNNTT, CD, x, pa);
                }
            }

            *TGT = *TGT - ds[dau][j].doDai;
            ds[dau][j].daDung = 0;
            ds[j][dau].daDung = 0;
        }
    }
}

void reset(canh ds[][size], int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) ds[i][j].daDung = 0;
    }
}

void inPhuongAn(canh pa[], int n) {
    float sum = 0.0f;
    printf("DANH SACH CAC PHUONG AN\n");
    for(int i=0; i<n; i++) {
        printf("%3d%c%c\t%.2f\n", i+1, pa[i].dau+97, pa[i].cuoi + 97, pa[i].doDai);
        sum += pa[i].doDai;
    }
    for(int i=0; i<n; i++) {
        printf("%c -> ", pa[i].dau+97);
    }
    printf("%c\n", pa[0].dau + 97);
    printf("=> Tong do dai cac canh trong chu trinh = %.2f\n", sum);
}

int main() {
   canh ds[size][size];
   int n;
    readFromFile(ds, &n);
    canh pa[n];
    canh x[n];
    char yn, c;
    while(1) {
        fflush(stdin);
        in_Bang(ds, n);
        float TGT = 0.0f, CD = 0.0f, GNNTT = 999999;
        printf("Chon dinh de xuat phat? (a - e)");
        scanf("%c", &c);
        getchar();
        nhanh_can(ds, n, 0, c-97, &TGT, &GNNTT, &CD, x, pa);
        inPhuongAn(pa, n);
        fflush(stdin);
        printf("Tiep tuc Y/N?");
        scanf("%c", &yn);
        if(yn =='N' || yn == 'n') break;
        reset(ds, n);
    }
}