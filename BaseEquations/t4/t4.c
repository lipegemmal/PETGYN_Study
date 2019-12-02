#include <math.h>
#include <stdio.h>

double t4(double ca,double va,double xa,double fa){

return  ((3.6 * ca)/va) *(1 + (xa/(4000*fa)) + pow((xa/(900*fa)),3))  ; 
}
int main(){
double a0,a1,a2,a3;
scanf("%lf%lf%lf%lf", &a0,&a1,&a2,&a3);
printf("%lf\n", t4(a0,a1,a2,a3));
 return 0;
}