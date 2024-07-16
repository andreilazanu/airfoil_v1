#include <stdio.h>
#include <uxhw.h>
#include <math.h>


# define A0 340.29  //the speed of sound at standard sea level (661.47 knots (1,225.04 km/h; 340.29 m/s)),
# define T0 288.15 // (the temperature at standard sea level in K)
# define RHO0 1.225 // the air density at sea level in the International Standard Atmosphere (15 °C and 1013.25 hectopascals, corresponding to a density of 1.225 kg/m3),
# define P0 1.01325e5 // pressure at sea level


static void
loadInputs(double *  p, double *  ps, double *  T, double *  A, double *  alpha, double *  pc, double *  W, double *  beta)
{

    //*M        = UxHwDoubleDistFromSamples(empiricalTaylorFactorValues, sizeof(empiricalTaylorFactorValues)/sizeof(double));
    *p      = UxHwDoubleUniformDist(8.e4*(1.-0.22/100), 8.e4*(1+0.22/100));
    *ps     = UxHwDoubleUniformDist(5.e4*(1.-0.22/100), 5.e4*(1+0.22/100));
    *T      = UxHwDoubleUniformDist(260.*(1.-0.15/100), 260.*(1.+0.15/100));
    *A      = 1000.;	
    *alpha  = UxHwDoubleUniformDist(4*M_PI/180.*(1.-8/100), 4*M_PI/180.*(1.+8/100));
    *pc     = 0.06;
    *W      = UxHwDoubleUniformDist(25.*(1.-2/100), 25.*(1.+2/100));
    *beta   = UxHwDoubleUniformDist(30*M_PI/180.*(1.-8/100), 30*M_PI/180.*(1.+8/100));
}




    //Airfoil

    double alpha=4*M_PI/180.;
    double pc=0.06;
    //Wind
    double W=25;
    double beta=30*M_PI/180.;


double coeff1(double percent, double alpha) {
    // lift coefficient
    double C0=2.0*M_PI*(2.0*percent+1-sqrt(4.0*percent*percent+1));
    return C0+2.0*M_PI*alpha;
}



double rho(double p, double T) {
    return RHO0*p*T0/(P0*T);
}

double tas(double p, double ps, double T) {
    // This is the true air speed
    // https://en.wikipedia.org/wiki/True_airspeed

    double tassubsonic=sqrt(2.*(p-ps)/p*T/(RHO0*T0));;
    double tassupersonic=A0*sqrt(T/T0)*sqrt(5.*pow((p-ps)/p+1,(2./7.))-1.);;
    
   if (tassubsonic<340)
       return tassubsonic;
    else
        return tassupersonic;
}

double lift(double c1, double density, double v, double A) {
    // lift formula
    return c1*density*v*v*A/2.0;
}


// Model parameters p, p_s, T

int main(int argc, const char * argv[]) {
	
    double p;
    double ps;
    double T;

    //Airfoil
    double A;
    double alpha;
    double pc;
	
    //Wind
    double W;
    double beta;

    loadInputs(&p, &ps, &T, &A, &alpha, &pc, &W, &beta);
	
    double c1=coeff1(pc,alpha);
    double density=rho(p,T);
    

    
	
    double v=tas(p,ps,T)+W*cos(beta-alpha);
    printf("Lift force is %e \n",lift(c1,density,v,A));
    return 0;
}

