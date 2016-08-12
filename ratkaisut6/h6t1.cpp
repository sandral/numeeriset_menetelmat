//Harjoitus 6, tehtava 1
#include <iostream>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include "gmatutl.h"
#include <gsl/gsl_eigen.h>

using namespace std;

gsl_matrix *transp(gsl_matrix *a)
{
  gsl_matrix *b=gsl_matrix_alloc(a->size2,a->size1);
  gsl_matrix_transpose_memcpy(b,a);
  return b;
}

int isEqualM(gsl_matrix * m1, gsl_matrix * m2) //compares if two square matrices are the same
{
    int n = m1->size1;
    int ret = 1;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            if (gsl_matrix_get(m1, i, j) != gsl_matrix_get(m2, i, j))
            {
                ret = 0;
            }
        }
    }
    return ret;
}

int isSymmetric(gsl_matrix * m) //checks if square matrix is symmetric
{
gsl_matrix * m_t = transp(m);
return isEqualM(m, m_t);
}

gsl_matrix * eigenM(gsl_matrix * m)
{
int n = m->size1;
gsl_vector * eval = gsl_vector_alloc(n);
gsl_matrix * evec = gsl_matrix_alloc(n, n);

gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc(n);

gsl_eigen_symmv(m, eval, evec, w);

gsl_eigen_symmv_free(w);

return evec;
}

gsl_vector * eigenVec(gsl_matrix * m) {
int n = m->size1;
gsl_vector * eval = gsl_vector_alloc(n);
gsl_matrix * evec = gsl_matrix_alloc(n, n);

gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc(n);

gsl_eigen_symmv(m, eval, evec, w);

gsl_eigen_symmv_free(w);

return eval;
}


int isPosDefS(gsl_matrix * m) //m nxn matrix, n dimension of matrix
{
    int ret = 1;
    int n = m->size1;

    if (isSymmetric(m)==0)
    {
        ret = 0;
    }
    else
    {

        gsl_vector * eval = eigenVec(m);

        for (int i=0; i<n; i++)
        {
            if (gsl_vector_get(eval, i)<0)
            {
                ret = 0;
            }
        }

    }
    return ret;
}



void makePosDef(gsl_matrix * m) //m nxn symmetric matrix
{
if (isSymmetric(m)==1)
{
int n = m->size1;

gsl_matrix * id = gsl_matrix_alloc(n, n);
gsl_matrix_set_identity(id);

gsl_matrix * m2 = gsl_matrix_alloc(n, n);
gsl_matrix_memcpy(m2, m);

gsl_vector * ev = eigenVec(m2);
gsl_matrix * em = eigenM(m2);

gsl_eigen_symmv_sort(ev, em, GSL_EIGEN_SORT_ABS_DESC);


gsl_matrix_scale(id, (0.01+fabs(gsl_vector_get(ev, 0))));

gsl_matrix_add(m, id);

}
}


int main()
{

    srand(time(NULL));

    gsl_matrix * m1 = gsl_matrix_alloc(2,2);
    gsl_matrix * m2 = gsl_matrix_alloc(2,2);
    gsl_matrix * m3 = gsl_matrix_alloc(2,2);

    gsl_matrix * m4 = gsl_matrix_alloc(4,4);

    gsl_matrix_set(m1, 0, 0, -1);
    gsl_matrix_set(m1, 0, 1, 0);
    gsl_matrix_set(m1, 1, 0, 0);
    gsl_matrix_set(m1, 1, 1, 3);

    gsl_matrix_set(m2, 0, 0, 5);
    gsl_matrix_set(m2, 0, 1, 2);
    gsl_matrix_set(m2, 1, 0, 2);
    gsl_matrix_set(m2, 1, 1, 3);

    gsl_matrix_set(m3, 0, 0, 4);
    gsl_matrix_set(m3, 0, 1, 0);
    gsl_matrix_set(m3, 1, 0, 0);
    gsl_matrix_set(m3, 1, 1, 3);

    for (int i=0; i<4; i++) {
        for (int j=i; j<4; j++) {
            int r = rand()%10-5;
            gsl_matrix_set(m4, i, j, r);
            gsl_matrix_set(m4, j, i, r);
        }
    }





    cout<<"Truth value for matrix m1 being positive definite: "<<endl<<isPosDefS(m1)<<endl;

    cout<<"M1: "<<endl;
    for (int i=0; i<2; i++) {
    for (int j=0; j<2; j++){
        cout<<gsl_matrix_get(m2, i, j)<<" ";
    }
    cout<<endl;
    }

    cout<<"Truth value for matrix m2 being positive definite: "<<endl<<isPosDefS(m2)<<endl;


    cout<<"M2: "<<endl;
    for (int i=0; i<2; i++) {
    for (int j=0; j<2; j++){
        cout<<gsl_matrix_get(m3, i, j)<<" ";
    }
    cout<<endl;
    }

    cout<<"Truth value for matrix m3 being positive definite: "<<endl<<isPosDefS(m3)<<endl;

    gsl_matrix_mul_elements(m2, m3);


    cout<<"M2.M3 : "<<endl;
    for (int i=0; i<2; i++) {
    for (int j=0; j<2; j++){
        cout<<gsl_matrix_get(m2, i, j)<<" ";
    }
    cout<<endl;
    }

    cout<<"Truth value for matrix m2.m3 being positive definite: "<<endl<<isPosDefS(m2)<<endl;


    cout<<"m4: "<<endl;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            cout<<gsl_matrix_get(m4, i, j)<<" ";
        }
        cout<<endl;
    }

    cout<<"is m4 positive definite: "<<isPosDefS(m4)<<endl;

    makePosDef(m4);

    cout<<"m4 made positive definite: "<<endl;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            cout<<gsl_matrix_get(m4, i, j)<<" ";
        }
        cout<<endl;
    }

    cout<<"Truth value for m4 being positive definite: "<<endl;
    cout<<isPosDefS(m4);

    return 0;
}
