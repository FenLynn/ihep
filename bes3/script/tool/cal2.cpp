#include <cmath>

void cal2()
{
double a,f,sigma1,sigma2,mu1,mu2;
f=3.70599e-01;
sigma1= 5.73670e-03;
sigma2= 3.4524e-03;
mu1=0.00709;
mu2=0.00073;
double y=sqrt(f*sigma1*sigma1+(1-f)*sigma2*sigma2+f*(1-f)*(mu1-mu2)*(mu1-mu2));
cout<<y<<endl;

}
