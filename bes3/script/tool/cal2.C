#include <cmath>

void cal2()
{
double a,f,sigma1,sigma2,mu1,mu2,mcmean,fitmean1,fitmean2;
f=0.2246;
sigma1= 0.01040;
sigma2= 0.004398;
mcmean=0.1349766;
fitmean1=0.133473;
fitmean2=0.134532;
mu1=fabs(fitmean1-mcmean);
mu2=fabs(fitmean2-mcmean);
double y=sqrt(f*sigma1*sigma1+(1-f)*sigma2*sigma2+f*(1-f)*(mu1-mu2)*(mu1-mu2));
cout<<y<<endl;

}
