#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

double bisection(double x[], double y[], int size, double u) {
	double an = 0;
	double bn = 1;
	double last_mid, mid;
	int counter = 0;

	mid = (an + bn) / 2;

	while (1) {
		last_mid = mid;
		mid = (an + bn) / 2;

		/*printf("%2d  %5lf  %5lf  ", counter, an, bn);
		printf("%20.18e  ", mid);
		printf("%12.10e  \n", fabs(integration(0, mid, x, y, size) - u));*/

		if (fabs(integration(0, mid,x ,y, size) - u) < DELTA) break;
		if (counter >= Nmax) break;
		if (counter != 0 && fabs(integration(0, last_mid, x, y, size) - integration(0, mid, x, y, size)) < EPSILON) break;
		if (integration(0, mid, x, y, size) == u) break;

		if ((integration(0, an, x, y, size) - u) * (integration(0, mid, x, y, size) - u) >= 0) an = mid;
		else bn = mid;

		counter++;
	}

	return mid;
}

void program2_2()
{
	FILE* fp_r, *fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	/***************************************************/

	int num_sample;
	double delta_x;
	double* x, * y;
	fscanf(fp_r, "%d %lf\n", &num_sample, &delta_x);

	x = (double*)malloc(num_sample * sizeof(double));
	y = (double*)malloc(num_sample * sizeof(double));

	for (int i = 0; i < num_sample; i++) {
		fscanf(fp_r, "%lf %lf\n", &(x[i]), &(y[i]));
	}

	int num_rand;

	printf("Enter number of random numbers you want to create: ");
	scanf("%d", &num_rand);

	fprintf(fp_w, "%d\n", num_rand);

	double* u, *rand_nums;

	u = (double*)malloc(num_rand * sizeof(double));
	rand_nums = (double*)malloc(num_rand * sizeof(double));

	int i = 0, irand;
	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);


	// assign random double between [0, 1) to u
	for (int i = 0; i < num_rand; i++) {
		u[i] = float(rand()) / (RAND_MAX + 1);
		rand_nums[i] = bisection(x, y, num_sample, u[i]);
		fprintf(fp_w, "%20.18e\n", rand_nums[i]);
	}


	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
