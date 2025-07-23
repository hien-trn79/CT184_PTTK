#include <stdio.h>

typedef struct {
    float doDai;
    int dau, cuoi;
} canh;

void swap(canh *a, canh *b) {
    canh temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(canh* dscanh, int n) {
    for(int i=0; i<n; i++) {
        for(int j=n-1; j>i; j--) {
            if(dscanh[j].doDai < dscanh[j-1].doDai) swap(&dscanh[j], &dscanh[j-1]);
        }
    }
}
//Tao dinh cha cho tung nut
void init_forest(int parent[], int n) {
    for(int i=0; i<n; i++) parent[i] = i;
}

void readFile(canh ds[], int n, FILE* file) {
    int temp;
    int k = 0;
    if(file != NULL) {
        for(int i=0; i<n; i++) {
            for(int j=i; j<n; j++) {
                if(j == i) {
                    for(int t=0; t<=j; t++) {
                        fscanf(file, "%f", &temp);
                    }
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

void in_ds_canh(canh ds[], int n, int la_pa) {
    float sum=0.0f;
    for(int i=0; i<n; i++) {
        printf("%3d | %c%c | %.2f\n", i+1, ds[i].dau+97, ds[i].cuoi + 97, ds[i].doDai);
        if(la_pa) sum += ds[i].doDai;
    }
    if(la_pa) printf("Tong do dai cac canh: %5.2f\n", sum);
    printf("\n");
}

int find_root(int parent[], int u) {
    while(u != parent[u]) {
        parent[u] = u;
    }
    return u;
}

void update__forest(int parent[], int root1, int root2) {
    parent[root2] = parent[root1];
}

int dinhBac3(canh pa[], int n, canh canhMoi) {
    int cnt_dau = 1, cnt_cuoi = 1;
    for(int i=0; i<n; i++) {
        if(canhMoi.dau == pa[i].dau || canhMoi.dau == pa[i].cuoi) {
            cnt_dau++;
        }
        if(canhMoi.cuoi == pa[i].dau || canhMoi.cuoi == pa[i].cuoi) {
            cnt_cuoi++;
        }
    }
    if(cnt_dau == 3 || cnt_cuoi == 3) {
        return 1;
    }
    else {
        return 0;
    }
}

int chutrinh(int parent[], int root1, int root2) {
    if(parent[root1] == parent[root2]) {
        return 1;
    } else {
        return 0;
    }
}

void in_parent(int parent[], int n) {
    for(int i=0; i<n; i++) printf("pa[%c] => %c\n", i + 97, parent[i] + 97);
}

void greedy(canh ds[], int n, canh pa[]) {
    int k = 0, i;
    int parent[n];
    int r_dau, r_cuoi;
    init_forest(parent, n);
    for(i=0; i<n*(n-1)/2 && k < n-1; i++) {
        r_dau = parent[ds[i].dau];
        r_cuoi = parent[ds[i].cuoi];
        if(!dinhBac3(pa, k, ds[i]) && !chutrinh(parent, r_dau, r_cuoi)) {
            pa[k] = ds[i];
            pa[k].doDai = ds[i].doDai;
            update__forest(parent, r_dau, r_cuoi);
            k++;
        }
    }
    for(; i<n*(n-1)/2; i++) {
        r_dau = parent[ds[i].dau];
        r_cuoi = parent[ds[i].cuoi];
        if(!dinhBac3(pa, k, ds[i]) && chutrinh(parent, r_dau, r_cuoi)) {
            pa[n-1] = ds[i];
            pa[n-1].doDai = ds[i].doDai;
            break;
        }
    }
}

int main() {
    printf("Thuat toan TSP\n");
    int n;
    FILE* file = fopen("TSP.txt", "r");
    fscanf(file, "%d", &n);
    canh ds[n*(n-1)/2];
    readFile(ds, n, file);
    printf("DANH SACH CANH TRUOC KHI SAP XEP\n");
    in_ds_canh(ds, n*(n-1)/2, 0);
    
    bubble_sort(ds, n*(n-1)/2);
    printf("DANH SACH CAC CANH SAU KHI DUOC SAP XEP\n");
    in_ds_canh(ds, n*(n-1)/2, 0);

    canh pa[n];
    greedy(ds, n, pa);

    float sum = 0.0f;
    printf("DANH SACH PHUONG AN\n");
    in_ds_canh(pa, n, 1);
}