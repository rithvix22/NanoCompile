#include<stdio.h>



int main(){
  
  int n = 100;
  int k = 10;

  int arr[n];
  for(int i =0 ;i<n;i++){
    arr[i] = i;
  }

  int sum = 0;
  for(int i =0 ; i<k ; i++){
      
    int local_sum = 0;
    for(int j = i*(n/k);j<(i+1)*(n/k);j++){
      local_sum += arr[j];
    }
    sum+=local_sum;
  }
  
  printf("%d\n",sum);
}
