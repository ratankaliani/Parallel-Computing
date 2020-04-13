#include <stdlib.h>
#include <stdio.h>
//
#include "mpi.h"
//
#include <sys/time.h>
//
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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//int r=300;
//int c =400;
#define r 300
#define c 400

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
long timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}


  int main(void){
    clock_t t1, t2;
		int rank;
		int size;
		int tag = 0;
		MPI_Init(&argc,&argv);
		MPI_Comm_size(MPI_COMM_WORLD, &size);
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    long elapsed;
		srand(rank);
    t1 = clock();


    for(float x=0.01;x<=1;x+=0.01){
      int sum = 0;
      for(int y=0; y<100/size;y++){
        int result = iteration(x);

        sum+=result;
      }

      float average = sum/(100.0*c);
      printf("%f",average/c);
      printf("%c", ' ');
      printf("%f",x);
      printf("%c",'\n');

    }
		MPI.finalize();
    t2 = clock();

    elapsed = timediff(t1, t2);
    printf("elapsed: %ld ms\n", elapsed);

    return 0;
  }
