#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

double better_integration(double x_start, double x_end, double x[], double y[], int size, double integ[]) {
	if (x_start == x_end) {
		return 0;
	}

	double delta = x[1] - x[0];
	int start_idx = 0;
	int end_idx = size - 1;

	double result = 0;

	for (int i = 0; i < size - 1; i++) {
		if (x[i] < x_end && x_end < x[i + 1]) {
			end_idx = i;
		}
	}

	result = integ[end_idx];

	if (x_end > x[end_idx + 1]) {
		result -= delta * (y[end_idx - 1] + y[end_idx]) / 2;
		result += (y[end_idx] + (y[end_idx] - y[end_idx - 1]) / delta * (x_end - x[end_idx - 1]) / 2) * (x_end - x[end_idx - 1]);
	}

	return result;
}

double better_bisection(double x[], double y[], int size, double u, double integ[], int nmax = Nmax) {
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

		if (fabs(better_integration(0, mid, x, y, size, integ) - u) < DELTA) break;
		if (counter >= nmax) break;
		if (counter != 0 && fabs(better_integration(0, last_mid, x, y, size, integ) - better_integration(0, mid, x, y, size, integ)) < EPSILON) break;
		if (better_integration(0, mid, x, y, size, integ) == u) break;

		if ((better_integration(0, an, x, y, size, integ) - u) * (better_integration(0, mid, x, y, size, integ) - u) >= 0) an = mid;
		else bn = mid;

		counter++;
	}

	return mid;
}

double secant(double x[], double y[], int size, double u, double integ[]) {
	double xnp = 0;
	double xn = 0;
	double xnn = 1;

	int counter = 0;

	double fab_f_xn1;

	while (1) {
		fab_f_xn1 = fabs(better_integration(0, xnn, x, y, size, integ)-u);

		if (fab_f_xn1 < DELTA) break;
		if (counter >= Nmax) break;
		if (counter != 0 && fabs(better_integration(0, xnn, x, y, size, integ) - better_integration(0, xn, x, y, size, integ)) < EPSILON) break;

		xnp = xn;
		xn = xnn;
		counter++;

		xnn = xn - (better_integration(0, xn, x, y, size, integ) - u) * (xn - xnp) / ((better_integration(0, xn, x, y, size, integ) - u) - (better_integration(0, xnp, x, y, size, integ) - u));
	}

	return xnn;
}

double newton(double x[], double y[], int size, double u, double integ[], double initial_value) {
	double xn = initial_value;
	double xn1 = initial_value;

	double fab_f_xn1;
	int counter = 0;

	int s, idx = 0;

	while (1) {
		fab_f_xn1 = fabs((better_integration(0, xn1, x, y, size, integ) - u));

		if (fab_f_xn1 < DELTA) break;
		if (counter >= Nmax) break;
		if (counter != 0 && fabs((better_integration(0, xn1, x, y, size, integ) - u) - (better_integration(0, xn, x, y, size, integ) - u)) < EPSILON) break;

		xn = xn1;
		counter++;

		//printf("%2d  ", counter);
		//printf("%20.18e  ", xn);
		//printf("%12.10e \n", fab_f_xn1);

		for (int i = 0; i < size - 1; i++) {
			if (x[i] <= xn && xn <= x[i + 1]) {
				idx = i;
			}
		}

		s = (xn - x[idx]) / (x[idx + 1] - x[idx]);

		xn1 = xn - (better_integration(0, xn, x, y, size, integ) - u) / ((1 - s) * y[idx] + s * y[idx + 1]);
	}

	return xn1;
}

