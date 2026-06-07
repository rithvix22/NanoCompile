#include<stdio.h>
#include<bits/stdc++.h>

using namespace std;

int main(){

  long long int n = 1000000001;
  vector <long long int> arr(n);
  for(int i = 0;i<n;i++){
    arr[i] = i;
  }

  long long int sum = 0;
  for(int i =0;i<n;i++){
    sum+=arr[i];
  }
  
  cout << sum<<endl;
}

