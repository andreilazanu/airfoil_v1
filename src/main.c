#include <stdio.h>
#include <uxhw.h>
#include <math.h>


# define A0 340.29  //the speed of sound at standard sea level (661.47 knots (1,225.04 km/h; 340.29 m/s)),
# define T0 288.15 // (the temperature at standard sea level in K)
# define RHO0 1.225 // the air density at sea level in the International Standard Atmosphere (15 °C and 1013.25 hectopascals, corresponding to a density of 1.225 kg/m3),
# define P0 1.01325e5 // pressure at sea level


static void
loadInputs(double *  p, double *  ps, double *  T, double *  S, double *  alpha, double *  pc)
{

    *p      = UxHwDoubleUniformDist(8.e4*(1.-0.22/100.), 8.e4*(1+0.22/100.));
    *ps     = UxHwDoubleUniformDist(5.e4*(1.-0.22/100.), 5.e4*(1+0.22/100.));
    *T      = UxHwDoubleUniformDist(275.*(1.-0.15/100.), 275.*(1.+0.15/100.));
    *S      = 1000.;	
    *alpha  = UxHwDoubleUniformDist(4.*M_PI/180.*(1.-8./100.), 4.*M_PI/180.*(1.+8./100.));
    *pc     = 0.06;
}

static void
loadInputs2(double *  p, double *  ps, double *  T, double *  S, double *  alpha, double *  pc)
{

    *p      = UxHwDoubleUniformDist(5.5e4*(1.-0.22/100.), 5.5e4*(1+0.22/100.));
    *ps     = UxHwDoubleUniformDist(5.03e4*(1.-0.22/100.), 5.03e4*(1+0.22/100.));
    *T      = UxHwDoubleUniformDist(258.*(1.-0.15/100.), 258.*(1.+0.15/100.));
    *S      = 1000.;	
    *alpha  = UxHwDoubleUniformDist(6.*M_PI/180.*(1.-8./100.), 6.*M_PI/180.*(1.+8./100.));
    *pc     = 0.04;
}


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

   return A0*sqrt(T/T0)*sqrt(5.)*sqrt(pow((p-ps)/p+1,(2./7.))-1.);;

}

double mach(double p, double ps) {
	return sqrt(5.*(pow((p-ps)/p+1.,2./7.)-1.));
	
}

double lift(double c1, double density, double v, double A, double p, double ps) {
    // lift formula
    double m=mach(p,ps);
    if(m<0.5)
	    return c1*(p-ps)*A/sqrt(1.-m*m);
    else
	    return c1*density*v*v*A/2.0/sqrt(1.-m*m);
   
}


// Model parameters p, p_s, T

int main(int argc, const char * argv[]) {
	
    double p;
    double ps;
    double T;

    //Airfoil
    double S;
    double alpha;
    double pc;

    double c1;
    double density;
    double v;

    // Model 1
    loadInputs(&p, &ps, &T, &S, &alpha, &pc);
    c1=coeff1(pc,alpha);
    density=rho(p,T);
    v=tas(p,ps,T);
    printf("rho: %e; tas: %e\n",density,v);
    printf("Lift force (1) is %e \n",lift(c1,density,v,S,p,ps));

    // Model 2
    loadInputs2(&p, &ps, &T, &S, &alpha, &pc);
    c1=coeff1(pc,alpha);
    density=rho(p,T);
    v=tas(p,ps,T);
    printf("rho: %e; tas: %e\n",density,v);
    printf("Lift force (2) is %e \n",lift(c1,density,v,S,p,ps));


	
    return 0;
}

