#include <stdio.h>
#include <malloc.h>

typedef struct {
    char tenDV[25];
    float TL, GT, DG;
    int PA;
} DV;

DV *readFromFile(float *W, int *n)
{
    DV *dsdv = (DV *)malloc(sizeof(DV));
    FILE *file = fopen("CBL1.txt", "r");
    fscanf(file, "%f", W);
    int i = 0;
    if (file != NULL)
    {
        while (!feof(file))
        {
            fscanf(file, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].tenDV);
            dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
            dsdv[i].PA = 0;
            i++;

            dsdv = (DV *)realloc(dsdv, sizeof(DV) * (i + 1));
        }
    }
    *n = i;
    return dsdv;
}

void swap(DV *a, DV *b)
{
    DV temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(DV *dsdv, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (dsdv[j].DG > dsdv[j - 1].DG)
                swap(&dsdv[j], &dsdv[j - 1]);
        }
    }
}

void in_dsdv(DV *dsdv, int n, float W)
{
    float TTL = 0.0f;
    float TGT = 0.0f;
    printf("Tong trong luong ban dau cau balo: %.2f\n", W);
    printf("| %3s | %-18s | %5s | %5s | %5s | %3s |\n", "STT", "Ten do vat", "TL", "GT", "DG", "PA");
    for (int i = 0; i < n; i++)
    {
        TTL += dsdv[i].TL * dsdv[i].PA;
        TGT += dsdv[i].PA * dsdv[i].GT;
        printf("| %2d  | %-18s | %5.2f | %5.2f | %5.2f | %2d  |\n", i + 1, dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].PA);
    }

    printf("Tong trong luong trong balo: %.2f\n", TTL);
    printf("Tong gia tri cua balo: %.2f\n", TGT);
}

void tao_nut_goc(float W, float *V, float *CT, float DG_Max, float *GLNTT, float *TGT)
{
    *V = W;
    *CT = *V * DG_Max;
    *TGT = 0.0f;
    *GLNTT = 0.0f;
}

void update_Can(float *GLNTT, float TGT, int x[], DV *dsdv, int n)
{
    if (TGT > *GLNTT)
    {
        *GLNTT = TGT;
        printf("GLNTT = %.2f\n", *GLNTT);
        for (int i = 0; i < n; i++)
        {
            printf("Cap nhat dv %d = %d\n", i + 1, x[i]);
            dsdv[i].PA = x[i]; // cap nhat lai phuong an cua duong di moi
        }
    }
}

void nhanh_can(int i, float *TGT, float *CT, float *V, float *GLNTT, int x[], DV *dsdv, int n)
{
    int j;
    int yk;
    yk = *V / dsdv[i].TL;
    for (j = yk; j >= 0; j--)
    {
        *TGT = *TGT + j * dsdv[i].GT;
        *V = *V - j * dsdv[i].TL;
        *CT = *TGT + *V * dsdv[i + 1].DG;

        printf("--- xet co %d vat----\n", j);
        printf("TGT = %.2f; W = %.2f; CT = %.2f\n", *TGT, *V, *CT);
        printf("GLNTT hien tai = %.2f\n", *GLNTT);
        printf("Don gia vat ke tiep = %.2f\n", dsdv[i + 1].DG);

        if (*CT > *GLNTT)
        {
            x[i] = j;
            printf("x[%d] = %d\n", i, x[i]);
            if ((i == n - 1) || (*V == 0))
            {
                printf("=> cap nhat lai can\n");
                update_Can(GLNTT, *TGT, x, dsdv, n);
            }
            else
            {
                printf("==> Tiep tuc phan nhanh i+1 = %d\n", i + 1);
                nhanh_can(i + 1, TGT, CT, V, GLNTT, x, dsdv, n);
            }
        }
        x[i] = 0;
        *TGT = *TGT - j*dsdv[i].GT;
        *V = *V + j*dsdv[i].TL;
    }

}

int main()
{
    float W;
    int n;
    DV *ds = readFromFile(&W, &n);

    bubble_sort(ds, n);
    float TGT, CT, GLNTT, V;
    int x[n];
    tao_nut_goc(W, &V, &CT, ds[0].DG, &GLNTT, &TGT);
    nhanh_can(0, &TGT, &CT, &V, &GLNTT, x, ds, n);
    in_dsdv(ds, n, W);
}