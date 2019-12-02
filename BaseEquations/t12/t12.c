#include <math.h>
#include <stdio.h>

double t12(double ca,double va,double xa,double z,double fa,double w1,double w2,double w3){

return  ((3.6 * ca)/va) *(1 + ((3*xa+z)/(12000*fa)) + pow((xa/(1200*fa)),3) + pow(w1/1800,3) + pow(w2/1800,3) + pow(w3/1800,3) + pow(z/(2000*fa),3) ) ; 
}
int main(){
double a0,a1,a2,a3,a4,a5,a6,a7;
scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &a0,&a1,&a2,&a3,&a4,&a5,&a6,&a7);
printf("%lf\n", t12(a0,a1,a2,a3,a4,a5,a6,a7));
 return 0;
}