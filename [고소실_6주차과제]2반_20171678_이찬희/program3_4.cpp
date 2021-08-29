#include "my_solver.h"

#define index_2d(row, col, dim) row*dim+col

void program3_4() {
    int i, ia, j, n, * l;
    float* a, * b, * x, * s;

    /********************************/

    FILE* fp_r = fopen("linear system 3-4.txt", "r");
    FILE* fp_w = fopen(" solution 3-4.txt", "w");

    fscanf(fp_r, "%d\n", &n);

    ia = n;

    l = (int*)malloc(n * sizeof(int));
    a = (float*)malloc(n * n * sizeof(float));
    b = (float*)malloc(n * sizeof(float));
    x = (float*)malloc(n * sizeof(float));
    s = (float*)malloc(n * sizeof(float));

    for (int i = 0; i < n * n; i++) {
        fscanf(fp_r, "%f\n", &(a[i]));
    }
    for (int i = 0; i < n; i++) {
        fscanf(fp_r, "%f\n", &(b[i]));
    }

    printf("***** Equation *****\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) printf("a[%d][%d] = %f, ", i, j, a[index_2d(j, i, n)]);
        printf("\n");
    }

    for (i = 0; i < n; i++) {
        printf("b[%d] = %f ", i, b[i]);
    }
    printf("\n");

    gespp_(&n, a, &ia, l, s);

    //printf("***** After LU-decomposition *****\n");
    //printf("s[0] = %f, s[1] = %f, s[2] = %f, s[2] = %f\n", s[0], s[1], s[2], s[3]);
    //printf("l[0] = %d, l[1] = %d, l[2] = %d, l[3] = %d\n", l[0], l[1], l[2], l[3]);

    /*for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) printf("a[%d][%d] = %f, ", i, j, a[index_2d(j, i, 4)]);
        printf("\n");
    }*/

    fprintf(fp_w, "%d\n", n);

    solve_(&n, a, &ia, l, b, x);
    printf("***** Solution *****\n");
    double ax_b = 0;
    double b_ = 0;
    double temp = 0;
    for (i = 0; i < n; i++) {
        fprintf(fp_w, "%.6e\n", x[i]);
        for (int j = 0; j < n; j++) {
            temp += a[index_2d(i, j, n)] * x[j];
        }
        ax_b += pow(temp, 2);
        b_ += pow(b[i], 2);
    }
    double error = ax_b / b_;
    fprintf(fp_w, "%.6e\n", error);

    /********************************/
    fclose(fp_r);
    fclose(fp_w);
    free(l);
    free(x);
    free(s);
    free(a);
    free(b);
}