//Harjoitus 3, Tehtävä 3
#include <iostream>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>
#include <math.h>
#include <stdio.h>

using namespace std;
bool isDD(double m[], int n)//A function to determine wether a nxn matrix is diagonally dominated. parms: m list of elements.
{
    double a[n][n]; //list into matrix

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            a[i][j] = m[n*i+j];
        }
    }

    double x;
    double y = 1;
    for (int i=0; i<n; i++)
    {
        x = 0;
        for (int j=0; j<n; j++)
        {
            if (j != i)
            {
                x += fabs(a[i][j]);
            }
        }
        if (fabs(a[i][i]) < fabs(x))
        {
            y = 0;
        }
    }
    if (y==0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int main()
{
    int n = 36;
    int k = 6;
    srand(time(NULL));
    double xs[n];
    double ys[n];

    //Allocating matrices m1, m2 and m3
    int s;
    gsl_matrix * m1 = gsl_matrix_alloc(n, n);
    gsl_matrix * m2 = gsl_matrix_alloc(n, n);
    gsl_matrix * m3 = gsl_matrix_alloc(n, n);
    gsl_matrix * m4 = gsl_matrix_alloc(3, 3); //allocating counterexample matrix for inverse of ddmatrix


    gsl_matrix * inverse = gsl_matrix_alloc(3, 3);
    gsl_permutation * perm = gsl_permutation_alloc(3);


    //Creating random elements for matrices
    for (int i=0; i<n; i++)
    {
        int r1 = rand()%20 - 10;
        int r2 = rand()%20 - 10;
        xs[i] = r1;
        ys[i] = r2;
    }

    //Inserting elements to matrices
    for (int i=0; i<k; i++)
    {
        for (int j=0; j<k; j++)
        {
            gsl_matrix_set(m1, i, j, xs[i*k+j]);
            gsl_matrix_set(m2, i, j, ys[i*k+j]);

        }
    }

    //Modifying matrices to diagonally dominated
    for (int i=0; i<k; i++)
    {
        double temp1 = 0;
        double temp2 = 0;
        for (int j=0; j<k; j++)
        {
            if (i!=j)
            {
                temp1 += fabs(gsl_matrix_get(m1, i, j));
                temp2 += fabs(gsl_matrix_get(m2, i, j));
            }
        }
        if (fabs(temp1) >= fabs(gsl_matrix_get(m1, i, i)))
        {
            if (gsl_matrix_get(m1, i, i) < 0) {
                gsl_matrix_set(m1, i, i, gsl_matrix_get(m1, i, i)
                -fabs(fabs(temp1)-fabs(gsl_matrix_get(m1, i, i)))-(rand()%5+1));
        }

        else {gsl_matrix_set(m1, i, i, gsl_matrix_get(m1, i, i)
                +fabs(fabs(temp1)-fabs(gsl_matrix_get(m1, i, i)))+(rand()%5+1));
                }
                }

        if (fabs(temp2) >= fabs(gsl_matrix_get(m2, i, i)))
        {
             if (gsl_matrix_get(m2, i, i) < 0) {
                gsl_matrix_set(m2, i, i, gsl_matrix_get(m2, i, i)
                -fabs(fabs(temp2)-fabs(gsl_matrix_get(m2, i, i)))-(rand()%5+1));
        }

        else {gsl_matrix_set(m2, i, i, gsl_matrix_get(m2, i, i)
                +fabs(fabs(temp2)-fabs(gsl_matrix_get(m2, i, i)))+(rand()%5+1));
                }
        }
    }

    cout<<"m1: "<<endl;
    for (int i=0; i<k; i++)
    {
        for (int j=0; j<k; j++)
        {
            cout<<gsl_matrix_get(m1, i, j)<<" ";
        }
        cout<<endl;
    }

    cout<<endl<<"m2: "<<endl;
    for (int i=0; i<k; i++)
    {
        for (int j=0; j<k; j++)
        {
            cout<<gsl_matrix_get(m2, i, j)<<" ";
        }
        cout<<endl;
    }

    //Product of m1 and m2
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, m1, m2, 1.0, m3);


    //Print m3
    cout<<endl<<"m3: "<<endl;
    for (int i=0; i<k; i++)
    {
        for (int j=0; j<k; j++)
        {
            cout<<gsl_matrix_get(m3, i, j)<<" ";
        }
        cout<<endl;
    }


    //Matrix m3 into list
    double ml3[n];
    for (int i=0; i<k; i++)
    {
        for (int j=0; j<k; j++)
        {
            ml3[k*i+j] = gsl_matrix_get(m3, i, j);
        }
    }

    cout<<endl<<"m3 = m1*m2 is diagonally dominant: "<<isDD(ml3, k)<<endl;

    double ml1[n];
    for (int i=0; i<k; i++)
    {
        for (int j=0; j<k; j++)
        {
            ml1[k*i+j] = gsl_matrix_get(m1, i, j);
        }
    }


    double ml2[n];
    for (int i=0; i<k; i++)
    {
        for (int j=0; j<k; j++)
        {
            ml2[k*i+j] = gsl_matrix_get(m2, i, j);
        }
    }

    //Counterexample to show that inverse of ddmatrix is not dd:
    //Setting element into matrix m4
    gsl_matrix_set(m4, 0, 0, 2);
    gsl_matrix_set(m4, 0, 1, 1);
    gsl_matrix_set(m4, 0, 2, 1);
    gsl_matrix_set(m4, 1, 0, 0);
    gsl_matrix_set(m4, 1, 1, 1);
    gsl_matrix_set(m4, 1, 2, 0);
    gsl_matrix_set(m4, 2, 0, 0);
    gsl_matrix_set(m4, 2, 1, 0);
    gsl_matrix_set(m4, 2, 2, 1);

    gsl_linalg_LU_decomp(m4, perm, &s);
    gsl_linalg_LU_invert(m4, perm, inverse);

    //inverse of m4 to list
    double inv[9];
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            inv[3*i+j] = gsl_matrix_get(inverse, i, j);
        }
    }

    //matrix m4 to list
    double ml4[9];
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            ml4[3*i+j] = gsl_matrix_get(m4, i, j);
        }
    }
    cout<<endl<<"m4 is diagonally dominant: "<<isDD(ml4, 3)<<endl;


    cout<<endl<<"Inverse of m4 is diagonally dominant: "<<isDD(inv, 3)<<endl<<endl;


    //Allocating tridiagonal matrix
    gsl_matrix * tridm = gsl_matrix_alloc(n, n);
    gsl_matrix * inv_tridm = gsl_matrix_alloc(n, n);
    gsl_permutation * p = gsl_permutation_alloc(n);

    gsl_matrix_set_zero(tridm);
    //Set random elements into matrix
    for (int i=0; i<k; i++)
    {
        for (int j=0; j<k; j++)
        {
            if (fabs(i-j)<=1)
            {
                double rr = rand()%9+1;
                gsl_matrix_set(tridm, i, j, rr);
            }
        }
    }

    for (int i=0; i<k; i++)
    {
        for (int j=0; j<k; j++)
        {
        cout<<gsl_matrix_get(tridm, i, j)<<" ";
        }
        cout<<endl;
        }
    //Invert matrix
    gsl_linalg_LU_decomp(tridm, p, &s);
    gsl_linalg_LU_invert(tridm, p, inv_tridm);


    int istridiagonal = 1;
    for (int i=0; i<k; i++) {
    for (int j=0; j<k; j++) {

            if (fabs(i-j)>1)
            {
                if (gsl_matrix_get(inv_tridm, i, j) != 0)
                {
                    istridiagonal = 0;
                }
            }
        }
    }
    if (istridiagonal==1)
    {
        cout<<"Inverse is tridiagonal"<<endl;
    }

    return 0;

}
