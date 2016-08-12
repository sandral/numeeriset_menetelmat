//Tehtävät 1 ja 2
#include <iostream>
#include <math.h>

using namespace std;

double windChill(double T, double V)
{
double ret;

    if (V==0)
    {
        ret = T;
    }
    else
    {
        ret = 0.045*(5.27*sqrt(V) + 10.45 - 0.28*V)*(T - 33)+33;
    }
    return ret;
}

double windChillF(int T, int V) {

return 35.74 + (0.6215*T) - (35.75 * pow(V, 0.16)) + (0.4275 * T * pow(V, 0.16));

}

double ctoF(double tempC)
{
return 1.8*tempC+32;
}

double ftoC(double tempF)
{
return (tempF-32)/1.8;
}

double kmphToms(double v)
{
return (2.777778)*v;
}

double msToKmph(double v)
{
return 3.6*v;
}

int Prompt_TV()
{
  double T,V;
  cout<<"Enter temperature in Celsius:" <<endl;
  cin>>T;
  cout<<"Enter wind speed in km/h:" <<endl;
  cin>>V;
  cout<<"For T = "<<T<<", V = "<<V;
  cout<<", wind chill is: "<< windChill(T,V)<<endl;
  return 0;
}


int main()
{
Prompt_TV();

//Tehtävä 2
    for (int V = 0; V <= 8; V += 2)
    {
    double vel = msToKmph(V);
    cout << "\n";

        for (int T = 10; T >= -10; T -= 5)
        {
            cout <<windChill(T,vel) << " ";

        }
    }
    return 0;
}
