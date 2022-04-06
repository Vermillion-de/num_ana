#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#define EPS 1e-3
using namespace std;
double eps(double x){
    return exp(-x) / 2 * (1 + ( cos(2*x) - 2 * sin(2*x) )/5);
} 
int main(){
    int c = log(1/(5*EPS));
    while (eps(c) > EPS){
        c++;
    }
    cout << "the condition is, " << c << endl;
    double r = c, l = c - 1, m = (l+r)/2;
    for(int i = 0; i < 10; i++){
        if(eps(m) < EPS){
            r = m;
        }
        else{
            l = m;
        }
        m = (r+l)/2;
    }
    cout << "after iter 10times, " << m << endl;
    return 0;
}