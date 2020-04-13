//
// Torbert, 18 October 2018
//
#include <stdlib.h>
#include <stdio.h>
//

#include "mpi.h"
//
#include <time.h>
//int r=300;
//int c =400;
#define r 300
#define c 400
typedef struct Foo {
  int somearray[2];
} Foo;

//actually calculates
int iteration(float yeet){

  //randomly fill array
  char forest[r][c];
  for(int m=0; m<r;m++){
    for (int n=0;n<c;n++){
      float p = rand() *1.0 / RAND_MAX;
      if(p<yeet){
        forest[m][n]='T';
      }
      else{
        forest[m][n]=' ';
      }
    }
  }
  //setup stuffs on fire
  for(int m=0; m<r;m++){
    if(forest[m][0]=='T'){
    forest[m][0]='*';}
  }
  //check if there is nothing left
  int count=0;
  Foo bu;
  while(1){
    Foo yeetarray[(r*c)] = {bu};

    int num = 0;
    for(int m=0;m<r;m++){
      for(int n=0;n<c;n++){
        Foo f;
        if(forest[m][n]=='*'){
          f.somearray[0]=m;
          f.somearray[1]=n;
          yeetarray[num]=f;
          num++;

          }

        }
      }

    //exit loop (no fire or trees)
    if(num==0){
      break;
    }

    for(int a=0;a<num;a++){
      Foo boo;
      int m = yeetarray[a].somearray[0];
      int n = yeetarray[a].somearray[1];
        if(forest[m][n]=='*'){
          if((m-1)>=0){
            if(forest[m-1][n]=='T'){
              forest[m-1][n]='Q';
              boo.somearray[0] = m-1;
              boo.somearray[1] = n;
              yeetarray[num]=boo;
              num++;
            }
          }
          if((n-1)>=0){
            if(forest[m][n-1]=='T'){
              forest[m][n-1]='Q';
              boo.somearray[0] = m;
              boo.somearray[1] = n-1;
              yeetarray[num]=boo;
              num++;
            }
          }
          if((m+1)<r){
            if(forest[m+1][n]=='T'){
              forest[m+1][n]='Q';
              boo.somearray[0] = m+1;
              boo.somearray[1] = n;
              yeetarray[num]=boo;
              num++;
            }
          }
          if((n+1)<c){
            if(forest[m][n+1]=='T'){
              forest[m][n+1]='Q';
              boo.somearray[0] = m;
              boo.somearray[1] = n+1;
              yeetarray[num]=boo;
              num++;
            }
          }
        }
      }
    //set all things with Q to F, and all F to nothing
    for(int x=0;x<num;x++){
      int y = yeetarray[x].somearray[0];
      int z = yeetarray[x].somearray[1];
        if(forest[y][z]=='*'){
          forest[y][z]=' ';
        }
        if(forest[y][z]=='Q'){
          forest[y][z]='*';
        }
      }
    count++;
  }
  return count;
  }
int main( int argc , char* argv[] )
{
   // MPI variables
   int        rank    ;
   int        size    ;
   MPI_Status status  ;
   int        tag = 0 ; // does not matter as long as same
   // other variables
   int        k , j  ;
   int        x , y  ;
   // boilerplate
   MPI_Init(      &argc          , &argv ) ;
   MPI_Comm_size( MPI_COMM_WORLD , &size ) ; // same
   MPI_Comm_rank( MPI_COMM_WORLD , &rank ) ; // different
   srand( rank ) ;
   // manager has rank = 0
   //
   if( rank == 0 )
   {
      x = 5 ;
      //
      for( j = 1 ; j < size ; j++ )
      {
         MPI_Send( &x , 1 , MPI_INT , j , tag , MPI_COMM_WORLD ) ;
      }
      //
      k = 0 ;
      //
      while( k < size - 1 )
      {
          MPI_Recv( &x , 1 , MPI_INT , MPI_ANY_SOURCE , tag , MPI_COMM_WORLD , &status ) ;
          j = status.MPI_SOURCE ;
          if( x % 4 == 3 )
          {
              y = -1 ;
              //
              printf( "Worker rank %d is done now.\n" , j ) ;
              //
              k++ ;
          }
          else
          {
              y = 5 ;
          }
          //
          MPI_Send( &y , 1 , MPI_INT , j , tag , MPI_COMM_WORLD ) ;
      }
      //
      printf( "*** *** Manager done. *** ***\n" ) ;
   }
   //
   // workers have rank > 0
   //
   else
   {
       // while( 1 )
       // {
          MPI_Recv( &y , 1 , MPI_INT , 0 , tag , MPI_COMM_WORLD , &status ) ;
          //
          if( y < 0 ) break ;
          //
          for(float a=0.01;a<=1;a+=0.01){
            int sum = 0;
            for(int z=0; z<100/size;z++){
              int result = iteration(a);
              sum+=result;
            }

            float x = sum/(100.0*c);}
          //
          printf( "rank=%d x=%d x%%4==%d\n" , rank , x , x % 4 ) ;

          //
          MPI_Send( &x , 1 , MPI_FLOAT , 0 , tag , MPI_COMM_WORLD ) ;
       //}
       //
       printf( "*** Worker %d done. ***\n" , rank ) ;
   }
   //
   // boilerplate
   //
   MPI_Finalize() ;
   //
   return 0;
}
//
// end of file
//
