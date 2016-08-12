//Harjoitus 2, tehtävä 1
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;


int main()
{
    srand(time(NULL));

    double p=0;
    double b = 4*M_PI;
    double n = 10000;

    for (int i=0; i<n; i++)
    {
        double x = (double(rand())/double(RAND_MAX))*2*M_PI;
        double y = fabs(double(rand())/double(RAND_MAX));

        cout<<i<<endl;

        if (cos(x)>=sin(x))
        {

            if (y <= cos(x) && y >= sin(x))
            {
                p++;
                cout<<"p: "<<p<<endl;
            }

            else if (cos(x) <= sin(x))
            {
                if (y >= cos(x) && y <= sin(x))
                {
                    p++;
                    cout<<"p: "<<p<<endl;
                }
            }
        }

    }
    cout<<(p/n)*b<<endl;

    return 0;
}
