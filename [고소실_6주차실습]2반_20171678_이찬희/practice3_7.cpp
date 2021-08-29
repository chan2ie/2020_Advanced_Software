#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_7(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/
	
	fvec[0] = 2 * pow(x[0], 3) - 12 * x[0] - x[1] - 1;
	fvec[1] = 3 * pow(x[1], 2) - 6 * x[1] - x[0] - 3;

	/********************************/
}

void practice3_7(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { -4.0, 5.0 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-7.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-7.txt");
		return;
	}

	/********************************/

	float delta = 0.1;

	double known_x[100];
	double known_y[100];

	int idx = 0;

	for (float i = -4.0; i <= 4; i += delta) {
		for (float j = -5.0; j <= 5; j += delta) {

			x[0] = i;
			x[1] = j;
			bool flag = false;

			//printf("/**** 초기값: x = %.2lf, y = %.2lf ****/\n\n", x[0], x[1]);

			hybrd1_(fcn3_7, &n, x, fvec, &tol, &info, wa, &lwa);

			if (info != 1) {
				//print_info(info, fp_w);
			}
			else {
				for (int k = 0; k < idx; k++) {
					if (fabs(known_x[k] - x[0]) < 0.000001 && fabs(known_y[k] - x[1]) < 0.000001) {
						flag = true;
						continue;
					}
				}
				if (!flag) {
					known_x[idx] = x[0];
					known_y[idx] = x[1];
					idx++;

					fprintf(fp_w, "/**** 초기값: x = %.2f, y = %.2f ****/\n\n", i, j);

					fvec[0] = 2 * pow(x[0], 3) - 12 * x[0] - x[1] - 1;
					fvec[1] = 3 * pow(x[1], 2) - 6 * x[1] - x[0] - 3;


					fprintf(fp_w, "x = %lf, y = %lf\n\n", x[0], x[1]);

					for (int k = 0; k < 2; k++) {
						fprintf(fp_w, "|f%d(x, y)| = %10lf \n", k + 1, fabs(fvec[k]));
					}
					fprintf(fp_w, "\n");
				}
			}
		}
	}

	/********************************/

	fclose(fp_w);
}