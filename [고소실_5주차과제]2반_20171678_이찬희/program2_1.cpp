#include "my_solver.h"

double integration(double x_start, double x_end, double x[], double y[], int size) {
	if (x_start == x_end) {
		return 0;
	}

	double delta = x[1] - x[0];
	int start_idx = 0;
	int end_idx = size - 1;

	double result = 0;

	for (int i = 0; i < size-1; i++) {
		if (x[i] < x_start && x_start < x[i + 1]) {
			start_idx = i + 1;
		}
		if (x[i] < x_end && x_end < x[i + 1]) {
			end_idx = i;
		}
	}

	for (int i = start_idx; i < end_idx; i++) {
		result += delta * (y[i] + y[i + 1]) / 2;
		//printf("idx: %d, %lf\n", i, result);
	}

	if (x_start < x[start_idx]) {
		result += (y[start_idx] + (y[start_idx + 1] - y[start_idx]) / delta * (x[start_idx] - x_start) / 2) * (x[start_idx] - x_start);
	}
	if (x_end > x[end_idx + 1]) {
		result -= delta * (y[end_idx - 1] + y[end_idx]) / 2;
		result += (y[end_idx] + (y[end_idx] - y[end_idx - 1]) / delta * (x_end - x[end_idx - 1]) / 2) * (x_end - x[end_idx - 1]);
	}

	return result;
}

void program2_1()
{
	FILE* fp_r, *fp_w;
	__int64 start, freq, end;
	float resultTime = 0;

	fp_r = fopen("sampling_table.txt", "r");
	if (fp_r == NULL) {
		printf("input file not found....\n");
		exit(0);
	}

	fp_w = fopen("pdf_table.txt", "w");

	/***************************************************/
	int num_sample;
	double delta_x;
	double* sample_x, * sample_y, *normal_x, *normal_y;
	fscanf(fp_r,"%d %lf\n", &num_sample, &delta_x);

	sample_x = (double*)malloc(num_sample * sizeof(double));
	sample_y = (double*)malloc(num_sample * sizeof(double));
	normal_x = (double*)malloc(num_sample * sizeof(double));
	normal_y = (double*)malloc(num_sample * sizeof(double));

	for (int i = 0; i < num_sample; i++) {
		fscanf(fp_r, "%lf %lf\n", &(sample_x[i]), &(sample_y[i]));
	}

	double x_min = sample_x[0];
	double x_max = sample_x[num_sample - 1];

	for (int i = 0; i < num_sample; i++) {
		normal_x[i] = (sample_x[i] - x_min) / (x_max - x_min);
	}

	double integ = integration(normal_x[0], normal_x[num_sample - 1], normal_x, sample_y, num_sample);

	for (int i = 0; i < num_sample; i++) {
		normal_y[i] = sample_y[i] / integ;
	}

	printf("*** Integrating the pdf from %.2f to %.2f = %lf\n", 0, 1.0, integration(0, 1, normal_x, normal_y, num_sample));
	printf("*** Integrating the pdf from %.2f to %.2f = %lf\n", 0, 0.25, integration(0, 0.25, normal_x, normal_y, num_sample));
	printf("*** Integrating the pdf from %.2f to %.2f = %lf\n", 0.25, 0.5, integration(0.25, 0.5, normal_x, normal_y, num_sample));
	printf("*** Integrating the pdf from %.2f to %.2f = %lf\n", 0.5, 0.75, integration(0.5, 0.75, normal_x, normal_y, num_sample));
	printf("*** Integrating the pdf from %.2f to %.2f = %lf\n", 0.75, 1.0, integration(0.75, 1, normal_x, normal_y, num_sample));


	fprintf(fp_w, "%d %lf\n", num_sample, normal_x[1] - normal_x[0]);

	for (int i = 0; i < num_sample; i++) {
		fprintf(fp_w, "%lf %lf\n", normal_x[i], normal_y[i]);
	}
	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
