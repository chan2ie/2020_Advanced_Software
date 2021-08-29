#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Bisection Method
**********************************************/
void program1_3(FILE* fp) {
	double a0 = 0;
	double b0 = 0;

	printf("============ Bisection Method =============\n\n");
	printf("Input the initial value a0: ");
	scanf("%lf", &a0);
	printf("Input the initial value b0: ");
	scanf("%lf", &b0);

	double mid = (a0 + b0)/2;
	double last_mid = mid;
	double an = a0;
	double bn = b0;

	int counter = 0;

	double ans = 0.6819748188604164429;

	fprintf(fp, "============ Bisection Method =============\n\n");
	fprintf(fp, "Initial value - a0: %lf\n", a0);
	fprintf(fp, "Initial value - b0: %lf\n", b0);
	fprintf(fp, "\n i          an+bn/2             |f(an+bn/2)|    \n");
	
	printf("\n i             xn1                 |f(xn1)|      \n");
	while (1) {
		last_mid = mid;
		mid = (an + bn) / 2;
		printf("%2d  ", counter);
		printf("%20.18e  ", mid);
		printf("%12.10e  \n", fabs(_f(mid)));
		//printf("%12lf  \n", fabs(mid - ans) / fabs(last_mid - ans));

		fprintf(fp, "%2d  ", counter);
		fprintf(fp, "%20.18e  ", mid);
		fprintf(fp, "%12.10e  \n", fabs(_f(mid)));

		if (fabs(_f(mid)) < DELTA) break;
		if (counter >= Nmax) break;
		if (counter != 0 && fabs(_f(last_mid) - _f(mid)) < EPSILON) break;
		if (_f(mid) == 0) break;

		if (_f(an) * _f(mid) >= 0) an = mid;
		else bn = mid;

		counter++;

	}

	printf("\n\n");
	fprintf(fp, "\n\n");

}
