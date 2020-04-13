//
// Torbert, 28 February 2017
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
//

// Torbert, March 2015
//
#define M 640
#define N 480
typedef struct
{
   double x ;
   double y ;
   double z ;
	
   //
} triple ;
//
triple e = { 0.50 , 0.50 , -1.00 } ; // the eye
triple g = { 0.00 , 1.25 , -0.50 } ; // the light
//
double dotp( triple t , triple u )
{
   return t.x * u.x + t.y * u.y + t.z * u.z ;
}
//
triple diff(triple u , triple v ) // t = u - v
{
	triple bet;
	bet.x = u.x - v.x ;
	bet.y = u.y - v.y ;
	bet.z = u.z - v.z ;
	return bet;

}
//
typedef struct{
	double r;
	double g;
	double b;
} hue;
typedef struct{
	triple c;
	double r;
	hue h;
} sphere;
sphere ow[4];
void init()
{
   ow[0].c.x =      0.50 ;
   ow[0].c.y = -20000.00 ; // the floor
   ow[0].c.z =      0.50 ;
   ow[0].r   =  20000.25 ;
   ow[0].h.r =    205    ; // color is Peru
   ow[0].h.g =    133    ;
   ow[0].h.b =     63    ;
   //
   ow[1].c.x =      0.50 ;
   ow[1].c.y =      0.50 ;
   ow[1].c.z =      0.50 ;
   ow[1].r   =      0.25 ;
   ow[1].h.r =      0    ; // color is Blue
   ow[1].h.g =      0    ;
   ow[1].h.b =    255    ;
   //
   ow[2].c.x =      1.00 ;
   ow[2].c.y =      0.50 ;
   ow[2].c.z =      1.00 ;
   ow[2].r   =      0.25 ;
   ow[2].h.r =      0    ; // color is Green
   ow[2].h.g =    255    ;
   ow[2].h.b =      0    ;
   //
   ow[3].c.x =      0.00 ;
   ow[3].c.y =      0.75 ;
   ow[3].c.z =      1.25 ;
   ow[3].r   =      0.50 ;
   ow[3].h.r =    255    ; // color is Red
   ow[3].h.g =      0    ;
   ow[3].h.b =      0    ;
}



int main( int argc , char* argv[] )
{
	init();
	FILE* fout ;
	//
	
	//
	fout = fopen( "ray3.ppm" , "w" ) ;
	fprintf( fout , "P3\n" ) ;
	fprintf( fout , "%d %d\n" , M , N ) ;
	fprintf( fout , "255\n" ) ;
	
	//eye to ball
	for(int t = 0; t<10; t++){
		for( int y = 0 ; y < N ; y++ )
		{
		  for( int x = 0 ; x < M ; x++)
		  {
		     
			//Define Vectors
			double px = (1.0 * x)/N-1.0/6;
			double py = 1- (1.0 * y) / N;//-(9.0/10);
			double pz = 0;

			triple ray = {px - e.x, py - e.y, pz - e.z};
		
		
			double magnitude = sqrt(pow(ray.x,2)+pow(ray.y,2)+pow(ray.z,2));
		
			ray.x /=magnitude;
			ray.y /=magnitude;
			ray.z /=magnitude;
		
			int hit=-1;
			double tmin = DBL_MAX;
			for(int s=0;s<4;s++){
				triple d= diff(e,ow[s].c);
				double a = 1.0;
				double b = 2*(dotp(ray,d));
				double c = pow(d.x,2)+pow(d.y,2)+pow(d.z,2)-pow(ow[s].r,2);

				double disc = pow(b,2)-(4*a*c);
				if(disc>0){
					double t1 = (-b+sqrt(disc))/(2*a);
					double t2 = (-b-sqrt(disc))/(2*a);
			
					double t = fmin(t1,t2);
					if(t<tmin && t>0){
						hit=s;
						tmin = t;
					}
				}
			}

			if(hit==-1){
				fprintf(fout,"135 206 235 \n");
			}
			else{
			
				double px = e.x+tmin*ray.x;
				double py = e.y+tmin*ray.y;
				double pz = e.z+tmin*ray.z;
				triple ray = {g.x-px, g.y-py, g.z-pz};
				double magnitude = sqrt(pow(ray.x,2)+pow(ray.y,2)+pow(ray.z,2));
			
			
				int hits=-1;
				double tmin = DBL_MAX;
				ray.x /=magnitude;
				ray.y /=magnitude;
				ray.z /=magnitude;
				for(int s=0;s<4;s++){
					triple pt = {px,py,pz};
					triple d= diff(pt,ow[s].c);
					double a = 1.0;
					double b = 2*(dotp(ray,d));
					double c = pow(d.x,2)+pow(d.y,2)+pow(d.z,2)-pow(ow[s].r,2);

					double disc = pow(b,2)-(4*a*c);
					if(disc>0){
						double t1 = (-b+sqrt(disc))/(2*a);
						double t2 = (-b-sqrt(disc))/(2*a);
			
					
						if(t1>0.01 || t2>0.01){
							hits=s;
						
							break;
						
						}
					}
				}

				if(hits==-1){
					triple lamb = {px-ow[hit].c.x, py-ow[hit].c.y, pz-ow[hit].c.z};
					double magnitudel = sqrt(pow(lamb.x,2)+pow(lamb.y,2)+pow(lamb.z,2));
					lamb.x/=magnitudel;
					lamb.y/=magnitudel;
					lamb.z/=magnitudel;
					double multi = dotp(lamb,ray);	
					double fac = 1.0 ;
					if( multi < 0 ){ 
					multi = 0 ;}
					fac = 0.5 + 0.5 * multi ;
					if (hit>0){
						fprintf(fout, "%i %i %i\n", (int)(ow[hit].h.r*fac),(int)(ow[hit].h.g*fac),(int)(ow[hit].h.b*fac));
					}
					else{
						int xi = (int)(px/0.1);
						int zi = (int)(pz/0.1);
						int sum = (xi + zi)%2;
						if(sum<0){
							sum--;
						
						}
					
					
					
						if(sum==0){
							//royal purple
							fprintf(fout,"120 81 169 \n");			
						}
						else{
						
							fprintf(fout,"205 133 63 \n");
						}		
					}
				}
			
				else{
			
				if (hit>0){
						fprintf(fout, "%i %i %i\n", (int)(ow[hit].h.r*0.5),(int)(ow[hit].h.g*0.5),(int)(ow[hit].h.b*0.5));
					}
				else{
					int xi = (int)(px/0.1);
					int zi = (int)(pz/0.1);
					int sum = (xi + zi)%2;
					if(sum<0){
						sum--;
					
					}
				
				
				
					if(sum==0){
						//royal purple
						fprintf(fout,"60 41 85 \n");			
					}
					else{
					
						fprintf(fout,"102 67 32 \n");
					}		
				}

				//fprintf(fout, "%i %i %i\n", (int)(ow[hit].h.r*0.5 ),(int)(ow[hit].h.g*0.5 ),(int)(ow[hit].h.b*0.5 ));
				}
			
			}
			

		  }
		}
	}
	
	  
	fclose( fout ) ;
		
	//
	return 0 ;
}
//
// end of file
//



