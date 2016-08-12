//Harjoitus 5, tehtävä 6 b
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include "gmatutl.c"
#include "gsolve.c"

using namespace std;

void usolve(gsl_matrix *um, gsl_vector *x, gsl_vector *b){

  /* Solves the system um*x=b, where um is
     a upper triangular matrix */

  int i,j,n,m;
  double s;
  n=um->size1; m=um->size2;
  if (n!=m)
    printf("\nMatrix is not square!\n");
  else {
    gsl_vector_set(x,n-1,gsl_vector_get(b,n-1)/gsl_matrix_get(um,n-1,n-1));
    for(i=n-2;i>=0;i--){
      s=0.0;
      for(j=i+1;j<n;j++){
	s+=gsl_matrix_get(um,i,j)*gsl_vector_get(x,j);
      }
      gsl_vector_set(x,i,(gsl_vector_get(b,i)-s)/gsl_matrix_get(um,i,i));
    }
  }
}

gsl_vector *house_vec(gsl_matrix *a, int k)
  /* Returns for column col_idx the Householder
     vector v  and makes zero the subdiagonal entries
     of col_idx of a
*/
{
  int kk,j,jj,m=a->size1,n=a->size2;
  double s,alf,beta,gam;
  gsl_vector *v=gsl_vector_calloc(m);
  gsl_vector *w=gsl_vector_alloc(m);
  if ( (m <2) || (n <2) ||(m<n) || (k>=n) ){
    printf("Argument error in house_vec,m,n, col_idx= %d, %d, %d\n",m,n,k);
    exit(1);
  }
  s=0.0;
  for (kk=k;kk<m;kk++){
    s+=pow(gsl_matrix_get(a,kk,k),2.0);
    gsl_vector_set(v,kk,gsl_matrix_get(a,kk,k));
  }
  if (gsl_matrix_get(a,k,k)>0)
    alf=pow(s,0.5);
  else
    alf=-pow(s,0.5);
  gsl_vector_set(v,k,gsl_vector_get(v,k)-alf);

  s=0.0;
  for (kk=0;kk<m;kk++)
    s+=pow(gsl_vector_get(v,kk),2.0);
  beta=s;
  if (beta>1e-14) /* if beta =0 go to next k */
  {
     for (j=k;j<n;j++)
     {
       gam=0.0;
       for (jj=0;jj<m;jj++)
         gam+=gsl_vector_get(v,jj)*gsl_matrix_get(a,jj,j);
       for (jj=0;jj<m;jj++)
         gsl_matrix_set(a,jj,j,gsl_matrix_get(a,jj,j)-
                       (2*gam/beta)*gsl_vector_get(v,jj));
     }
  }
  for (j=0;j<a->size1;j++)
    gsl_vector_set(w,j,gsl_vector_get(v,j));

  return w;
}


gsl_vector *HOUSEsolve(gsl_matrix *a, gsl_vector *b)
/*   Solves a*x = b by the Householder method
     writing a = QR with orthog. Q and upper triangular R
     a will be overwritten.
*/
{
  int i,ii,j,m=a->size1,n=a->size2;
  double beta,gam;
  gsl_vector *sol=gsl_vector_alloc(n);
  gsl_vector *v=gsl_vector_alloc(m);
  gsl_vector *tmp=gsl_vector_alloc(m);
  gsl_matrix *aa=gsl_matrix_alloc(n,n);
  gsl_vector *rhs=gsl_vector_alloc(n);

  if ( (m <2) || (n <2) || (m<n) ||(b->size!=m))
  {
    printf("Argument error in HOUSEsolve,m,n= %d, %d\n",m,n);
    exit(1);
  }
  gsl_vector_memcpy(tmp,b);
  for (i=0;i<n;i++)
  {
    v=house_vec(a,i);
    beta=vnormp(v,2.0);
    beta=beta*beta;
    if (beta>1e-14)
    {
      gam=0.0;
      for (ii=0;ii<m;ii++)
	gam+=gsl_vector_get(v,ii)*gsl_vector_get(tmp,ii);
      gam=2*gam/beta;
      for (ii=0;ii<m;ii++)
	gsl_vector_set(tmp,ii,gsl_vector_get(tmp,ii)-gam*gsl_vector_get(v,ii));
    }
  }

  for (i=0;i<n;i++)
    for (j=0;j<n;j++)
      gsl_matrix_set(aa,i,j,gsl_matrix_get(a,i,j));
  for (i=0;i<n;i++)
    gsl_vector_set(rhs,i,gsl_vector_get(tmp,i));
  usolve(aa,sol,rhs);

  return sol;
}

int main()
{
  /* Compare three methods to solve a LSQ problem:
     a) SVDsolve
     b) HOUSEsolve
     c) banal solution: Solution for a*x =b is given
        as x= pseudoinv(a)*b                           */
  int i,n=3;
  gsl_matrix * a = gsl_matrix_alloc(5, 3);
  gsl_vector *b,*x;

    gsl_matrix_set(a, 0, 0, 1);
    gsl_matrix_set(a, 0, 1, 1);
    gsl_matrix_set(a, 0, 2, 1);
    gsl_matrix_set(a, 1, 0, 1);
    gsl_matrix_set(a, 1, 1, 2);
    gsl_matrix_set(a, 1, 2, 4);
    gsl_matrix_set(a, 2, 0, 1);
    gsl_matrix_set(a, 2, 1, 3);
    gsl_matrix_set(a, 2, 2, 9);
    gsl_matrix_set(a, 3, 0, 1);
    gsl_matrix_set(a, 3, 1, 3);
    gsl_matrix_set(a, 3, 2, 9);
    gsl_matrix_set(a, 4, 0, 1);
    gsl_matrix_set(a, 4, 1, 4);
    gsl_matrix_set(a, 4, 2, 16);

  printf("\nA=\n");
  showmat(a);
  printf("\n");
/*
  ac=gsl_matrix_alloc(a->size1,a->size2);
  v=gsl_vector_alloc(a->size1);
 */

x = gsl_vector_alloc(3);
b = gsl_vector_alloc(5);

    gsl_vector_set(b, 0, 2);
    gsl_vector_set(b, 1, 2);
    gsl_vector_set(b, 2, 3);
    gsl_vector_set(b, 3, 5);
    gsl_vector_set(b, 4, 6);


  /*pia=gsl_matrix_alloc(a->size2,a->size1);
  gsl_matrix_memcpy(ac,a);
  for(i=0;i<sol->size;i++)
    gsl_vector_set(sol,i,1.0);
  gsl_blas_dgemv(CblasNoTrans, 1.0, ac, sol, 0.0, v);
  */


  x = HOUSEsolve(a,b);

    cout<<"x: "<<endl;
    for (int i=0; i<3; i++) {
    cout<<gsl_vector_get(x, i)<<endl;
    }

  /*
  printf("HOUSEsolve: Resid = %e\n",residual(a,sol,v));
  for(i=0;i<sol->size;i++)
    gsl_vector_set(sol,i,1.0);
  gsl_blas_dgemv(CblasNoTrans, 1.0, a, sol, 0.0, b);
  sol=SVDsolve(a,b);
  printf("SVDsolve: Resid = %e\n",residual(a,sol,b));
  pia=pseudoinv(a);
  gsl_blas_dgemv(CblasNoTrans, 1.0, pia, b, 0.0, sol);
  printf("Pseudoinv: Resid = %e\n\n",residual(a,sol,b));

  gsl_matrix_free(pia);
  gsl_matrix_free(ac);
  gsl_matrix_free(a);
  gsl_vector_free(b);
  gsl_vector_free(v);
  gsl_vector_free(sol);
  */
}
