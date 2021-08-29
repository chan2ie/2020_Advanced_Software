#include <stdio.h>
#include <random>
#include <time.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

#define N 50
double Taylor_series(double x, int n);
double Taylor_series_ex(double x, int n);
__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;

void main(void)
{
	CHECK_TIME_START;
	printf("*** f<-8.3> = %.6e \n", Taylor_series(-8.3, N));
	CHECK_TIME_END(compute_time);
	printf("*** compute time: %f ms\n", compute_time);

	CHECK_TIME_START;
	printf("*** f<-8.3> = %.6e \n", Taylor_series_ex(-8.3, N));
	CHECK_TIME_END(compute_time);
	printf("*** compute time: %f ms\n", compute_time);

	printf("*** f<-8.3> = %.6e \n", pow(2.71828182846, -8.3));
}




double Taylor_series(double x, int n)
{
	double res = 1.0;
	double xn;

	for (int i = 1; i < n; i++) {
		xn = pow(x, i);
		for (int j = 1; j <= i; j++) {
			xn /= j;
		}

		res += xn;
	}

	return res;
}


double Taylor_series_ex(double x, int n)
{
	float res = 0.0f;
	
	for (int i = n; i > 0; i--) {
		res = res * (float)x / i + 1;
	}

	return res;

}
