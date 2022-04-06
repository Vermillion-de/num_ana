#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

double f1(double x){
    return log(x);
}

double df1(double x){
    return 1/x;
}

double f2(double x){
    return tan(x);
}

double df2(double x){
    return 1/pow(cos(x),2);
}

double f3(double x){
    return sin(x*x+x/3);
}

double df3(double x){ 
    return cos(x*x+x/3)*(2*x+1./3.);
}

double phi(double f(double), double x, double h,int n){
    h = h/pow(2,n);
    return (f(x+h) - f(x-h))/(2*h);
}

void lab6(double f(double), double x, double h, int M, double df(double)){
    double D[M+1][M+1],derivate = df(x);
    for (int i = 0; i <= M; i++){
        D[i][0] = phi(f,x,h,i);
    }
    for (int k = 0; k < M; k++){
        for (int j = 0; j < M - k; j++){
            D[j][k+1] = (D[j+1][k]*pow(2,2*k+2) - D[j][k])/(pow(2,2*k+2) - 1);
        }
    }
    cout << "numerical caculate:" << endl;
    for (int i = 0; i <= M; i++){
        for (int j = 0; j <= M-i ; j++){
            cout << D[i][j]<< "\t";
        }
        cout << endl;
    }
    cout<< fixed << setprecision(12) << scientific << "real eps:" << endl;
    for (int i = 0; i <= M; i++){
        for (int j = 0; j <= M-i ; j++){
            cout << D[i][j] - derivate << "\t";
        }
        cout << endl;
    }
}

int main(){
    double x[3] = {3,asin(0.8),0}, h[3] = {1,1,1};
    int M[3] = {3,4,5};
    double (*func[3])(double x) = {f1,f2,f3};
    double (*dfunc[3])(double x) = {df1, df2, df3};
    string descripe[3] = {"log(x), x=3, M=3", "tan(x), x=arcsin(0.8), M=4", "sin(x*x+x/3), x=0, M=5"};
    for (int i = 0; i < 3; i++){
        cout << fixed << setprecision(12) << descripe[i] << endl;
        lab6(func[i],x[i],h[i],M[i],dfunc[i]);
        cout << endl;
    }
    getchar();
    return 1;
}
