#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#define PI 3.1415926535897932384626
using namespace std;

double f(double x){
    return 1/(1+25*pow(x,2));
}

double int_f(double x){
    return atan(5*x)/5;
}

void print_vec(vector<double> vec){
    for (int i = 0; i < vec.size(); i++){
        cout << vec[i] << " \t " ;
    }
    cout << endl;
}

vector<double> mkpt_uniform(double l, double r, int n){
    // [l,r] => n intervals
    vector<double> ret;
    double temp = (r - l) / n;
    for (int i = 0; i <= n; i++)
    {
        ret.push_back(temp*i+l);
    }
    return ret;
}

vector<double> mkpt_chebysheff(double l, double r, int n){
    vector<double> ret;
    double radis = (l - r) / 2, center = (l + r) / 2;
    for (int i = 0; i <= n; i++){
        ret.push_back(center + radis * cos((i+1.)/(n+2.)*PI));
    }
    return ret;
}

vector<double> add(vector<double> a, vector<double> b){
    // ret : a + b
    vector<double> ret;
    for (int i = 0; i < a.size(); i++){
        ret.push_back(a[i]+b[i]);
    }
    return ret;
}

vector<double> move(vector<double> a){
    vector<double> ret;
    ret.push_back(0);
    for (int i = 0; i < a.size(); i++){
        ret.push_back(a[i]);
    }
    return ret;
}

vector<double> prod(vector<double> a, double x){
    vector<double> ret;
    for (int i = 0; i < a.size(); i++){
        ret.push_back(x*a[i]);
    }
    return ret;
}

double lagbasis_int(vector<double> x, int k, double l, double r){
    // int on k-th basis w.r.t x;
    vector<double> coef{1}, temp;
    double quote = 1, integ = 0;
    for (int i = 0; i < k; i++){
        temp = move(coef);
        coef = prod(coef,-x[i]);
        coef.push_back(0);
        coef = add(coef,temp);
        quote *= (x[k] - x[i]);
    }
    for (int i = k+1; i < x.size(); i++){
        temp = move(coef);
        coef = prod(coef,-x[i]);
        coef.push_back(0);
        coef = add(coef,temp);
        quote *= (x[k] - x[i]);
    }
    for (int i = 0; i < x.size(); i++){
        integ += coef[i]*(pow(r, i+1) - pow(l, i+1))/(i+1);
    }
    integ /= quote;
    return integ;
}

double lag_int(double f(double), vector<double> x, double l, double r){
    double ret = 0;
    for (int i = 0; i < x.size(); i++){
        ret += lagbasis_int(x,i,l,r)*f(x[i]);
    }
    return ret;
}

void warpup_code6(){
    double l = -1, r = 1, error_uniform = 0, error_chebysheff = 0, int_uniform = 0, int_chebysheff = 0, int_real = int_f(r) - int_f(l);
    vector<int> N{5,10,15,20,25,30,35,40};
    vector<double> uniform_split, chebysheff_split;
    cout << fixed  << "N" << " \t" << "int_uniform" << " \t" << "int_chebysheff" << " \t" << "int_real" << " \t" << "error_uniform" << " \t" << "error_chebysheff" << endl;
    for (int i = 0; i < N.size(); i++){
        uniform_split = mkpt_uniform(l,r,N[i]);
        int_uniform = lag_int(f,uniform_split,l,r);
        chebysheff_split = mkpt_chebysheff(l,r,N[i]);
        int_chebysheff = lag_int(f,chebysheff_split,l,r);
        error_uniform = abs(int_uniform - int_real);
        error_chebysheff = abs(int_chebysheff - int_real);
        cout << N[i] << " \t" << int_uniform << " \t" << int_chebysheff << " \t" << int_real << " \t" << error_uniform << " \t" << error_chebysheff << endl;
    }
}

int main(){
    warpup_code6();
    return 0;
}