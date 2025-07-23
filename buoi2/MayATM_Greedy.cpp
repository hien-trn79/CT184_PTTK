#include <stdio.h>
#include <malloc.h>

typedef struct {
    char tenTien[25];
    int MG, PA;
} Tien;

void swap(Tien* a, Tien *b) {
    Tien temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(Tien *ds, int n) {
    for(int i=0; i<n; i++) {
        for(int j=n-1; j>i; j--) {
            if(ds[j].MG > ds[j-1].MG) swap(&ds[j], &ds[j-1]);
        }
    }
}

Tien* readFromFile(int *n) {
    Tien* ds = (Tien*) malloc (sizeof(Tien));
    int i=0;
    FILE* file = fopen("dataATM.txt", "r");
    if(file != NULL) {
        while(!feof(file)) {
            fscanf(file, "%d%[^\n]", &ds[i].MG, &ds[i].tenTien);
            ds[i].PA = 0;
            i++;

            ds = (Tien*) realloc(ds, sizeof(Tien) * (i+1));
        }
    }
    *n = i;
    return ds;
}

void in_ds(Tien* ds, int n) {
    printf("| %3s | %8s | %20s | %3s |\n", "STT", "MG", "Ten Tien", "PA");
    for(int i=0; i<n; i++) {
        printf("| %2d  | %8d | %-20s | %2d  |\n", i+1, ds[i].MG, ds[i].tenTien, ds[i].PA);
    }
}

void in_phuong_an(Tien* ds, int n, int TienBanDau) {
    printf("So tien ban dau: %d\n", TienBanDau);
    int sum = 0;
    printf("DANH SACH CAC PHUONG AN\n");
    for(int i=0; i<n; i++) {
        sum += ds[i].PA * ds[i].MG;
        printf("| %2d  | %8d | %-20s | %2d  |\n", i+1, ds[i].MG, ds[i].tenTien, ds[i].PA);
    }
    printf("Tong tien rut duoc: %d\n", sum);
}

void greedy(Tien* ds, int n, int TienBanDau) {
    int money = TienBanDau;
    int i=0; 
    while(money > 0 && i < n) {
        ds[i].PA = money / ds[i].MG;
        money -= ds[i].PA * ds[i].MG;
        i++;
    }
}

int main() {
    int n;
    Tien* ds = readFromFile(&n);

    bubble_sort(ds, n);
    printf("Nhap so tien can rut ?");
    int money;
    scanf("%d", &money);
    greedy(ds, n, money);
    in_phuong_an(ds, n, money);
}