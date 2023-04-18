#include <stdlib.h>
#include <stdio.h>
#include "nml_matrix.h"

int	main(void)
{
	printf("\nInverse of a matrix:\n");
	float m_v[16] = {
		2.0, 7.0, 6.0, 1.0,
		9.0, 5.0, 0.0, 2.0,
		4.0, 3.0, 8.0, 3.0,
		3.0, 5.0, 1.0, 9.0
	};
	t_nml_mat *m = nml_mat_from(4,4,16, m_v);
	t_nml_mat_lup *lup = nml_mat_lup_solve(m);
	t_nml_mat* minv = nml_mat_inv(lup);
	t_nml_mat *mdotminv = nml_mat_dot(m, minv);

	printf("m=");
	nml_mat_print(m);
	printf("minv=");
	nml_mat_print(minv);
	printf("(%%e) m * minv=");
	nml_mat_print(mdotminv);
	printf("(%%f) m * minv=");
	nml_mat_print(mdotminv);

	nml_mat_free(m);
	nml_mat_free(minv);
	nml_mat_free(mdotminv);
	return 0;
}
