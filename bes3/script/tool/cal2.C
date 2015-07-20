#include <cmath>

void cal2()
{
double a,f,sigma1,sigma2,mu1,mu2,mcmean,fitmean1,fitmean2;
f=1.6484e-01;
sigma1= 1.4481e-02;
sigma2= 4.4099e-03;
mcmean=0.95778;
fitmean1=9.5648e-01;
fitmean2=9.5782e-01;
mu1=fabs(fitmean1-mcmean);
mu2=fabs(fitmean2-mcmean);
double y=sqrt(f*sigma1*sigma1+(1-f)*sigma2*sigma2+f*(1-f)*(mu1-mu2)*(mu1-mu2));
cout<<y<<endl;

}
