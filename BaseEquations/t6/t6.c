#include <math.h>
#include <stdio.h>

double t6(double ca,double va,double xa,double z,double fa){

return  ((3.6 * ca)/va) *(1 + ((3*xa+z)/(14000*fa)) + pow((xa/(900*fa)),3) + pow(z/(1600*fa),3))   ; 
}
int main(){
double a0,a1,a2,a3,a4;
scanf("%lf%lf%lf%lf%lf", &a0,&a1,&a2,&a3,&a4);
printf("%lf\n", t6(a0,a1,a2,a3,a4));
 return 0;
}