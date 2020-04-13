//
// Torbert, 8 November 2018
//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//
// https://physics.nist.gov/cgi-bin/cuu/Value?bg
//
#define G 6.674e-11 // (m^3)(kg^-1)(s^-2)
//
// https://ssd.jpl.nasa.gov/?planet_phys_par
//
#define M 5.972e+24 // kg
#define R 6.371e+6  // m
//
// parameters
//
#define DT 10     // s
//
int main()
{
	//
	// time intervals - duration is 90 minutes
	//
	double theta = 28;
	double durationHour = (theta/360)*672*1.5;
	int n = (int)( 0.5 + ( durationHour * 60 * 60 ) / DT ) ;
	//
	//////////////////////////////////////////////////
	//
	double* t = malloc(sizeof(double) * n) ;
	double* x= malloc(sizeof(double) * n) ;
	double* y= malloc(sizeof(double) * n) ;
	double* vx = malloc(sizeof(double) * n) ;
	double* vy = malloc(sizeof(double) * n) ;
	double* shipx= malloc(sizeof(double) * n) ;
	double* shipy= malloc(sizeof(double) * n) ;
	double* shipvx = malloc(sizeof(double) * n) ;
	double* shipvy = malloc(sizeof(double) * n) ;
	//
	//////////////////////////////////////////////////
	//
	FILE* fout   ;
	//
	int j        ;
	//
	double r , a ;
	//
	double mSat = 28801.0 ; // kg - Apollo 11
	//double m = 419725.0 ; // kg - ISS
	double mMoon = 7.34767e+22;
	//
	//////////////////////////////////////////////////
	//
	// International Space Station
	//
	// https://www.nasa.gov/sites/default/files/atoms/files/np-2015-05-022-jsc-iss-guide-2015-update-111015-508c.pdf
	//
	// Page 54 - altitude : 370 km to 460 km
	// Page 54 - speed    : 28,000 km per hour
	//
	double rMoon = 3.84e+8;


	t[0]  = 0.0          ;
	x[0] = 3.84e+8;
	y[0] = 0.0;
	vx[0] =   0.0   ; // circular-7672 elliptical
	vy[0] = 1023.0556;


	shipx[0] = 202751774.4*cos(theta*M_PI/180.0);
	shipy[0] = 202751774.4*sin(theta*M_PI/180.0);
	shipvx[0] = 1527.048*cos(theta*M_PI/180.0);
	shipvy[0] = 1527.048*sin(theta*M_PI/180.0);
	//ship to Earth
	double rshipE = 202751774.4;
	//ship to moon
	double rshipM;

	//
	// hyperbolic changes both initial (x,y) and (vx,vy) - compare to circular
	//
	//////////////////////////////////////////////////
	//
	for( j = 1 ; j < n ; j ++ )
	{
		//earth on moon
		t[j] = t[j-1] + DT           ;
		x[j] = x[j-1] + DT * vx[j-1] ;
		y[j] = y[j-1] + DT * vy[j-1] ;
		shipx[j] = shipx[j-1] + DT * shipvx[j-1] ;
		shipy[j] = shipy[j-1] + DT * shipvy[j-1] ;
		//
		r = sqrt( x[j-1]*x[j-1] + y[j-1]*y[j-1] ) ;
		//
		a = G * M / ( r * r ) ;
		//
		vx[j] = vx[j-1] - a * ( x[j-1] / r ) * DT ;
		vy[j] = vy[j-1] - a * ( y[j-1] / r ) * DT ;
		// earth on ship
		//
		rshipE = sqrt( shipx[j-1]*shipx[j-1] + shipy[j-1]*shipy[j-1] ) ;
		//
		a = G * M / ( rshipE * rshipE ) ;
		//
		shipvx[j] = shipvx[j-1] - a * ( shipx[j-1] / rshipE ) * DT ;
		shipvy[j] = shipvy[j-1] - a * ( shipy[j-1] / rshipE ) * DT ;
		//moon on ship
		rshipM = sqrt( (shipx[j-1]-x[j-1])*(shipx[j-1]-x[j-1]) + (shipy[j-1]-y[j-1])*(shipy[j-1]-y[j-1]) ) ;
		//
		a = G * mMoon / ( rshipM * rshipM ) ;
		//
		shipvx[j] -=  a * ( (shipx[j-1]-x[j-1]) / rshipM ) * DT ;
		shipvy[j] -= a * ( (shipy[j-1]-y[j-1]) / rshipM ) * DT ;
	}
	//
	//////////////////////////////////////////////////
	//
	fout = fopen( "orbit.txt" , "w" ) ;
	//
	for( j = 0 ; j < n ; j ++ )
	{
		fprintf( fout , "%d %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f\n" ,
		j , t[j] , x[j] , y[j] , vx[j] , vy[j] , sqrt( vx[j]*vx[j] + vy[j]*vy[j] ), sqrt( x[j]*x[j] + y[j]*y[j] ) ) ;
	}
	//
	fclose( fout ) ;
	fout = fopen( "orbitShip.txt" , "w" ) ;
	//
	for( j = 0 ; j < n ; j ++ )
	{
		fprintf( fout , "%d %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f\n" ,
		j , t[j] , shipx[j] , shipy[j] , shipvx[j] , shipvy[j] , sqrt( shipvx[j]*shipvx[j] + shipvy[j]*shipvy[j] ), sqrt( shipx[j]*shipx[j] + shipy[j]*shipy[j] ) ) ;
	}
	//
	fclose( fout ) ;
	//
	//////////////////////////////////////////////////
	//
	fout = fopen( "earth.txt" , "w" ) ;
	//
	for( j = 0 ; j <= 360 ; j ++ )
	{
		fprintf( fout , "%0.16f %0.16f\n" , R * cos( j * M_PI / 180.0 ) , R * sin( j * M_PI / 180.0 ) ) ;
	}
	//
	fclose( fout ) ;
	//
	// done
	//
	return 0 ;
}
//
// end of file
