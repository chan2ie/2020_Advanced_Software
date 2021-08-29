#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Newton-Rapson Method
**********************************************/
void sp_program1_1(FILE* fp) {
	float initial_value = 0;
	printf("========== SP Newton-Raphson Method ==========\n\n");
	printf("Input the initial value x0: ");
	scanf("%f", &initial_value);

	float xn = initial_value;
	float xn1 = initial_value;

	float fab_f_xn1;
	int counter = 0;
	fprintf(fp, "========== SP Newton-Raphson Method ==========\n\n");
	fprintf(fp, "Initial value - x0: %f\n", initial_value);
	fprintf(fp, "\n i             xn1                 |f(xn1)|      \n");

	printf("\n i             xn1                 |f(xn1)|      \n");
	while (1) {
		fab_f_xn1 = fabsf(_sp_f(xn1));

		printf("%2d  ", counter);
		printf("%20.18e  ", xn1);
		printf("%12.10e  \n", fab_f_xn1);

		fprintf(fp, "%2d  ", counter);
		fprintf(fp, "%20.18e  ", xn1);
		fprintf(fp, "%12.10e  \n", fab_f_xn1);

		if (fab_f_xn1 < DELTA) break;
		if (counter >= Nmax) break;
		if (counter != 0 && fabsf(_sp_f(xn1) - _sp_f(xn)) < EPSILON) break;

		xn = xn1;
		counter++;

		xn1 = xn - _sp_f(xn) / _sp_fp(xn);
	}

	printf("\n\n");
	fprintf(fp, "\n\n");
}
