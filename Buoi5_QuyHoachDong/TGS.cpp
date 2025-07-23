#include <stdio.h>

typedef int bang[20][20];

void readFromFile(bang a, int *n) {
    int i=0;
    FILE *file = fopen("TGS.txt", "r");
    if(file == NULL) printf("Loi mo file!");
    else {
        while(!feof(file)) {
            for(int j=0; j<=i; j++) {
                fscanf(file, "%d", &a[i][j]);
            }
            i++;
        }
    }
    *n = i;
    fclose(file);
}

void in_tamGiac(bang a, int n) {
    int i=0; 
    while(i<n) {
        for(int j=0; j<=i; j++) {
            printf("%d ", a[i][j]);
        }
        i++;
        printf("\n");
    }
}

int cs_max(bang a, int i, int j) {
    if(j == 0) return (a[i-1][0] > a[i-1][1]) ? 0: 1;
    if(i == j) return i-1;
    if(j == i-1) return (a[i-1][i-2] > a[i-1][i-1]) ? i-2: i-1;
    if(a[i-1][j-1] > a[i-1][j] && a[i-1][j-1] > a[i-1][j+1]) return j-1;
    if(a[i-1][j] > a[i-1][j-1] && a[i-1][j] > a[i-1][j+1]) return j;
    if(a[i-1][j+1] > a[i-1][j] && a[i-1][j+1] > a[i-1][j-1]) return j+1;
}

void taoBang(bang a, int n, bang f) {
    f[0][0] = a[0][0];
    f[1][0] = a[0][0] + a[1][0];
    f[1][1] = a[0][0] + a[1][1];

    for(int i=2; i<n; i++) {
        for(int j=0; j<=i; j++) {
            int k = cs_max(f, i, j);
            f[i][j] = f[i-1][k] + a[i][j];
        }
    }
}

int cs_max_dong_cuoi(int f[], int j) {
    int max = f[0];
    int maxIndex = 0;
    for(int i=1; i<=j; i++) {
        if(f[i] > max) {
            max = f[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

void traBang(bang a, int n, bang f, int pa[]) {
    int j = cs_max_dong_cuoi(f[n-1], n-1);
    pa[n-1] = a[n-1][j];
    for(int i=n-1; i>=1; i--) {
        j = cs_max(f, i, j);
        pa[i-1] = a[i-1][j];
    }
}

int giaPA(int pa[], int n) {
    int sum = 0;
    for(int i=0; i<n; i++) {
        sum += pa[i];
    }
    return sum;
}

void in_phuong_an(int pa[], int n) {
    for(int i=0; i<n-1; i++) {
        printf("%d => ", pa[i]);
    }
    printf("%d\n", pa[n-1]);
    printf("Tong gia tri duong di: %d", giaPA(pa, n));
}

int main() {
    int n;
    bang f;
    readFromFile(f, &n);
    bang x;
    int pa[n];
    taoBang(f, n, x);
    traBang(f, n, x, pa);
    in_phuong_an(pa, n);

    return 0;
}