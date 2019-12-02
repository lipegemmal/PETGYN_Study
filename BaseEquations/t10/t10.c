#include <math.h>
#include <stdio.h>

double t10(double ca,double va,double xa,double fa,double w1,double w2,double w3){

return  ((3.6 * ca)/va) *(1 + ((xa)/(3000*fa)) + pow((xa/(1200*fa)),3) + pow(w1/1800,3) + pow(w2/1800,3) + pow(w3/1800,3) ) ; 
}
int main(){
double a0,a1,a2,a3,a4,a5,a6;
scanf("%lf%lf%lf%lf%lf%lf%lf", &a0,&a1,&a2,&a3,&a4,&a5,&a6);
printf("%lf\n", t10(a0,a1,a2,a3,a4,a5,a6));
 return 0;
}