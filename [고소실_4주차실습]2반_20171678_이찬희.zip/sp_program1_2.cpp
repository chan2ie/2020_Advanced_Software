#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Secant Method
**********************************************/
void sp_program1_2(FILE* fp) {
	float xnp, xn, xnn;

	for (int i = 0; i < 1; i++) {
		printf("============== SP Secant Method ==============\n\n");

		printf("Input the initial values x0: ");
		scanf("%f", &xn);
		printf("Input the initial values x1: ");
		scanf("%f", &xnn);

		float fab_f_xn1;
		int counter = 0;

		fprintf(fp, "============== SP Secant Method ==============\n\n");
		fprintf(fp, "Initial values - x0: %f, x1: %f\n", xn, xnn);
		fprintf(fp, "\n i             xn1                 |f(xn1)|      \n");

		printf("\n i             xn1                 |f(xn1)|      \n");
		while (1) {
			fab_f_xn1 = float(fabsf(_sp_f(xnn)));

			printf("%2d  ", counter);
			printf("%20.18e  ", xnn);
			printf("%12.10e  \n", fab_f_xn1);

			fprintf(fp, "%2d  ", counter);
			fprintf(fp, "%20.18e  ", xnn);
			fprintf(fp, "%12.10e  \n", fab_f_xn1);

			if (fab_f_xn1 < DELTA) break;
			if (counter >= Nmax) break;
			if (counter != 0 && fabsf(_sp_f(xnn) - _sp_f(xn)) < EPSILON) break;

			xnp = xn;
			xn = xnn;
			counter++;

			xnn = xn - _sp_f(xn) * (xn - xnp) / (_sp_f(xn) - _sp_f(xnp));
		}
		printf("\n\n");
		fprintf(fp, "\n\n");
	}
}
