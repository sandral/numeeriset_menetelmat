//Harjoitus 5, tehtava 5
#include <iostream>
#include <math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "gsolve.c"
//#include "gmatutl.c"

using namespace std;

gsl_matrix *matmul(gsl_matrix *a, gsl_matrix *b)
{
  gsl_matrix *c;
  double s = 0.0;
  int i, j, k;

  if (a->size2 != b->size1)
  {
    fprintf(stderr, "multiplication not applicable, a_n!=b_m");
    exit(1);
  }

  c = gsl_matrix_alloc(a->size1, b->size2);
  for (i = 0; i < (a->size1); i++)
  {
    for (j = 0; j < (b->size2); j++)
    {
      s = 0.0;
      for (k = 0; k < (a->size2); k++)
        s += gsl_matrix_get(a,i,k)*gsl_matrix_get(b,k,j);
      gsl_matrix_set(c, i, j, s);
    }
  }

  return c;
}

gsl_matrix *transp(gsl_matrix *a)
{
  gsl_matrix *b=gsl_matrix_alloc(a->size2,a->size1);
  gsl_matrix_transpose_memcpy(b,a);
  return b;
}

int main()
{
srand(time(NULL));
int n=4;
int m=3;
int k=2;

gsl_matrix * m1 = gsl_matrix_alloc(n, m);
gsl_matrix * m1_t = gsl_matrix_alloc(m, n);

gsl_matrix * pinv_m1 = gsl_matrix_alloc(m, n);



cout<<"A: "<<endl;
for (int i=0;i<n;i++) {
    for (int j=0;j<m;j++) {
      gsl_matrix_set(m1,i,j,rand()%20-10);
      cout<<gsl_matrix_get(m1, i, j)<<" ";
      }
      cout<<endl;
}



pinv_m1 = pseudoinv(m1);

cout<<endl<<"Pseudoinverse of A: "<<endl;
for (int i=0;i<m;i++) {
    for (int j=0;j<n;j++) {
      cout<<gsl_matrix_get(pinv_m1,i,j)<<" ";
      }
      cout<<endl;
}

gsl_matrix * pinv_pinv_m1 = gsl_matrix_alloc(n, m);

pinv_pinv_m1 = pseudoinv(pinv_m1);


cout<<endl<<"Pseudoinverse of pseudoinverse of A: "<<endl;
for (int i=0;i<n;i++) {
    for (int j=0;j<m;j++) {
      cout<<gsl_matrix_get(pinv_pinv_m1,i,j)<<" ";
      }
      cout<<endl;
}


gsl_matrix * pinv_m1_t = gsl_matrix_alloc(n, m);

pinv_m1_t = transp(pinv_m1);


cout<<endl<<"Transpose of pseudoinverse of A: "<<endl;
for (int i=0;i<n;i++) {
    for (int j=0;j<m;j++) {
      cout<<gsl_matrix_get(pinv_m1_t,i,j)<<" ";
      }
      cout<<endl;
}

m1_t = transp(m1);

gsl_matrix * m1_t_pinv = gsl_matrix_alloc(n,m);

m1_t_pinv = pseudoinv(m1_t);


cout<<endl<<"Pseudoinverse of transpose of A: "<<endl;
for (int i=0;i<n;i++) {
    for (int j=0;j<m;j++) {
      cout<<gsl_matrix_get(m1_t_pinv,i,j)<<" ";
      }
      cout<<endl;
}


gsl_matrix * m2 = gsl_matrix_alloc(m, k);
gsl_matrix * pinv_m2 = gsl_matrix_alloc(k, m);
gsl_matrix * m1m2_pinv = gsl_matrix_alloc(k, n);

for (int i=0; i<m; i++) {
for (int j=0; j<k; j++) {
gsl_matrix_set(m2, i, j, rand()%20-10);
}
}

gsl_matrix * m1m2 = gsl_matrix_alloc(n, k);

m1m2 = matmul(m1, m2);

gsl_matrix * pinv_m1m2 = gsl_matrix_alloc(k, n);

pinv_m1m2 = pseudoinv(m1m2);

pinv_m2 = pseudoinv(m2);

m1m2_pinv = matmul(pinv_m2, pinv_m1);

cout<<endl<<"Pseudoinverse A*B: "<<endl;
for (int i=0;i<k;i++) {
    for (int j=0;j<n;j++) {
      cout<<gsl_matrix_get(pinv_m1m2,i,j)<<" ";
      }
      cout<<endl;
}


cout<<endl<<"B^+ * A^+: "<<endl;
for (int i=0;i<k;i++) {
    for (int j=0;j<n;j++) {
      cout<<gsl_matrix_get(m1m2_pinv,i,j)<<" ";
      }
      cout<<endl;
}



    return 0;
}
