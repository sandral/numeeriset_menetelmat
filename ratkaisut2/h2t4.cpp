//Harjoitus 2, tehtävä 4
#include <iostream>
#include <gsl_blas.h>
#include <gsl_matrix.h>
#include <gsl_linalg.h>
#include <gsl_cblas.h>
#include <gsl_blas.h>
#include <math.h>


using namespace std;

int upperTriangularInverse(double elem[], int n)
{
    gsl_matrix * m = gsl_matrix_alloc(n,n);
    gsl_matrix * inverse = gsl_matrix_alloc(n,n);
    gsl_permutation * p = gsl_permutation_alloc(n);
    int s;

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            if (i > j)
            {
                gsl_matrix_set(m, i, j, 0);
            }
            else
            {
                gsl_matrix_set(m, i, j, elem[i*n+j]);
            }
        }
    }
    gsl_linalg_LU_decomp(m, p, &s);
    gsl_linalg_LU_invert(m, p, inverse);

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            cout<<gsl_matrix_get(inverse, i, j)<<" ";
        }
        cout<<endl;
    }
    return 0;
}




int main()
{
    srand(time(NULL));
    int n=25;
    int k=sqrt(n);
    double xs[n];
    double ys[n];
    double zs[n];

    for (int i=0; i<n; i++)
    {
        int r = rand()%50+1;
        int r2 = rand()%50+1;
        xs[i] = r;
        ys[i] = r2;
        zs[i] = 0;
    }

    gsl_matrix * A = gsl_matrix_alloc(sqrt(n), sqrt(n));
    gsl_matrix * B = gsl_matrix_alloc(sqrt(n), sqrt(n));
    gsl_matrix * C = gsl_matrix_alloc(sqrt(n), sqrt(n));
    gsl_matrix_set_zero(C);


    for (int i=0; i<sqrt(n); i++)
    {
        for (int j=0; j<sqrt(n); j++)
        {
            if (i > j)
            {
                gsl_matrix_set(A, i, j, 0);
                gsl_matrix_set(B, i, j, 0);

            }
            else
            {
                gsl_matrix_set(A, i, j, xs[i*k+j]);
                gsl_matrix_set(B, i, j, ys[i*k+j]);
            }
        }
    }

    gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,
                    1.0, A, B, 1.0, C);

    cout<<"A*B: "<<endl;
    for (int i=0; i<sqrt(n); i++)
    {
        for (int j=0; j<sqrt(n); j++)
        {
            cout<<gsl_matrix_get(C, i, j)<<" ";
        }
        cout<<endl;
    }
    cout<<"A: "<<endl;

    for (int i=0; i<sqrt(n); i++)
    {
        for (int j=0; j<sqrt(n); j++)
        {
            cout<<gsl_matrix_get(A, i, j)<<" ";
        }
        cout<<endl;
    }
    cout<<"B: "<<endl;

    for (int i=0; i<sqrt(n); i++)
    {
        for (int j=0; j<sqrt(n); j++)
        {
            cout<<gsl_matrix_get(B, i, j)<<" ";
        }
        cout<<endl;
    }

    cout<<endl;
    cout<<"Inverse of upperdiagonal matrix A: "<<endl;
    upperTriangularInverse(xs, sqrt(n));


    return 0;
}
