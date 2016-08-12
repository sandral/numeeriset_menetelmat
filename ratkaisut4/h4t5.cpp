//Harjoitus 4, tehtävä 4
#include <iostream>
#include <math.h>

using namespace std;


//a-kohta
double pnorm(double l[], double p) //l vector, p-value must be at least 1.
{
double ret=0;
int n =sizeof(l);
for (int i=0; i<n; i++) {
ret += pow(fabs(l[i]), p);
}
return pow(ret, 1/p);
}

int pnorm_matrix_columns(double l[], int n, int m, double p) //l list of matrix elements, m rows, n columns, p-value at least 1.
{

for (int i=0; i<n; i++) {
double x[m];
for (int j=0; j<m; j++) {
    x[j] = l[i*m+j];
}
cout<<pnorm(x, p)<<endl;
}
return 0;
}


//b-kohta

int bmatrix(double a[], int n, int m, double p)
{
double b[m*n];
for (int i=0; i<n; i++) {
double sum;
double c;
for (int j=0; j<m; j++) {
    sum += pow(fabs(a[i*m+j]), 2);
}
    c = 1/sum;
    for (int j=0; j<m; j++) {
        b[i*m+j] = a[i*m+j]*c;
        cout<<b[i*m+j]<<" ";
    }
    cout<<endl;
}

return 0;
}

//c-kohta



int main() {
    double x[] = {1,2,3,4,5,6};
    pnorm_matrix_columns(x, 2, 3, 2);

    bmatrix(x, 2, 3, 2);

    return 0;
}
