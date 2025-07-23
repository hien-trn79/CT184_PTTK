#include <stdio.h>

typedef struct {
    float doDai;
    int dau, cuoi;
} canh;

void swap(canh* a, canh* b) {
    canh temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(canh ds[], int n) {
    for(int i=0; i<n*(n-1)/2; i++) {
        for(int j=n*(n-1)/2-1; j>i; j--) {
            if(ds[j].doDai < ds[j-1].doDai) swap(&ds[j], &ds[j-1]);
        }
    }
}

void in_ds_canh(canh ds[], int n, int la_pa) {
    float sum = 0.0f; 
    printf("----------------------\n");
    printf("| %3s | %2s | %5s |\n", "STT", "Canh", "Dodai");
    printf("----------------------\n");
    for(int i=0; i<n; i++) {
        printf("| %2d  |  %c%c  | %5.2f |\n", i+1, ds[i].dau + 97, ds[i].cuoi + 97, ds[i].doDai);
        if(la_pa) sum += ds[i].doDai;
    }
    if(la_pa) printf("Tong do dai cac canh : %.2f\n", sum);
}

void readFromFile(canh ds[], int *n) {
    int k=0;
    FILE* file = fopen("TSP1.txt", "r");
    if(file != NULL) {
        fscanf(file, "%d", n);
        for(int i=0; i<*n; i++) {
            float temp;
            for(int j=i; j<*n; j++) {
                if(i == j) {
                    for(int t=0; t<=j; t++) fscanf(file, "%f", &temp);
                } else {
                    fscanf(file, "%f", &ds[k].doDai);
                    ds[k].dau = i;
                    ds[k].cuoi = j;
                    k++;
                }
            }
        }
    }
}

void init_forest(int parent[], int n) {
    for(int i=0; i<n; i++) parent[i] = i;
}

void update_forest(int parent[], int root1, int root2) {
    parent[root2] = parent[root1];
}

int findRoot(int parent[], int u) {
    while(u != parent[u]) {
        u = parent[u];
    }
    return u;
}

int dinhBac3(canh pa[], int k, canh canhMoi) {
    int cnt1 = 1, cnt2 = 1;
    for(int i=0; i<k; i++) {
        if(canhMoi.dau == pa[i].dau || canhMoi.dau == pa[i].cuoi) cnt1++;
        if(canhMoi.cuoi == pa[i].dau || canhMoi.cuoi == pa[i].cuoi) cnt2++;
    }
    if(cnt1 == 3 || cnt2 == 3) return 1;
    else return 0;
}

int chu_trinh(int parent[], int root1, int root2) {
    return parent[root1] == parent[root2];
}

void greedy(canh ds[], int n, canh pa[]) {
    int parent[n];
    int k=0, i;
    int r_dau, r_cuoi;
    init_forest(parent, n);
    for(i=0; i<n*(n-1)/2 && k<n-1; i++) {
        r_dau = findRoot(parent, ds[i].dau);
        r_cuoi = findRoot(parent, ds[i].cuoi);

        if(!dinhBac3(pa, k, ds[i]) && !chu_trinh(parent, r_dau, r_cuoi)) {
            pa[k] = ds[i];
            k++;
            update_forest(parent, r_dau, r_cuoi);
        }
    }
    for(; i<n*(n-1)/2; i++) {
        r_dau = findRoot(parent, ds[i].dau);
        r_cuoi = findRoot(parent, ds[i].cuoi);

        if(!dinhBac3(pa, k, ds[i]) && chu_trinh(parent, r_dau, r_cuoi)) {
            pa[n-1] = ds[i];
            k++;
            update_forest(parent, r_dau, r_cuoi);
            break;
        }
    }
}

int main() {
    int n;
    canh ds[100];
    readFromFile(ds, &n);
    bubble_sort(ds, n);

    canh pa[n];
    greedy(ds, n, pa);
    in_ds_canh(pa, n, 1);
}