#include <math.h>
#include <stdio.h>

double t2(double ca,double va,double xa,double fa,double s){

return  ((3.6 * ca)/va) *(1 + ((xa)/(2500*fa)) + pow((xa/(500*fa)),3) ) + s * (3 + (3.6*ca)/va)  ; 
}
int main(){
double a0,a1,a2,a3,a4;
scanf("%lf%lf%lf%lf%lf", &a0,&a1,&a2,&a3,&a4);
printf("%lf\n", t2(a0,a1,a2,a3,a4));
 return 0;
}