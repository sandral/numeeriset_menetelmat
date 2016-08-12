//harjoitus 5, tehtava 1
#include <iostream>
#include <iomanip>
#include <math.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_vector.h>
#include "gpolint.c"

using namespace std;

//a-kohta
double sol_a(double x, double y, double z, int n)
{
    gsl_vector * xs = gsl_vector_alloc(n+1);
    gsl_vector * ys = gsl_vector_alloc(n+1);

    double a, dy;

    for (int i=0; i<n+1; i++)
    {
        gsl_vector_set(xs, i, y+i*(z-y)/n);
        gsl_vector_set(ys, i, sin(gsl_vector_get(xs, i)));
    }

    gpolint(xs, ys, n+1, x, &a, &dy);

    return dy;
}

//b-kohta
double sol_b(double x, double y, double z, int n)
{
    double xs[n+1];
    double ys[n+1];

    for (int i=0; i<n+1; i++)
    {
        xs[i] = y+i*(z-y)/n;
        ys[i] = sin(xs[i]);
    }

    gsl_interp_accel * acc = gsl_interp_accel_alloc();

    const gsl_interp_type * t = gsl_interp_cspline_periodic;

    gsl_spline * spline = gsl_spline_alloc(gsl_interp_cspline, n+1);


    gsl_spline_init(spline, xs, ys, n+1);

    double ret = gsl_spline_eval (spline, x, acc);

    return ret;
}

//c-kohta
double sol_c(double x, double y, double z, int n)
{
    double xs[n+1];
    double ys[n+1];

    for (int i=0; i<n+1; i++)
    {
        xs[i] = y + i*(z-y)/n;
        ys[i] = sin(xs[i]);
    }

    gsl_interp_accel * acc = gsl_interp_accel_alloc();

    gsl_spline * spline = gsl_spline_alloc(gsl_interp_cspline, n+1);

    gsl_spline_init(spline, xs, ys, n+1);

        double ret = gsl_spline_eval (spline, x, acc);

    return ret;
}

int main()
{
    double x, y;

        double e1 = -1.0;
        double t1;

        for (int i=0; i<100; i++)
        {
            x = i*M_PI/200;

                y = sol_a(x, 0, 0.5*M_PI, 5);

            t1 = fabs(sin(x)-y);
            if (e1 < t1)
            {
                e1 = t1;
            }
        }
            cout<<"a-kohta"<<" : "<<e1<<endl;

        double e2 = -1.0;
        double t2;

        for (int i=0; i<100; i++)
        {
            x = i*M_PI/200;

                y = sol_b(x, 0, 0.5*M_PI, 5);

            t2 = fabs(sin(x)-y);
            if (e2 < t2)
            {
                e2 = t2;
            }
        }
            cout<<"b-kohta"<<" : "<<e2<<endl;

        double e3 = -1.0;
        double t3;

        for (int i=0; i<100; i++)
        {
            x = i*M_PI/200;

                y = sol_c(x, 0, 0.5*M_PI, 5);

            t3 = fabs(sin(x)-y);
            if (e3 < t3)
            {
                e3 = t3;
            }
        }
            cout<<"c-kohta"<<" : "<<e3<<endl;


    return 0;
}
