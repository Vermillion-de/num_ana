#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#define Gauss3 0.774596692
#define PI     3.1415926535897932
#define A0     0.5555555555555555
#define A1     0.8888888888888888

class integral
{
private:
    double (*f)(double);
    double (*I_f)(double);
    double l, r, h;
    vector<double> pt;
public:
    integral(double func(double), double left, double right, int n = 0){
        // function f and its intervals n.
        l = left, r = right;
        f = func;
        h = (right - left)/n;
        for (int i = 0; i <= n; i++){
            pt.push_back(left + i * h);
        }
    }
    
    integral(double func(double), double I_func(double), double left, double right, int n = 0){
        // function f and its intervals n.
        l = left, r = right;
        f = func, I_f = I_func;
        h = (right - left)/n;
        for (int i = 0; i <= n; i++){
            pt.push_back(left + i * h);
        }
    }

    integral(double func(double)){
         f = func;
         l = r = h = 0;
    }

    integral(){
        f = NULL;
        l = 0, r = 0, h = 0;
        pt.resize(0);
    }
    ~integral(){};

    void set_pt(double left, double right, int n){
        pt.clear();
        l = left, r = right;
        h = (right - left)/n;
        for (int i = 0; i <= n; i++){
            pt.push_back(left + i * h);
        }
    }

    void set_pt(int n){
        pt.clear();
        h = (r - l)/n;
        for (int i = 0; i <= n; i++){
            pt.push_back(l + i * h);
        }
    }

    void print_pt(){
        cout << "[";
        for (int i = 0; i < pt.size() - 1 ; i++)
        {
            cout << pt[i] << ",\t";
        }
        cout << pt[pt.size()-1] << "]" << endl;
    } 

    void print_value(){
        cout << "[";
        for (int i = 0; i < pt.size() - 1 ; i++)
        {
            cout << f(pt[i]) << ",\t";
        }
        cout << f(pt[pt.size()-1]) << "]" << endl;
    }

    double result_line(){
        double ret = 0;
        ret += f(l)/2. + f(r)/2.;
        for (int i = 1; i < pt.size()-1; i++){
            ret += f(pt[i]);
        }
        ret *= h;
        return ret;
    }

    vector<double> pt_to_gauss3(){
        double g_l = l, g_r;
        vector<double> ret;
        for (int i = 1; i < pt.size(); i++)
        {
            g_r = pt[i];
            ret.push_back( (g_r + g_l)/2. - ((g_r - g_l)/2.) * Gauss3);
            ret.push_back( (g_r + g_l)/2.);
            ret.push_back( (g_r + g_l)/2. + ((g_r - g_l)/2.) * Gauss3);
            g_l = pt[i];
        }
        return ret;
    }

    double result_gauss3(){
        double ret = 0;
        vector<double> g_pt = pt_to_gauss3();
        double weight[3] = {A0,A1,A0};
        for (int i = 0; i < g_pt.size(); i++){
            ret += f( g_pt[i]) * weight[i%3]*3./2. ;
        }
        ret *= h/3;
        return ret;
    }

    double result(){
        return I_f(r) - I_f(l);
    }

    double error_line(){
        return abs(result() - result_line());
    }

    double error_gauss3(){
        return abs(result() - result_gauss3());
    }

    double error_line(int n){
        set_pt(n);
        return abs(result() - result_line());
    }
    
    double error_gauss3(int n){
        set_pt(n);
        return abs(result() - result_gauss3());
    }
};

double f(double x){
    return x*x;
}
double If(double x){
    return x*x*x/3.;
}

double f_1(double x){
    return exp(-x*x);
}
double f_2(double x){
    return 1./(1.+x*x);
}
double f_3(double x){
    return 1./(2.+cos(x));
}

double I_1(double x){
    return 1./2.*sqrt(PI)*erf(x);
}

double I_2(double x){
    return atan(x);
}

double I_3(double x){
    return 2/sqrt(3.)*atan( tan(x/2.)/sqrt(3.) );
}


void mk_one(integral I, string words){
    double eLine0, eGauss0, eLine1,eGauss1;
    vector<int> N{1,2,4,8,16,32,64,128};
    double ordLine,ordGauss;
    cout << fixed  << scientific << words << endl;
    I.set_pt(N[0]);
    cout << "N" << "\t\t" << "L error\t" << "\t\t" << "L order" << "\t\t\t" << "\tG error\t" << "\t\t" << "G order" << endl;
    eLine0 = I.error_line(), eGauss0 = I.error_gauss3();
    cout << N[0] << "\t\t" << eLine0 << "\t\t" << "--\t" << "\t\t\t" << eGauss0 << "\t\t" << "--\t" << endl;
    for (int i = 1; i < N.size(); i++)
    {
        I.set_pt(N[i]);
        eLine1 = eLine0, eGauss1 = eGauss0;
        eLine0 = I.error_line(), eGauss0 = I.error_gauss3();
        ordLine = log(eLine1/eLine0)/log(2.), ordGauss = log(eGauss1/eGauss0)/log(2.);
        cout << N[i] << "\t\t" << eLine0 << "\t\t" << ordLine << "\t\t\t" << eGauss0 << "\t\t" << ordGauss << endl;         
    }   
}


void mk_test(){
    integral I0(f_1,I_1,0,1),I1(f_2,I_2,0,4), I2(f_3,I_3,0,PI/2), I(f,If,0,1);
    //mk_one(I,"int_0^1 exp(-x^2)");
    mk_one(I0,"int_0^1 exp(-x^2)");
    mk_one(I1,"int_0^4 1/(x^2+1)");
    mk_one(I2,"int_0^pi/2 1/(2+cos(x)");
}





int main(){
    //integral I(f_3,I_3,0,1);
    // // I.print_pt();
    // // I.print_value();
    // cout << "the error linear:" << I.result_line() - 1./3. << endl;
    // cout << "the error gauss3:" << I.result_gauss3() - 1./3. << endl;
    // cout << erf(double(1)) << endl;
    mk_test();
    // integral I(f_3,I_3,0,2*PI);
    // I.set_pt(64);
    // cout << "pt is 64 now" << endl;
    // cout << "int_gauss " << I.result_gauss3() << endl;
    // cout << "int_line " << I.result_line() << endl;
    // cout << "result " << I.result() << endl;
    // cout << "error_gauss " << I.error_gauss3() << endl;
    // cout << "error_line " << I.error_line() << endl; 
    // cout << "pt is 128 now" << endl;
    // I.set_pt(128);
    // cout << "int_gauss " << I.result_gauss3() << endl;
    // cout << "int_line " << I.result_line() << endl;
    // cout << "result " << I.result() << endl;
    // cout << "error_gauss " << I.error_gauss3() << endl;
    // cout << "error_line " << I.error_line() << endl; 

    return 0;
}