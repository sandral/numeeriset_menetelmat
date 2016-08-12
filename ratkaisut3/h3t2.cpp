//Harjoitus 3, Tehtävä 2
#include <iostream>
#include <algorithm>


using namespace std;

int main()
{
    srand(time(NULL));
    int n = 10;
    double xs[n];

    for (int i=0; i<n; i++) {
    double r = rand()%10;
    xs[i] = r;
    }

    sort(xs, xs+10);



/*
    for (int i=0; i<n; i++) {
    cout<<xs[i]<<" ";
    }
*/
    return 0;
}