// HOMEWORK
void program2_3()
{
	FILE* fp_r, * fp_w, * fp_r2;

	fp_r = fopen("pdf_table.txt", "r");
	fp_r2 = fopen("random_event_table.txt", "r");
	fp_w = fopen("histogram.txt", "w");

	int num_sample, num_ran;
	double delta_x;
	double* x, * y, * rand;
	int* rand_count;
	fscanf(fp_r, "%d %lf\n", &num_sample, &delta_x);
	fscanf(fp_r2, "%d\n", &num_ran);

	x = (double*)malloc(num_sample * sizeof(double));
	y = (double*)malloc(num_sample * sizeof(double));
	rand = (double*)malloc(num_ran * sizeof(double));
	rand_count = (int*)calloc(num_sample, sizeof(int));

	double result = 0;

	for (int i = 0; i < num_sample; i++) {
		fscanf(fp_r, "%lf %lf\n", &(x[i]), &(y[i]));
	}

	for (int i = 0; i < num_ran; i++) {
		fscanf(fp_r2, "%lf\n", &(rand[i]));
		int idx = int(rand[i] / delta_x);
		rand_count[idx] += 1;
	}

	for (int i = 0; i < num_sample - 1; i++) {
		fprintf(fp_w, "[%lf, %lf]\t%lf\t%.2f\n", x[i], x[i + 1], y[i], rand_count[i] / float(num_sample));
	}

	fclose(fp_r);
	fclose(fp_r2);
	fclose(fp_w);
}


// HOMEWORK
void program2_2_a()
{
	__int64 start, freq, end;
	float resultTime = 0;

	FILE* fp_r, * fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	/***************************************************/

	int num_sample;
	double delta_x;
	double* x, * y, *integ;
	fscanf(fp_r, "%d %lf\n", &num_sample, &delta_x);

	x = (double*)malloc(num_sample * sizeof(double));
	y = (double*)malloc(num_sample * sizeof(double));
	integ = (double*)malloc(num_sample * sizeof(double));

	double result = 0;

	for (int i = 0; i < num_sample; i++) {
		fscanf(fp_r, "%lf %lf\n", &(x[i]), &(y[i]));
	}
	integ[0] = 0;
	for (int i = 0; i < num_sample - 1; i++) {
		result += (x[1] - x[0]) * (y[i] + y[i + 1]) / 2;
		integ[i + 1] = result;
	}

	CHECK_TIME_START;

	int num_rand;

	printf("Enter number of random numbers you want to create: ");
	scanf("%d", &num_rand);

	fprintf(fp_w, "%d\n", num_rand);

	double* u, * rand_nums;

	u = (double*)malloc(num_rand * sizeof(double));
	rand_nums = (double*)malloc(num_rand * sizeof(double));

	int i = 0, irand;
	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);


	// assign random double between [0, 1) to u
	for (int i = 0; i < num_rand; i++) {
		u[i] = float(rand()) / (RAND_MAX + 1);
		rand_nums[i] = better_bisection(x, y, num_sample, u[i], integ);
		fprintf(fp_w, "%20.18e\n", rand_nums[i]);
	}

	CHECK_TIME_END(resultTime);

	for (int i = 0; i < num_rand; i++) {
		fprintf(fp_w, "%20.18e\n", rand_nums[i]);
	}

	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);

	free(u);
	free(rand_nums);

	printf("The program2_2_a run time is %f(ms)..\n", resultTime * 1000.0);
}

