#include "my_solver.h"

void print_info(int info, FILE* fp) {
	switch (info) {
	case 0:
		fprintf(fp, "Failed: Improper input parameters.\n");
		break;
	case 2:
		fprintf(fp, "Failed:  Number of calls to fcn with iflag = 1 has reached 100*(n+1).\n");
		break;
	case 3:
		fprintf(fp, "Failed: tol is too small. No further improvement in the approximate solution x is possible.\n");
		break;
	case 4:
		fprintf(fp, "Failed: Iteration is not making good progress.\n");
		break;
	}
}