#include "my_solver.h"

#define SOLNUMS 4
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_2(int* n, double* x, double* fvec, int* iflag)
{	//x[0]: w, x[1]: x, x[2]: y, x[3]: z
	/********************************/

	fvec[0] = x[1] + 10 * x[2] + 9;
	fvec[1] = sqrt(5) * (x[3] - x[0]) - 2 * sqrt(5);
	fvec[2] = pow(x[2] - 2 * x[3], 2) - 9;
	fvec[3] = sqrt(10) * pow(x[1] - x[0], 2) - 2 * sqrt(10);

	/********************************/
}

void program3_2(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.9, -0.9, 1.25, -1.25 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_found_3-2.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-5.txt");
		return;
	}

	/********************************/

	/**** 초기값 1: x0 = (0.9, -0.9, 1.25, -1.25) ****/

	hybrd1_(fcn3_2, &n, x, fvec, &tol, &info, wa, &lwa);

	fprintf(fp_w, "/**** 초기값: x0 = (0.9, -0.9, 1.25, -1.25) ****/\n\n");
	if (info != 1) {
		print_info(info, fp_w);
	}
	else {
		fvec[0] = x[1] + 10 * x[2] + 9;
		fvec[1] = sqrt(5) * (x[3] - x[0]) - 2 * sqrt(5);
		fvec[2] = pow(x[2] - 2 * x[3], 2) - 9;
		fvec[3] = sqrt(10) * pow(x[1] - x[0], 2) - 2 * sqrt(10);

		fprintf(fp_w, "w = %lf,  ", x[0]);
		fprintf(fp_w, "x = %lf,  ", x[1]);
		fprintf(fp_w, "y = %lf,  ", x[2]);
		fprintf(fp_w, "z = %lf  ", x[3]);
		fprintf(fp_w, "\n\n");

		for (int i = 0; i < 4; i++) {
			fprintf(fp_w, "|f%d(w, x, y, z)| = %10lf \n", i + 1, fabs(fvec[i]));
		}
	}

	/********************************/

	fclose(fp_w);
	printf("Done!\n");
}