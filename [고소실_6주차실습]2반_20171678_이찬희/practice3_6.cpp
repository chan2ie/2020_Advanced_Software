#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_6(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag) {
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/

		fvec[0] = 3.0 * pow(x[0], 2) - 2.0 * pow(x[1], 2) - 1.0;
		fvec[1] = pow(x[0], 2) - 2.0 * x[0] + pow(x[1], 2) + 2.0 * x[1] - 8.0;

		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/

		fjac[0] = 6.0 * x[0];					fjac[2] = -4.0 * x[1];		
		fjac[1] = 2.0 * x[0] - 2.0;				fjac[3] = 2.0 * x[1] + 2.0;

		/********************************/
	}
}

void practice3_6(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { -4.0, 5.0 };	//need to initilize x0
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-6.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-6.txt");
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

			hybrj1_(fcn3_6, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

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

					fvec[0] = 3.0 * pow(x[0], 2) - 2.0 * pow(x[1], 2) - 1.0;
					fvec[1] = pow(x[0], 2) - 2.0 * x[0] + pow(x[1], 2) + 2.0 * x[1] - 8.0;


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

	printf("Done!\n");
}