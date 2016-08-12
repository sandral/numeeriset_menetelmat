//Harjoitus 5, tehtävä 4

#include <iostream>
#include <math.h>
#include <gsl/gsl_vector.h>
#include <stdio.h>
#include <stdlib.h>
#include "gnumder.c"
#include "gnumdf.c"
#include "gnuplt1.c"


using namespace std;


double f(double x)
{
return sin(x);
}

double df(double x)
{
return gnumdf(f, x-1.0, x+1.0, x, 1E-5, 2);
}

double t(double x)
{
return f(x)+df(x);
}




int main()
{


setplotprint(1);
gnuplt1(f, "f(x)", 0, df, "df(x)", 0, NULL);
system("mv gnuplt1.ps h05t4a.ps");
gnuplt1(t, "t(x)", 2, NULL);
system("mv gnuplt1.ps h05t4b.ps");

return 0;
}
}


