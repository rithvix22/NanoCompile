#include<bits/stdc++.h>
#include<iostream>

using namespace std;

void mat_print(float *mat,int rows , int cols){
  for(int i = 0 ;i<rows;i++){
    for(int j=0;j<cols;j++){
      cout << mat[i*cols+j] << " ";
    }
    cout << endl;
  }
}

void matmul(float *A,
            float *B,
            float *C,
            int M,
            int N,
            int K
            )
{
  for(int i =0 ;i<M;i++){
    for(int j=0;j<N;j++){

      float sum = 0;
      for(int k =0 ;k<K;k++){
        sum+=A[i*K+k]*B[k*N+j];
      }
      C[i*N+j] = sum;
    }
  }
}

void matmul_tiled(float *A,
                  float *B,
                  float *C,
                  int M,
                  int N,
                  int K,
                  int TILE)
{
  if(M%TILE!=0 || N%TILE!=0 || K%TILE!=0){cout << "Invalid Tile size" ; return ;}
  
  int m = M/TILE;
  int n = N/TILE;
  int k = K/TILE;

  for(int rowBlock_A = 0 ; rowBlock_A < m ; rowBlock_A++){
    for(int colBlock_B = 0 ; colBlock_B<n ; colBlock_B++){

      for(int index = 0 ; index < k ; index++){

        for(int i = rowBlock_A*TILE ; i<(rowBlock_A+1)*TILE ; i++ ){

          for(int j = colBlock_B*TILE ; j < (colBlock_B+1)*TILE ; j++ ){
            
            int sum = 0;
            for(int dot = index*TILE ; dot<(index+1)*TILE;dot++){
             
            //****************AUTO VECTORIZATION**************************  
              sum+=A[i*K+dot]*B[dot*N+j]; 
            //****************AUTO VECTORIZATION**************************
            }
            C[i*N+j] += sum;
          }
        }
      }
    }
  }
}

int main(int argc , char **argv){
  int M,N,K;
  M = atoi(argv[1]);
  N = atoi(argv[2]);
  K = atoi(argv[3]);

  float *A = (float *)malloc(sizeof(float)*M*K);
  float *B = (float *)malloc(sizeof(float)*N*K);
  
  for(int i =0;i<M*K;i++){
      
    A[i] = i;
  }
  for(int i = 0;i<N*K;i++){

    B[i] = i;
  }

  float *C = (float *)malloc(sizeof(float)*M*N);
  for(int i = 0 ;i<M*N;i++){
    C[i] = 0;
  }
  
  int TILE = 2;
  mat_print(A,M,K);
  cout << endl;
  matmul_tiled(A,B,C,M,N,K,TILE);
  mat_print(C,M,N);

}
