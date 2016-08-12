//Tehtävä 6

#include <iostream>
#include <math.h>
#include <gsl/gsl_sf_hyperg.h>

using namespace std;

//a-kohta
double ag(double a, double b)
{
double a1, b1;

while( fabs(a-b) > 1.0E-16) {
a1 =  (a+b) / 2.0;
b1 = sqrt(a*b);

a= a1;
b=b1;
}

return a;

}



int main()
{

//b-kohta


/*
for (int i=1; i<20; i++) {

double x = gsl_sf_hyperg_2F1(0.5, 0.5, 1, 0.05*i);

cout<<x<<endl;

double y = 1/(ag(1, sqrt(1-pow(0.05*i,2))));

cout<<y<<endl;

cout<<x-y<<endl;

cout<<endl;

}

*/
//cout<<gsl_sf_hyperg_2F1(0.5, 0.5, 1, 0.05)-1/(ag(1, sqrt(1-pow(0.05,2))));


    double x,y;
    cout<<"Anna luku: "<<endl;
    cin>>x;
    cout<<"Anna toinen luku"<<endl;
    cin>>y;
    cout<<"Lukujen aritmeettis-geometrinen keskiarvo on: "<<ag(x,y)<<endl;

    return 0;
}
