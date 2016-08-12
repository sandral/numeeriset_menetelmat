//Harjoitus 2, tehtävä 3
#include <iostream>
#include <gsl_blas.h>
#include <gsl_matrix.h>
#include <gsl_math.h>
#include <gsl_linalg.h>

using namespace std;



int main()
{
double x[] = {1, 2, 1, 5, 1, 7, 1, 8};
double y[] = {1, 2, 3, 3};
int s;
    gsl_matrix * a = gsl_matrix_alloc(4,2);
    gsl_matrix * a_t = gsl_matrix_alloc(2,4);
    gsl_matrix * c = gsl_matrix_alloc(2,2);
    gsl_matrix * inv_c = gsl_matrix_alloc(2,2);
    gsl_matrix * b = gsl_matrix_alloc(4,1);
    gsl_matrix * res = gsl_matrix_alloc(2,1);
    gsl_matrix * m = gsl_matrix_alloc(2,4);
    gsl_permutation * perm = gsl_permutation_alloc(2);

    gsl_matrix_set_zero(c);
    cout<<"A: "<<endl;
    for (int i=0; i<4; i++) {
    for (int j=0; j<2; j++) {
    gsl_matrix_set(a, i, j, x[2*i+j]);
    gsl_matrix_set(a_t, j, i, x[2*i+j]);
    cout<<gsl_matrix_get(a, i, j)<<" ";
    }
    cout<<endl;
    }
    cout<<endl<<"Transpose of A: "<<endl;

    for (int i=0; i<2; i++) {
    for (int j=0; j<4; j++) {
    cout<<gsl_matrix_get(a_t, i, j)<<" ";
    }
    cout<<endl;
    }
    cout<<endl<<"b: "<<endl;

    for (int i=0; i<4; i++) {
    gsl_matrix_set(b, i, 0, y[i]);
    cout<<gsl_matrix_get(b, i, 0)<<endl;
    }

gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,
                    1.0, a_t, a,
                    1.0, c);

cout<<endl<<"A^T * A: "<<endl;

for (int i=0; i<2; i++) {
for (int j=0; j<2; j++) {
cout<<gsl_matrix_get(c, i, j)<<" ";
}
cout<<endl;
}

gsl_linalg_LU_decomp(c, perm, &s);
gsl_linalg_LU_invert(c, perm, inv_c);

cout<<endl<<"Inverse of A^T*A: "<<endl;
for (int i=0; i<2; i++) {
for (int j=0; j<2; j++) {
cout<<gsl_matrix_get(inv_c, i, j)<<" ";
}




cout<<endl;
}


gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,
                    1.0, c, a_t,
                    1.0, m);

cout<<endl<<"(A^T*A)^-1*A^T: "<<endl;
for (int i=0; i<2; i++) {
for (int j=0; j<4; j++) {
cout<<gsl_matrix_get(m, i, j)<<" ";
}
cout<<endl;
}


gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,
                    1.0, m, b,
                    1.0, res);

cout<<endl<<"x: "<<endl;
for (int i=0; i<2; i++) {
for (int j=0; j<1; j++) {
cout<<gsl_matrix_get(res, i, j)<<" ";
}
cout<<endl;
}
    return 0;

}
