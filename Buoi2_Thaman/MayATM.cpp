#include <stdio.h>
#include <cstdlib>

typedef struct {
    char tenTien[25];
    int MG, PA;
} Tien;

Tien* readFromFile(int *n) {
    int i = 0;
    Tien* dslt = (Tien*) malloc (sizeof(Tien));
    FILE *file = fopen("mayATM.txt", "r");
    if(file != NULL) {
        while(!feof(file)) {
            fscanf(file, "%d%[^\n]", &dslt[i].MG, &dslt[i].tenTien);
            dslt[i].PA = 0;
            i++;
            dslt = (Tien*) realloc (dslt, sizeof(Tien) * (i+1));
        }
    }
    *n = i;
    return dslt;
}

void printTotal(Tien* dslt, int n, int TienBanDau) {
    int sum = 0;
    printf("%3s | %10s | %25s | %5s \n", "STT", "Menh Gia", "Ten Tien", "So To");
    for(int i=0; i<n; i++) {
        printf("%3d | %-10d | %-25s | %-5d\n", i+1, dslt[i].MG, dslt[i].tenTien, dslt[i].PA);
        sum+= dslt[i].PA * dslt[i].MG;
    }
    printf("Tien ban dau la: %d\n", TienBanDau);
    printf("Tong Tien ban rut duoc: %d", sum);
}

void swap(Tien *a, Tien* b) {
    Tien temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(Tien* ds, int n) {
    for(int i=0; i<n; i++) {
        for(int j=n-1; j>i; j--) {
            if(ds[j].MG > ds[j-1].MG) swap(&ds[j], &ds[j-1]);
        }
    }
}

void greedy(Tien* dslt, int n, int TienBandau) {
    int money = TienBandau;
    int i=0; 
    while(i < n && money > 0) {
        dslt[i].PA = money / dslt[i].MG;
        money = money - dslt[i].MG * dslt[i].PA;
        i++;
    }
}

int main() {
    int n;
    printf("Nhap vao so tien ban muon rut\n");
    int money;
    scanf("%d", &money);
    Tien* ds = readFromFile(&n);
    bubble_sort(ds, n);
    greedy(ds, n, money);
    printTotal(ds, n, money);
}