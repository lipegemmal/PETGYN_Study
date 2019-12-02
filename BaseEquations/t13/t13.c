#include <math.h>
#include <stdio.h>

double t13(double ca,double va,double xa,double fa,double y1,double y2){

return  ((3.6 * ca)/va) *(1 + (xa/(2000*fa)) + pow((xa/(1000*fa)),3) ) + pow(y1/300,2) + pow(y2/300,2) ; 
}
int main(){
double a0,a1,a2,a3,a4,a5;
scanf("%lf%lf%lf%lf%lf%lf", &a0,&a1,&a2,&a3,&a4,&a5);
printf("%lf\n", t13(a0,a1,a2,a3,a4,a5));
 return 0;
}