//
// Torbert, 28 February 2017
//
#include <stdio.h>
#include <stdlib.h>
//
/
// Torbert, March 2015
//
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
void diff( triple* t , triple u , triple v ) // t = u - v
{
   t->x = u.x - v.x ;
   t->y = u.y - v.y ;
   t->z = u.z - v.z ;
}
//
void init()
{
   a[0].c.x =      0.50 ;
   a[0].c.y = -20000.00 ; // the floor
   a[0].c.z =      0.50 ;
   a[0].r   =  20000.25 ;
   a[0].h.r =    205    ; // color is Peru
   a[0].h.g =    133    ;
   a[0].h.b =     63    ;
   //
   a[1].c.x =      0.50 ;
   a[1].c.y =      0.50 ;
   a[1].c.z =      0.50 ;
   a[1].r   =      0.25 ;
   a[1].h.r =      0    ; // color is Blue
   a[1].h.g =      0    ;
   a[1].h.b =    255    ;
   //
   a[2].c.x =      1.00 ;
   a[2].c.y =      0.50 ;
   a[2].c.z =      1.00 ;
   a[2].r   =      0.25 ;
   a[2].h.r =      0    ; // color is Green
   a[2].h.g =    255    ;
   a[2].h.b =      0    ;
   //
   a[3].c.x =      0.00 ;
   a[3].c.y =      0.75 ;
   a[3].c.z =      1.25 ;
   a[3].r   =      0.50 ;
   a[3].h.r =    255    ; // color is Red
   a[3].h.g =      0    ;
   a[3].h.b =      0    ;
}



int main( int argc , char* argv[] )
{
   FILE* fout ;
   //
   char fname[50] ;
   //
   int frameCount ;
   //
   for( frameCount = 1 ; frameCount <= 100 ; frameCount++ )
   {
       //
       // something changes in the scene - position, angle, etc
       //
       // render all the pixel colors
       //
       // write out the PPM file - same code as before
       //
       fout = fopen( "allgreen.ppm" , "w" ) ;
       //
       fprintf( fout , "P3\n" ) ;
       fprintf( fout , "%d %d\n" , M , N ) ;
       fprintf( fout , "255\n" ) ;
       //
       for( y = 0 ; y < N ; y++ )
       {
          for( x = 0 ; x < M ; x++)
          {
             fprintf( fout , "%d %d %d\n" ,
              rgb[y][x][0] , rgb[y][x][1] , rgb[y][x][2] ) ;
          }
       }
       fclose( fout ) ;
       //
       // convert the temporary PPM file to a numbered frame file
       //
       sprintf( fname , "convert allgreen.ppm f%07d.png" , frameCount ) ;
       //
       system( fname ) ;
       //
       // after the run there will be 100 different PNG files
       //
       // f0000001.png
       // f0000002.png
       // f0000003.png
       //      :
       // f0000099.png
       // f0000100.png
       //
       // time convert -loop 0 -delay 10 *png movie.gif
       //
   }
   //
   return 0 ;
}
//
// end of file
//

