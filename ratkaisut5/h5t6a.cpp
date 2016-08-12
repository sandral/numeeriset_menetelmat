//Harjoitus 5, tehtävä 6
#include <iostream>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_vector.h>
#include <stdio.h>

using namespace std;



int main()
{

    double data[] = {1, 1, 1,
                     1, 2, 4,
                     1, 3, 9,
                     1, 3, 9,
                     1, 4, 16};

    double b_data[] = {2,2,3,5,6};

    gsl_matrix_view m
    = gsl_matrix_view_array (data, 5, 3);

    gsl_matrix * v = gsl_matrix_alloc(3, 3);
    gsl_vector * s = gsl_vector_alloc(3);
    gsl_vector * w = gsl_vector_alloc(3);

    gsl_vector_view b
    = gsl_vector_view_array (b_data, 5);

    gsl_vector * x = gsl_vector_alloc (3);

/*
    for (int i=0; i<5; i++) {
    for (int j=0; j<3; j++) {
    cout<<gsl_matrix_get(&m.matrix, i, j)<<" ";

    }
    cout<<endl;
    }
    cout<<endl;
*/
    gsl_linalg_SV_decomp (&m.matrix, v, s, w);

/*
    for (int i=0; i<5; i++) {
    for (int j=0; j<3; j++) {
    cout<<gsl_matrix_get(&m.matrix, i, j)<<" ";

    }
    cout<<endl;
    }

    cout<<endl;
    for (int i=0; i<3; i++) {
    for (int j=0; j<3; j++) {
    cout<<gsl_matrix_get(v, i, j)<<" ";

    }
    cout<<endl;
    }
    cout<<endl;

    for (int i=0; i<3; i++) {
    cout<<gsl_vector_get(s, i)<<" ";
    }
    cout<<endl;
*/
    gsl_linalg_SV_solve (&m.matrix, v, s, &b.vector, x);

    printf ("x = \n");
    gsl_vector_fprintf (stdout, x, "%g");


    return 0;
}
