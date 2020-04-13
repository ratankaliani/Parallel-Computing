#include <stdlib.h>
#include <stdio.h>
//
#include "mpi.h"
//
#include <sys/time.h>
//
//mpicc filename.c
//mpirun -np 4 a.out
//scp a.out infosphere:.

//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//int r=300;
//int c =400;
#define r 90
#define c 120

void printer(char boys[r][c]){
  for(int m=0; m<r;m++){
    char printable[1000];
    for (int n=0;n<c;n++){
      printable[n] = boys[m][n];
      printf("%c",boys[m][n]);
    }
    printf("%c",'\n');
  }
}

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
  // printer(forest);
  //check if there is nothing left
  int count=0;
  Foo bu;
  while(1){
    //printf("%d",count);
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

    // if(count==7){
    //   break;
    // }
    //set all things with trees next to fire on Q
    // for(int m=0;m<r;m++){
    //   for(int n=0;n<c;n++){
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

    //   }
    // }
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
  //call main 100 times
double gettime()
{
	double t ;
	//
	struct timeval* ptr = (struct timeval*)malloc( sizeof(struct timeval) ) ;
	//
	gettimeofday( ptr , NULL ) ; // second argument is time zone... NULL
	//
	t = ptr->tv_sec * 1000000.0 + ptr->tv_usec ;
	//
	free( ptr ) ;
	//
	return t / 1000000.0 ;
}
//
int main( int argc , char* argv[] )
{
   //
   // MPI variables
   //
   int        rank    ;
   int        size    ;
   MPI_Status status  ;
   int        tag = 0 ;
   //
   // other variables
   //
   int        k , j  ;
   double     prob , nbt ;
   double     tic  , toc ;
	int totalIter = 0;
   //
   // boilerplate
   //
   MPI_Init(      &argc          , &argv ) ;
   MPI_Comm_size( MPI_COMM_WORLD , &size ) ; // same
   MPI_Comm_rank( MPI_COMM_WORLD , &rank ) ; // different
   //
   // manager has rank = 0
   //
   if( rank == 0 )
   {
      printf( "\n" ) ;
      //
      prob = 0.60 ; // everyone gets the same probability
      //
      for( j = 1 ; j < size ; j++ )
      {
         MPI_Send( &prob , 1 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD ) ;
      }
      //
      for( k = 1 ; k < size ; k++ )
      {
         MPI_Recv( &nbt , 1 , MPI_DOUBLE , MPI_ANY_SOURCE , tag , MPI_COMM_WORLD , &status ) ;
         //
         j = status.MPI_SOURCE ;
         //
         printf( "%d %d %20.16f\n" , j , size , nbt ) ;
      }
      //
      printf( "\n" );
   }
   //
   // workers have rank > 0
   //
   else
   {
      tic = gettime() ;
      //
      MPI_Recv( &prob , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD , &status ) ;
      //
      for(double i=0;i<1.00; i+=0.01){
	totalIter=0;
	for(int y=0; y<100/size; y++){
		totalIter+=iteration(i);
	
	
	 }
	}     
      //
      MPI_Send( &nbt , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD ) ;
      //
      toc = gettime() ;
      //
      printf( "*** %d of %d - time = %0.16f seconds\n" , rank , size , toc - tic ) ;
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
