#include "my_solver.h"

void practice3_2() {
	char readfile[256];
	char writefile[256];

	int NCOEF, DEGREE;

	double* poly;
	double* zeror, * zeroi;
	long int fail;
	int i;
	int degree;

	for (int t = 1; t <= 6; t++) {

		sprintf(readfile, "polynomial_3-2_%d.txt", t);
		sprintf(writefile, "roots_3-2_%d.txt", t);

		FILE* fp_r = fopen(readfile, "r");
		if (fp_r == NULL) {
			printf("%s file open error...\n", readfile);
			return;
		}

		FILE* fp_w = fopen(writefile, "w");
		if (fp_w == NULL) {
			printf("%s file open error...\n", writefile);
			return;
		}

		fscanf(fp_r, "%d\n", &DEGREE);
		NCOEF = DEGREE + 1;
		degree = DEGREE;
		poly = (double*)malloc(sizeof(double) * NCOEF);
		zeror = (double*)malloc(sizeof(double) * DEGREE);
		zeroi = (double*)malloc(sizeof(double) * DEGREE);


		/********************************/
		for (int i = 0; i < NCOEF; i++) {
			fscanf(fp_r, "%lf\n", &(poly[i]));
		}

		rpoly_(poly, &degree, zeror, zeroi, &fail);

		if (fail) {
			fprintf(fp_w,"wrong\n");
		}
		else {
			fprintf(fp_w, "   |  zeror   |  zeroi   |  |f(x)|\n");
			for (i = 0; i < degree; i++) {
				fprintf(fp_w,"[%d]", i + 1);
				fprintf(fp_w, "%10f ", zeror[i]);
				fprintf(fp_w, "%10f ", zeroi[i]);
				if (zeroi[i] == 0) {
					double fx = 0;
					for (int j = 0; j < NCOEF; j++) {
						fx += poly[j] * pow(zeror[i], DEGREE - j);
					}
					fprintf(fp_w, "%10f ", fabs(fx));
				}
				fprintf(fp_w, "\n");
			}
		}

		/********************************/

		free(zeroi);
		free(zeror);
		free(poly);

		if (fp_r != NULL) fclose(fp_r);
		if (fp_w != NULL) fclose(fp_w);
	}
	printf("Done!\n");
}