void program2_2_b()
{
	__int64 start, freq, end;
	float resultTime = 0;

	FILE* fp_r, * fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	/***************************************************/

	int num_sample;
	double delta_x;
	double* x, * y, * integ;
	fscanf(fp_r, "%d %lf\n", &num_sample, &delta_x);

	x = (double*)malloc(num_sample * sizeof(double));
	y = (double*)malloc(num_sample * sizeof(double));
	integ = (double*)malloc(num_sample * sizeof(double));

	double result = 0;

	for (int i = 0; i < num_sample; i++) {
		fscanf(fp_r, "%lf %lf\n", &(x[i]), &(y[i]));
	}
	integ[0] = 0;
	for (int i = 0; i < num_sample - 1; i++) {
		result += (x[1] - x[0]) * (y[i] + y[i + 1]) / 2;
		integ[i + 1] = result;
	}

	CHECK_TIME_START;

	int num_rand;

	printf("Enter number of random numbers you want to create: ");
	scanf("%d", &num_rand);

	fprintf(fp_w, "%d\n", num_rand);

	double* u, * rand_nums;

	u = (double*)malloc(num_rand * sizeof(double));
	rand_nums = (double*)malloc(num_rand * sizeof(double));

	int i = 0, irand;
	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);


	// assign random double between [0, 1) to u
	for (int i = 0; i < num_rand; i++) {
		u[i] = float(rand()) / (RAND_MAX + 1);
		rand_nums[i] = secant(x, y, num_sample, u[i], integ);
		fprintf(fp_w, "%20.18e\n", rand_nums[i]);
	}

	CHECK_TIME_END(resultTime);

	for (int i = 0; i < num_rand; i++) {
		fprintf(fp_w, "%20.18e\n", rand_nums[i]);
	}

	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);

	free(u);
	free(rand_nums);

	printf("The program2_2_b run time is %f(ms)..\n", resultTime * 1000.0);

}

void program2_2_c() {
	__int64 start, freq, end;
	float resultTime = 0;

	FILE* fp_r, * fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	/***************************************************/

	int num_sample;
	double delta_x;
	double* x, * y, * integ;
	fscanf(fp_r, "%d %lf\n", &num_sample, &delta_x);

	x = (double*)malloc(num_sample * sizeof(double));
	y = (double*)malloc(num_sample * sizeof(double));
	integ = (double*)malloc(num_sample * sizeof(double));

	double result = 0;

	for (int i = 0; i < num_sample; i++) {
		fscanf(fp_r, "%lf %lf\n", &(x[i]), &(y[i]));
	}
	integ[0] = 0;
	for (int i = 0; i < num_sample - 1; i++) {
		result += (x[1] - x[0]) * (y[i] + y[i + 1]) / 2;
		integ[i + 1] = result;
	}

	CHECK_TIME_START;

	int num_rand;

	printf("Enter number of random numbers you want to create: ");
	scanf("%d", &num_rand);

	fprintf(fp_w, "%d\n", num_rand);

	double* u, * rand_nums;

	u = (double*)malloc(num_rand * sizeof(double));
	rand_nums = (double*)malloc(num_rand * sizeof(double));

	int i = 0, irand;
	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);


	// assign random double between [0, 1) to u
	for (int i = 0; i < num_rand; i++) {
		u[i] = double(rand()) / (RAND_MAX + 1);
		double initial_value = better_bisection(x, y, num_sample, u[i], integ, 5);
		rand_nums[i] = newton(x, y, num_sample, u[i], integ, initial_value);
	}


	CHECK_TIME_END(resultTime);

	for (int i = 0; i < num_rand; i++) {
		fprintf(fp_w, "%20.18e\n", rand_nums[i]);
	}


	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);

	free(u);
	free(rand_nums);

	printf("The program2_2_c run time is %f(ms)..\n", resultTime * 1000.0);
}

void program2_1_a() {
	int num;
	double lambda;

	double *u;
	double e = 0;
	double v = 0;


	printf("Enter the number of random numbers you want to create: ");
	scanf("%d", &num);
	printf("Enter lambda: ");
	scanf("%lf", &lambda);

	u = (double*)malloc(num * sizeof(double));

	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);

	for (int i = 0; i < num; i++) {
		u[i] = -log(1 - float(rand()) / (RAND_MAX + 1))/lambda;
		e += u[i] / num;
	}
	for (int i = 0; i < num; i++) {
		v += pow(u[i] - e, 2);
	}
	v /= num;

	printf("Expected Result\n");
	printf("E(x): %lf, V(x): %lf\n", 1 / lambda, 1 / pow(lambda, 2));
	printf("Actual Result\n");
	printf("E(x): %lf, V(x): %lf\n", e, v);
}