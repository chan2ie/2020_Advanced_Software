#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Secant Method
**********************************************/
void program1_2(FILE* fp) {
	double xnp, xn, xnn;

	printf("============== Secant Method ==============\n\n");

	printf("Input the initial values x0: ");
	scanf("%lf", &xn);
	printf("Input the initial values x1: ");
	scanf("%lf", &xnn);

	double fab_f_xn1;
	int counter = 0;
	double ans = 3.0571035499;

	fprintf(fp, "============== Secant Method ==============\n\n");
	fprintf(fp, "Initial values - x0: %lf, x1: %lf\n", xn, xnn);
	fprintf(fp, "\n i             xn1                 |f(xn1)|      \n");

	printf("\n i             xn1                 |f(xn1)|      \n");
	while (1) {
		fab_f_xn1 = fabs(_f(xnn));

		printf("%2d  ", counter);
		printf("%20.18e  ", xnn);
		printf("%12.10e \n", fab_f_xn1);
		//printf("%12lf  \n", fabs(xnn - ans) / pow(fabs(xn - ans), 1.62));

		fprintf(fp, "%2d  ", counter);
		fprintf(fp, "%20.18e  ", xnn);
		fprintf(fp, "%12.10e  \n", fab_f_xn1);

		if (fab_f_xn1 < DELTA) break;
		if (counter >= Nmax) break;
		if (counter != 0 && fabs(_f(xnn) - _f(xn)) < EPSILON) break;

		xnp = xn;
		xn = xnn;
		counter++;

		xnn = xn - _f(xn) * (xn - xnp) / (_f(xn) - _f(xnp));
	}
	printf("\n\n");
	fprintf(fp, "\n\n");
}
