#include <math.h>
#include <stdio.h>

double t3(double ca,double va,double xa,double z,double fa,double s){

return  ((3.6 * ca)/va) *(1 + ((3*xa+z)/(8000*fa)) + pow((xa/(900*fa)),3) + pow(z/(1500*fa),3) ) + s * (3 + (3.6*ca)/va)  ; 
}
int main(){
double a0,a1,a2,a3,a4,a5;
scanf("%lf%lf%lf%lf%lf%lf", &a0,&a1,&a2,&a3,&a4,&a5);
printf("%lf\n", t3(a0,a1,a2,a3,a4,a5));
 return 0;
}