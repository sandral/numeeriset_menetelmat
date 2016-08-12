//Harjoitus 5, tehtava 3
#include <iostream>
#include <math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_spline.h>



using namespace std;


int main()
{
    double x[20];
    double y[20];

    double xi;
    double yi;
    double e = -1.0;
    double t;


    for (int j=0; j<20; j++) {
    x[j] =  0.5+0.1*j;
    y[j] = tgamma(x[j]);
    }

    gsl_interp_accel * acc = gsl_interp_accel_alloc();

    gsl_spline * spline = gsl_spline_alloc(gsl_interp_cspline, 20);

    gsl_spline_init(spline, x, y, 20);


    for (int i=1; i<=200; i++) {
    xi = 0.5+0.01*i;
    yi = gsl_spline_eval (spline, xi, acc);
    t = fabs(tgamma(xi)-yi);
    if (e < t) {
    e = t;
    }
    }
    cout<<e<<endl;
    return 0;
}
