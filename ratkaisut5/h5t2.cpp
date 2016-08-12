//Harjoitus 5, tehtava 2
#include "gpolint.c"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <gsl/gsl_vector.h>

using namespace std;

int main()
{
    gsl_vector * x = gsl_vector_alloc(4);
    gsl_vector * y = gsl_vector_alloc(4);

    double x1;
    double y1;
    double dy;

    for (int i=0; i<4; i++) {
        gsl_vector_set(x, i, i);
    }

    gsl_vector_set(y, 0, 1.0);
    gsl_vector_set(y, 1, 125.0);
    gsl_vector_set(y, 2, 729.0);
    gsl_vector_set(y, 3, 2197.0);


    cout<<"pisteet:   x             y"<<endl;

    for (int i=0; i<4; i++)
    {
        cout<<setw(10)<<gsl_vector_get(x, i)<<setw(14)<<gsl_vector_get(y, i)<<endl;
    }
    cout<<"interpoloidut arvot: "<<endl;
    cout<<"        x             y            virhe"<<endl;
    for (int i=0; i<4; i++)
    {
        x1 = 2.0+i*0.25;
        gpolint(x, y, 4, x1, &y1, &dy);
        cout<<setw(10)<<x1<<setw(14)<<y1<<setw(14)<<dy<<endl;
    }

    srand(time(NULL));

    for (int i=0; i<4; i++)
    {
        gsl_vector_set(y, i, rand()%80);
    }

    cout<<"data:   x              y"<<endl;

    for (int i=0; i<4; i++)
    {
        cout<<setw(10)<<gsl_vector_get(x, i)<<setw(14)<<gsl_vector_get(y, i)<<endl;
    }
    cout<<"interpoloidut arvot"<<endl;
    cout<<"        x              y            virhe"<<endl;
    for (int i=0; i<4; i++)
    {
        x1 = 2.0+i*0.25;
        gpolint(x, y, 4, x1, &y1, &dy);
        cout<<setw(10)<<x1<<setw(14)<<y1<<setw(14)<<dy<<endl;
    }


    return 0;
}
