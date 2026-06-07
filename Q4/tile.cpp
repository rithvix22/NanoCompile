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

  
  for(int row_A =0;row_A<m;row_A++){
    for(int col_A=0;col_A<k;col_A++){
      for(int row_B=0;row_B<k;row_B++){
        for(int col_B=0;col_B<n;col_B++){

          for(int i = row_A*TILE;i<(row_A+1)*TILE;i++){
            for(int j = col_B*TILE;j<(col_B+1)*TILE;j++){
              float sum = 0;
              for(int kk = 0 ; kk<k;kk++){
                sum+=A[i*K+kk]*B[kk*N+j];
              }
              C[row_A*N+col_B]+= sum;
            }
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
