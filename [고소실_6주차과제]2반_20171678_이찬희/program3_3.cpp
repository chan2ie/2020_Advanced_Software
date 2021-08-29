#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_3_a(int* n, double* x, double* fvec, int* iflag)
{	//x[0]: x, x[1]: y
	/********************************/

	fvec[0] = (sin(x[0] * x[1] + M_PI / 6) + sqrt(pow(x[0], 2) * pow(x[1], 2) + 1)) / cos(x[0] - x[1]) + 2.8;
	fvec[1] = (x[0] * exp(x[0] * x[1] + M_PI / 6) - sin(x[0] - x[1])) / sqrt(pow(x[0], 2) * pow(x[1], 2) + 1) - 1.66;

	/********************************/
}

void program3_3(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { 20, 0 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_found_3-3.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-5.txt");
		return;
	}

	/********************************/

	/**** 초기값 1: x0 = (0.9, -0.9, 1.25, -1.25) ****/

	hybrd1_(fcn3_3_a, &n, x, fvec, &tol, &info, wa, &lwa);

	fprintf(fp_w, "/**** 초기값: x0 = (20.0, 0.0) ****/\n\n");
	if (info != 1) {
		print_info(info, fp_w);
	}
	else {
		fvec[0] = (sin(x[0] * x[1] + M_PI / 6) + sqrt(pow(x[0], 2) * pow(x[1], 2) + 1)) / cos(x[0] - x[1]) + 2.8;
		fvec[1] = (x[0] * exp(x[0] * x[1] + M_PI / 6) - sin(x[0] - x[1])) / sqrt(pow(x[0], 2) * pow(x[1], 2) + 1) - 1.66;

		fprintf(fp_w, "x = %lf,  ", x[0]);
		fprintf(fp_w, "y = %lf,  ", x[1]);
		fprintf(fp_w, "\n\n");

		for (int i = 0; i < 4; i++) {
			fprintf(fp_w, "|f%d(x, y)| = %10lf \n", i + 1, fabs(fvec[i]));
		}
	}

	/********************************/

	fclose(fp_w);
	printf("Done!\n");
}