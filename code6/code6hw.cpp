#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
double eps(double x){
    return exp(-x) / 2 * (1 + (2 * sin(2*x) - cos(2*x))/5);
} 
int main(){
    
    return 0;
}