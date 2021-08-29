#include "my_solver.h"

#define SOLNUMS 3
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_5(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/

	fvec[0] = 10.0 * x[0] - 2.0 * pow(x[1], 2) + x[1] - 2.0 * x[2] - 5.0;
	fvec[1] = 8.0 * pow(x[1], 2) + 4.0 * pow(x[2], 2) - 9.0;
	fvec[2] = 8.0 * x[1] * x[2] + 4.0;

	/********************************/
}

void practice3_5(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { 1.0, -1.0, 1.0 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-5.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-5.txt");
		return;
	}

	/********************************/

	/**** 초기값 1: x0 = (1.0, -1.0, 1.0) ****/
	x[0] = 1.0;
	x[1] = -1.0;
	x[2] = 1.0;

	hybrd1_(fcn3_5, &n, x, fvec, &tol, &info, wa, &lwa);

	fprintf(fp_w, "/**** 초기값 1: x0 = (1.0, -1.0, 1.0) ****/\n\n");
	if (info != 1) {
		print_info(info, fp_w);
	}
	else {
		fvec[0] = 10.0 * x[0] - 2.0 * pow(x[1], 2) + x[1] - 2.0 * x[2] - 5.0;
		fvec[1] = 8.0 * pow(x[1], 2) + 4.0 * pow(x[2], 2) - 9.0;
		fvec[2] = 8.0 * x[1] * x[2] + 4.0;

		for (int i = 0; i < 3; i++) {
			if (i != 0) {
				fprintf(fp_w, ", ");
			}
			fprintf(fp_w, "x%d = %lf ", i + 1, x[i]);
		}
		fprintf(fp_w, "\n\n");

		for (int i = 0; i < 3; i++) {
			fprintf(fp_w, "|f%d(x1, x2, x3)| = %10lf \n", i + 1, fabs(fvec[i]));
		}
	}

	/**** 초기값 2: x0 = (1.0, 1.0, -1.0) ****/
	x[0] = 1.0;
	x[1] = 1.0;
	x[2] = -1.0;

	hybrd1_(fcn3_5, &n, x, fvec, &tol, &info, wa, &lwa);

	fprintf(fp_w, "\n/**** 초기값 2: x0 = (1.0, 1.0, -1.0) ****/\n\n");
	if (info != 1) {
		print_info(info, fp_w);
	}
	else {
		fvec[0] = 10.0 * x[0] - 2.0 * pow(x[1], 2) + x[1] - 2.0 * x[2] - 5.0;
		fvec[1] = 8.0 * pow(x[1], 2) + 4.0 * pow(x[2], 2) - 9.0;
		fvec[2] = 8.0 * x[1] * x[2] + 4.0;

		for (int i = 0; i < 3; i++) {
			if (i != 0) {
				fprintf(fp_w, ", ");
			}
			fprintf(fp_w, "x%d = %lf ", i + 1, x[i]);
		}
		fprintf(fp_w, "\n\n");

		for (int i = 0; i < 3; i++) {
			fprintf(fp_w, "|f%d(x1, x2, x3)| = %10lf \n", i + 1, fabs(fvec[i]));
		}
	}

	/********************************/

	fclose(fp_w);
	printf("Done!\n");
}