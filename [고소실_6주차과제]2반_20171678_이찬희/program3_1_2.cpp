#include "my_solver.h"

#define SOLNUMS 4
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

double dc, db;
double dp11, dp12, dp13, dt1, dtr1;
double dp21, dp22, dp23, dt2, dtr2;
double dp31, dp32, dp33, dt3, dtr3;
double dp41, dp42, dp43, dt4, dtr4;

void fcn3_1_2(int* n, double* x, double* fvec, int* iflag)
{
	fvec[0] = pow(x[0] - dp11, 2) + pow(x[1] - dp12, 2) + pow(x[2] - dp13, 2) - pow(dc * (dtr1 + x[3] - dt1), 2);
	fvec[1] = pow(x[0] - dp21, 2) + pow(x[1] - dp22, 2) + pow(x[2] - dp23, 2) - pow(dc * (dtr2 + x[3] - dt2), 2);
	fvec[2] = pow(x[0] - dp31, 2) + pow(x[1] - dp32, 2) + pow(x[2] - dp33, 2) - pow(dc * (dtr3 + x[3] - dt3), 2);
	fvec[3] = pow(x[0] - dp41, 2) + pow(x[1] - dp42, 2) + pow(x[2] - dp43, 2) - pow(dc * (dtr4 + x[3] - dt4), 2);

}

void program3_1_2() {
	int n = SOLNUMS;
	double x[SOLNUMS] = { 0, 0, 0, 0 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	char readfile[256];
	char writefile[256];

	for (int i = 0; i < 3; i++) {
		sprintf(readfile, "GPS_signal_%d.txt", i);
		sprintf(writefile, "GPS_position_3-2_%d.txt", i);
		FILE* fp_r = fopen(readfile, "r");
		FILE* fp_w = fopen(writefile, "w");

		fscanf(fp_r, "%lf %lf\n", &dc, &db);
		fscanf(fp_r, "%lf %lf %lf %lf %lf\n", &dp11, &dp12, &dp13, &dt1, &dtr1);
		fscanf(fp_r, "%lf %lf %lf %lf %lf\n", &dp21, &dp22, &dp23, &dt2, &dtr2);
		fscanf(fp_r, "%lf %lf %lf %lf %lf\n", &dp31, &dp32, &dp33, &dt3, &dtr3);
		fscanf(fp_r, "%lf %lf %lf %lf %lf\n", &dp41, &dp42, &dp43, &dt4, &dtr4);

		for (int j = 0; j < SOLNUMS; j++) {
			printf("Enter x[%d]: ", j);
			scanf("%lf", &(x[j]));
		}

		fprintf(fp_w, "/**** �ʱⰪ %d: x0 = (%lf, %lf, %lf, %lf) ****/\n\n", i + 1, x[0], x[1], x[2], x[3]);

		hybrd1_(fcn3_1_2, &n, x, fvec, &tol, &info, wa, &lwa);

		if (info != 1) {
			print_info(info, fp_w);
		}
		else {
			fvec[0] = pow(x[0] - dp11, 2) + pow(x[1] - dp12, 2) + pow(x[2] - dp13, 2) - pow(dc * (dtr1 + x[3] - dt1), 2);
			fvec[1] = pow(x[0] - dp21, 2) + pow(x[1] - dp22, 2) + pow(x[2] - dp23, 2) - pow(dc * (dtr2 + x[3] - dt2), 2);
			fvec[2] = pow(x[0] - dp31, 2) + pow(x[1] - dp32, 2) + pow(x[2] - dp33, 2) - pow(dc * (dtr3 + x[3] - dt3), 2);
			fvec[3] = pow(x[0] - dp41, 2) + pow(x[1] - dp42, 2) + pow(x[2] - dp43, 2) - pow(dc * (dtr4 + x[3] - dt4), 2);

			for (int k = 0; k < SOLNUMS; k++) {
				if (k != 0) {
					fprintf(fp_w, ", ");
				}
				fprintf(fp_w, "x%d = %lf ", k + 1, x[k]);
			}
			fprintf(fp_w, "\n\n");

			for (int k = 0; k < SOLNUMS; k++) {
				fprintf(fp_w, "|f%d(x1, x2, x3)| = %10lf \n", i + 1, fabs(fvec[i]));
			}
		}
		fclose(fp_r);
		fclose(fp_w);
	}
}
