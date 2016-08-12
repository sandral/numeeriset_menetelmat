//Tehtävä 5
#include <iostream>
#include <math.h>

using namespace std;
/*
//a-kohta
double f(double x)
{
    return cos(x);
}
*/


//b-kohta
double f(double x)
{
    return exp(-x);
}


/*
//c-kohta
double f(double x)
{
    return 1 - cosh(x);
}
*/

double idty(double x)
{
    return x;
}


int main()
{


    double x, y, e, tol = 5.0e-10;
    int count = 0;
    printf("Enter the starting approximation:");
    scanf("%lf", &x);
    printf("\n");
    do
    {

        y = f(x);
        e = fabs(x - y);
        printf("%10.5lf %10.5lf %10.4e\n",x,y,e);
        x = y;
        count++;
        if (count > 60)
        {
            printf("Maximum number of iterates exceeded.\n");
            exit(1);
        }
    }
    while (e > fabs(y) * tol);
    printf("root= %lf\n", y);
    printf("iterates required = %d\n", count);

    return 0;
}
