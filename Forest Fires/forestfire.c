#include <stdio.h>
#include <stdlib.h>
int r=30;
int c = 40;
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

  while(1){
    //printf("%d",count);
    int num = 0;
    for(int m=0;m<r;m++){
      for(int n=0;n<c;n++){
        if(forest[m][n]=='*'){
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
    for(int m=0;m<r;m++){
      for(int n=0;n<c;n++){
        if(forest[m][n]=='*'){
          if((m-1)>=0){
            if(forest[m-1][n]=='T'){
              forest[m-1][n]='Q';
            }
          }
          if((n-1)>=0){
            if(forest[m][n-1]=='T'){
              forest[m][n-1]='Q';
            }
          }
          if((m+1)<30){
            if(forest[m+1][n]=='T'){
              forest[m+1][n]='Q';
            }
          }
          if((n+1)<40){
            if(forest[m][n+1]=='T'){
              forest[m][n+1]='Q';
            }
          }
        }
      }
    }
    //set all things with Q to F, and all F to nothing
    for(int m=0;m<r;m++){
      for(int n=0;n<c;n++){
        if(forest[m][n]=='*'){
          forest[m][n]=' ';
        }
        if(forest[m][n]=='Q'){
          forest[m][n]='*';
        }
      }
    }
    count++;
    // printf("%c",'\n');
    // printf("%s","-------------------------------------\n");
    // printer(forest);
  }

  // printf("%d",count);
  // printf("%c", ' ');
  // printf("%f", yeet);


  return count;

  }
  //call main 100 times
  int main(void){
    for(float x=0.01;x<=1;x+=0.01){
      int sum = 0;
      for(int y=0; y<100;y++){
        int result = iteration(x);

        sum+=result;
      }
      float average = sum/100.0;
      //printf("%f",average);
      // printf("%c", ' ');
      printf("%f",x);
      printf("%c",'\n');
      // printf("%f",x);
      // printf("%c", ' ');
      // printf("%f",average);
    }

    return 0;
  }
