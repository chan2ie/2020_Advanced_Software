#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Newton-Rapson Method
**********************************************/
void program1_1(FILE* fp) {
	double initial_value = 0;
	printf("========== Newton-Raphson Method ==========\n\n");
	printf("Input the initial value x0: ");
	scanf("%lf", &initial_value);

	double xn = initial_value;
	double xn1 = initial_value;

	double fab_f_xn1;
	int counter = 0;

	fprintf(fp, "========== SP Newton-Raphson Method ==========\n\n");
	fprintf(fp, "Initial value - x0: %lf\n", initial_value);
	fprintf(fp, "\n i             xn1                 |f(xn1)|      \n");

	printf("\n i             xn1                 |f(xn1)|      \n");
	while (1) {
		fab_f_xn1 = fabs(_f(xn1));

		printf("%2d  ", counter);
		printf("%20.18e  ", xn1);
		printf("%12.10e  \n", fab_f_xn1);

		fprintf(fp, "%2d  ", counter);
		fprintf(fp, "%20.18e  ", xn1);
		fprintf(fp, "%12.10e  \n", fab_f_xn1);

		if (fab_f_xn1 < DELTA) break;
		if (counter >= Nmax) break;
		if (counter != 0 && fabs(_f(xn1) - _f(xn)) < EPSILON) break;

		xn = xn1;
		counter++;

		xn1 = xn - _f(xn) / _fp(xn);
	}

	printf("\n\n");
	fprintf(fp, "\n\n");

}
