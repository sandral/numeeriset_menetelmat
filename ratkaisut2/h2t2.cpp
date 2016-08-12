//Harjoitus 2, tehtävä 3
#include <iostream>
#include <gsl_matrix.h>
#include <gsl_linalg.h>
#include <gsl_cblas.h>
#include <math.h>
#include <stdio.h>


using namespace std;

int main()
{
    //Matriisi a:
    int s;

    gsl_matrix * p = gsl_matrix_alloc(2,2);
    gsl_matrix * inversep = gsl_matrix_alloc(2,2);
    gsl_permutation * pp = gsl_permutation_alloc(2);


    gsl_matrix_set (p, 0, 0, 2);
    gsl_matrix_set (p, 0, 1, 0);
    gsl_matrix_set (p, 1, 0, 0);
    gsl_matrix_set (p, 1, 1, 2);

    cout<<"P: ";
    for (int i = 0; i < 2; i++)
    {
        cout<<endl;
        for (int j = 0; j < 2; j++)
        {
            cout<<gsl_matrix_get(p, i, j)<<" ";
        }
    }

    gsl_linalg_LU_decomp(p, pp, &s);

    gsl_linalg_LU_invert(p, pp, inversep);



    cout<<endl;
    cout<<endl;
    cout<<"Inverse of P: ";
    for (int i = 0; i < 2; i++)
    {
        cout<<endl;
        for (int j = 0; j < 2; j++)
        {
            cout<<gsl_matrix_get(inversep, i, j)<<" ";
        }
    }


    //Matriisi b:


    gsl_matrix * r = gsl_matrix_alloc(2,2);
    gsl_matrix * inverser = gsl_matrix_alloc(2,2);
    gsl_permutation * pr = gsl_permutation_alloc(2);


    gsl_matrix_set (r, 0, 0, 1);
    gsl_matrix_set (r, 0, 1, 2);
    gsl_matrix_set (r, 1, 0, 3);
    gsl_matrix_set (r, 1, 1, 2);

    cout<<endl;
    cout<<endl;
    cout<<"R: ";
    for (int i = 0; i < 2; i++)
    {
        cout<<endl;
        for (int j = 0; j < 2; j++)
        {
            cout<<gsl_matrix_get(r, i, j)<<" ";
        }
    }



    gsl_linalg_LU_decomp(r, pr, &s);

    gsl_linalg_LU_invert(r, pr, inverser);


    cout<<endl;
    cout<<endl;
    cout<<"Inverse of R: ";
    for (int i = 0; i < 2; i++)
    {
        cout<<endl;
        for (int j = 0; j < 2; j++)
        {
            cout<<gsl_matrix_get(inverser, i, j)<<" ";
        }
    }

    cout<<endl;


    gsl_matrix * a = gsl_matrix_alloc(4,4);
    gsl_matrix * b = gsl_matrix_alloc(4,4);
    gsl_matrix * inversea = gsl_matrix_alloc(4,4);
    gsl_permutation * pa = gsl_permutation_alloc(4);

    gsl_matrix_set(a,0,0,2);
    gsl_matrix_set(a,0,1,0);
    gsl_matrix_set(a,0,2,0);
    gsl_matrix_set(a,0,3,0);
    gsl_matrix_set(a,1,0,0);
    gsl_matrix_set(a,1,1,2);
    gsl_matrix_set(a,1,2,0);
    gsl_matrix_set(a,1,3,0);
    gsl_matrix_set(a,2,0,0);
    gsl_matrix_set(a,2,1,0);
    gsl_matrix_set(a,2,2,1);
    gsl_matrix_set(a,2,3,2);
    gsl_matrix_set(a,3,0,0);
    gsl_matrix_set(a,3,1,0);
    gsl_matrix_set(a,3,2,3);
    gsl_matrix_set(a,3,3,2);

    gsl_matrix_set(b,0,0,0.5);
    gsl_matrix_set(b,0,1,0);
    gsl_matrix_set(b,0,2,0);
    gsl_matrix_set(b,0,3,0);
    gsl_matrix_set(b,1,0,0);
    gsl_matrix_set(b,1,1,0.5);
    gsl_matrix_set(b,1,2,0);
    gsl_matrix_set(b,1,3,0);
    gsl_matrix_set(b,2,0,0);
    gsl_matrix_set(b,2,1,0);
    gsl_matrix_set(b,2,2,-0.5);
    gsl_matrix_set(b,2,3,0.5);
    gsl_matrix_set(b,3,0,0);
    gsl_matrix_set(b,3,1,0);
    gsl_matrix_set(b,3,2,0.75);
    gsl_matrix_set(b,3,3,-0.25);

    cout<<endl;
    cout<<"A: ";
    for (int i=0; i<4; i++)
    {
        cout<<endl;
        for (int j=0; j<4; j++)
        {
            cout<<gsl_matrix_get(a, i, j)<<" ";
        }
    }

    cout<<endl;
    cout<<endl;
    cout<<"B: ";
    for (int i=0; i<4; i++)
    {
        cout<<endl;
        for (int j=0; j<4; j++)
        {
            cout<<gsl_matrix_get(b, i, j)<<" ";
        }
    }

    cout<<endl;

    gsl_linalg_LU_decomp(a, pa, &s);

    gsl_linalg_LU_invert(a, pa, inversea);
    cout<<endl;
    cout<<"Inverse of A: ";
    for (int i=0; i<4; i++)
    {
        cout<<endl;
        for (int j=0; j<4; j++)
        {
            cout<<gsl_matrix_get(inversea, i, j)<<" ";
        }
    }



    return 0;
}
