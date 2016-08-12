//Tehtävä4
#include <iostream>
#include <math.h>

using namespace std;

double coeff(double x[], double y[], int n)
{
    double a;
    double b;
    double t1;
    double t2;
    double t3;
    double t5;

    for (int i=0; i<n; i++)
    {
        t1 += x[i]*y[i];
        t2 += x[i];
        t3 += y[i];
    }

    double t4 = t2/n;

    for (int i=0; i<n; i++)
    {
        t5 += pow((x[i]-t4),2);
    }
    a = (t1 - (t2*t3)/n)/t5;

    b = (t3 - a*t2)/n;

    std::cout<< "a: "<< a << " b: "<< b;
    return 0;
}



int main()
{
    double time[] = {0, 1, 2, 3, 4, 5};
    double value[] = {0.8969, 0.9005, 0.8961, 0.8919, 0.8793, 0.8818};

    coeff(time, value, 6);
    return 0;
}
