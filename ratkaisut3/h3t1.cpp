//Harjoitus 3, Tehtävä 1

#include <iostream>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>

using namespace std;

//Function to solve upper triangular matrix linear system
double usolve(double l[], double b[], int n)//l list of matrix elements, b vector, n number of rows.
{
    double xs[n];

    gsl_matrix * m = gsl_matrix_alloc(n, n);
    gsl_matrix_set_zero(m);

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            if (i <= j)
            {
                gsl_matrix_set(m, i, j, l[i*n+j]);
            }
        }
    }

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            cout<<gsl_matrix_get(m, i, j)<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    xs[0] = b[0] / gsl_matrix_get(m, 0, 0);


    double temp;
    for (int i=1; i<n; i++) {

    for (int j=0; j<i; j++) {
        temp = 0;
        temp +=  xs[j] * gsl_matrix_get(m, i, j);
    }
    xs[i] <- temp / gsl_matrix_get(m, i, i);
    }


    for (int i=0; i<n; i++) {
    cout<<endl<<"x"<<i+1<<": "<<xs[i]<<endl<<endl;
    }

    return 0;
}

//function to solve lower triangular matrix linear system
double lsolve(double l[], double b[], int n)//l list of matrix elements, b vector, n number of rows/columns.
{
    double xs[n];

    gsl_matrix * m = gsl_matrix_alloc(n, n);
    gsl_matrix_set_zero(m);

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            if (i >= j)
            {
                gsl_matrix_set(m, i, j, l[i*n+j]);
            }
        }
    }

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            cout<<gsl_matrix_get(m, i, j)<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    xs[0] = b[0] / gsl_matrix_get(m, n-1, n-1);


    double temp;
    for (int i=n-1; i>=0; i--) {

    for (int j=n-1; j<i; j--) {
        temp = 0;
        temp +=  xs[j] * gsl_matrix_get(m, i, j);
    }
    xs[i] <- temp / gsl_matrix_get(m, i, i);
    }


    for (int i=0; i<n; i++) {
    cout<<endl<<"x"<<i+1<<": "<<xs[i]<<endl<<endl;
    }

    return 0;
}




int main()
{

    srand(time(NULL));
    int n=4;
    int k=sqrt(n);

    double l1[n];
    double l2[n];

    for (int i=0; i<n; i++) {
        int r1 = rand()%50+1;
        l1[i] = r1;
        //cout<<l1[i]<<endl<<endl;
    }


    for (int i=0; i<k; i++) {
        int r2 = rand()%50+1;
        l2[i] = r2;
        //cout<<endl<<l2[i]<<endl;
    }

    usolve(l1, l2, 2);

    lsolve(l1, l2, 2);

    return 0;
}
