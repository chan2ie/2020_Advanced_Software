#include "my_solver.h"

extern void program1_1(FILE* fp); // Newton-Raphson Method
extern void program1_2(FILE* fp); // Secant Method
extern void program1_3(FILE* fp);

extern void sp_program1_1(FILE* fp); // Newton-Raphson Method
extern void sp_program1_2(FILE* fp); // Secant Method

double (*_f)(double);
double (*_fp)(double);

float (*_sp_f)(float);
float (*_sp_fp)(float);

int main() {
	FILE* fp;
	fp = fopen("result.txt", "w");

	_f = _f5;
	_fp = _fp5;

	_sp_f = _sp_f4;
	_sp_fp = _sp_fp4;

	program1_1(fp);

	fclose(fp);
}
