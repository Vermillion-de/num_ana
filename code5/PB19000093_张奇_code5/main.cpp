#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#define PI 3.1415926535897932384626
using namespace std;

double f(double x){
    return sin(x);
}

double int_f(double x){
    return -cos(x);
}

double splined_line(double f(double), double l, double r, int n){
    // \int_l^r f dx, approx with n intervals 
    double ret = 0, gap = (r-l)/n;
    ret += f(l)/2;
    for (int i = 1; i < n; i++){
        ret += f(l+i*gap);
    }
    ret += f(r)/2;
    ret = ret * gap;
    return ret;
}

double splined_simpson(double f(double), double l, double r, int n){
    // \int_l^r f dx, approx with n intervals 
    double ret = 0, gap = (r-l)/n;
    ret += f(l)/6. + f(r)/6.;
    for (int i = 0; i < n; i++){
        ret += f(l+(i+0.5)*gap)*2./3.;
    }
    for (int i = 1; i < n; i++)
    {
        ret += f(l+i*gap)/3.;
    }
    ret = ret * gap;
    return ret;
}

int main(){
    double l=0, r=4, simpson = 0, line = 0, simp_error_0 = 0, line_error_0 = 0, simp_error_1 = 0, line_error_1 = 0, simp_order = 0, line_order = 0;
    double  real_int = int_f(r) - int_f(l);
    cout << "N" << '\t' << "Simpson误差" << '\t' << "order" << '\t' << '\t' << "梯形误差" << '\t' << "order" << endl; 
    simpson = splined_simpson(f,l,r, pow(2,1)), line = splined_line(f,l,r, pow(2,1));
    simp_error_1 = abs(simpson - real_int), line_error_1 = abs(line - real_int);
    cout << pow(2,1) << '\t' << simp_error_1 << '\t' << "--" << '\t' << '\t' << line_error_1 << '\t' << "--" << endl;  
    for (int i = 2; i <= 12; i++){
        simp_error_0 = simp_error_1, line_error_0 = line_error_1;
        simpson = splined_simpson(f,l,r, pow(2,i)), line = splined_line(f,l,r, pow(2,i));
        simp_error_1 = abs(simpson - real_int), line_error_1 = abs(line - real_int);
        simp_order = log(simp_error_0/simp_error_1)/log(2), line_order = log(line_error_0/line_error_1)/log(2);
        cout << pow(2,i) << '\t' << simp_error_1 << '\t' << simp_order << '\t' << '\t' << line_error_1 << '\t' << line_order << endl;  
    } 
    return 0;
}
