//Harjoitus 2, tehtävä 5
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <math.h>


using namespace std;

double invf(double a, double b, double y, double (*f)(double),
	    double delta, double epsn, int maxit){
/*
invf returns a value x on the interval (a,b) such that f(x)=y.
Based on bisection of the interval (a,b) such that x remains
inside. Stopping criterion: iteration stopped when one of
the following is satisfied:
           (1)interval length <delta
           (2)number of iterations >maxit
           (3)residual tolerance < epsn
NB. c=a+e and (a+b)/2 are mathematically equivalent but the former
    is preferable because of its numerical properties.
*/
  int k;
  double w,c;
  double u = f(a)-y;                // fcn value at left pt
  double e = b - a;                 // interval length
  for (k = 1; k <= maxit; k++)      // main iteration loop
  {
    e*=0.5;                         // shrink interval by half
    c = a + e;                      // update middle pt
    w = f(c)-y;                     // fcn value at middle pt
    if (fabs(e) < delta || fabs(w) < epsn)
      return c;
    ((u > 0 && w < 0) || (u < 0 && w > 0)) ? (b = c) : (a = c, u = w);
  }
}

double ff (double x) {
  return 0.5*(x - sin(x)*cos(x));
}

/*
double fint(double upper)
{
  double  result = -cos(upper) + cos(0);
  return result;
}
*/

int main() {

  double epsn=1e-5, delta=epsn, root;
  double yval=5.0;

  root = invf(1e-2, 20, yval, ff, delta, epsn, 100);
  cout<<"\nApproximate root of f(x)=5 by invf() is: "<<root<<endl;
}
