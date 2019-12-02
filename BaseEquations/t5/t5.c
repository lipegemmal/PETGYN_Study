#include <math.h>
#include <stdio.h>

double t5(double ca,double va,double xa,double fa){

return  ((3.6 * ca)/va) *(1 + (xa/(4000*fa)) + pow((xa/(900*fa)),3))  ; 
}
int main(){
double a0,a1,a2,a3;
scanf("%lf%lf%lf%lf", &a0,&a1,&a2,&a3);
printf("%lf\n", t5(a0,a1,a2,a3));
 return 0;
}