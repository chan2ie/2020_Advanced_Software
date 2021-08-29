#define _USE_MATH_DEFINES
#include <math.h>

double _f1(double x) {
	return x*x - 4*x + 4 - log(x);
}

double _fp1(double x) {
	return 2*x -4 - 1/x;
}

double _f2(double x) {
	return x + 1 - 2 * sin(M_PI * x);
}

double _fp2(double x) {
	return 1 - 2 * M_PI * cos(M_PI * x);
}

double _f3(double x) {
	return pow(x, 4) - 11.0 * pow(x, 3) + 42.35 * pow(x, 2) - 66.55 * x + 35.1384;
}

double _fp3(double x) {
	return 4 * pow(x, 3) - 11.0 * 3 * pow(x, 2) + 42.35 * 2 * x - 66.55;
}

double _f4(double x) {
	return log(x) - 1;
}

double _fp4(double x) {
	return 1 / x;
}