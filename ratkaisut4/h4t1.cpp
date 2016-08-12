//Harjoitus 4, tehtava 1

#include <iostream>
#include <math.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>

using namespace std;

int main()
{

    double x1[] = {1,2,3};
    double m_data[12];

    for (int i=0; i<3; i++)
    {
        for (int j =0; j<3; j++)
        {
            m_data[3*i+j] = 2*pow(x1[i],2);
        }
    }
    double b_data[] = {1,2,3};

    gsl_matrix_view m
    = gsl_matrix_view_array (m_data, 3, 3);

    gsl_matrix * m1 = gsl_matrix_alloc(3,3);
    gsl_vector * s = gsl_vector_alloc(3);
gsl_vector * work = gsl_vector_alloc(3);

  gsl_vector_view b
    = gsl_vector_view_array (b_data, 3);

  gsl_vector * x = gsl_vector_alloc (3);

  gsl_permutation * p = gsl_permutation_alloc (3);

  gsl_linalg_SV_decomp (&m.matrix, m1, s, work);

  gsl_linalg_SV_solve (&m.matrix, m1, s, &b.vector, x);

  printf ("x = \n");
  gsl_vector_fprintf (stdout, x, "%g");

  gsl_permutation_free (p);
  gsl_vector_free (x);
  return 0;
}


