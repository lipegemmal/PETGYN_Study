#include <math.h>
#include <stdio.h>

double t9(double ca,double va,double xa,double fa,double z,double y1,double y2){

return  ((3.6 * ca)/va) *(1 + ((3*xa+z)/(10000*fa)) + pow((xa/(900*fa)),3) + pow(z/(1600*fa),3) ) + pow(y1/300,2) + pow(y2/300,2) ; 
}
int main(){
double a0,a1,a2,a3,a4,a5,a6;
scanf("%lf%lf%lf%lf%lf%lf%lf", &a0,&a1,&a2,&a3,&a4,&a5,&a6);
printf("%lf\n", t9(a0,a1,a2,a3,a4,a5,a6));
 return 0;
}