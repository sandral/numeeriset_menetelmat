//Tehtävä3
#include <iostream>

using namespace std;

int tehtava3(double xs[], double ys[])
{
    for (int i=0; i<20; i++)
    {
        std::cout << (ys[i+1]-ys[i])/(xs[i+1]-xs[i]) << "\n";
    }
    return 0;
}


int main()
{
    double x[] = {0, 0.0100, 0.0200, 0.0300, 0.0400, 0.0500, 0.0600, 0.0700, 0.0800, 0.0900, 0.1000, 0.1100, 0.1200,
                  0.1300, 0.1400, 0.1500, 0.1600, 0.1700, 0.1800, 0.1900, 0.2000
                 };
    double y[] = {0, 0.3700, 0.7400, 1.1098, 1.4796,  1.8492, 2.2187, 2.5879, 2.9568, 3.3255, 3.6938, 4.0618, 4.4294,
                  4.7965, 5.1631,  5.5292, 5.8948, 6.2597, 6.6241, 6.9878, 7.3508
                 };

    tehtava3(x, y);
    return 0;
}