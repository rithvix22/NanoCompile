#include<bits/stdc++.h>
#include<iostream>
#include<thread>

using namespace std;

void first(vector <long long int> &array , long long int &sum1){
    
  long long int local_sum = 0;
  long long int n = array.size();
  for(int i =0 ; i<n/4;i++){

    local_sum += array[i];
  }
  sum1 = local_sum;
  cout << "Thread 1 finished\n" ; 
}

void second(vector <long long int> &array , long long int &sum2){

  long long int local_sum = 0;
  long long int n = array.size();
  for(int i =n/4 ; i<n/2;i++){

    local_sum += array[i];
  }
  sum2 = local_sum;
  cout << "Thread 2 finished\n" ; 
}

void third(vector <long long int> &array , long long int &sum3){

  long long int local_sum = 0;
  long long int n = array.size();
  for(int i =n/2 ; i<(3*n)/4;i++){

    local_sum += array[i];
  }
  sum3 = local_sum;
  cout << "Thread 3 finished\n" ; 
}

void fourth(vector <long long int> &array , long long int &sum4){

  long long int local_sum = 0;
  long long int n = array.size();
  for(int i =(3*n)/4 ; i<n;i++){

    local_sum += array[i];
  }
  sum4 = local_sum;
  cout << "Thread 4 finished\n" ; 
}

int main(){

  long long int n = 1000000001;
  vector <long long int> arr(n);
  for(int i = 0;i<n;i++){
    arr[i] = i;
  }

  long long int sum1 = 0;
  long long int sum2 = 0;
  long long int sum3 = 0;
  long long int sum4 = 0;

  thread t1(first,ref(arr),ref(sum1));
  thread t2(second,ref(arr),ref(sum2));
  thread t3(third,ref(arr),ref(sum3));
  thread t4(fourth,ref(arr),ref(sum4));
  t1.join();
  t2.join();
  t3.join();
  t4.join();

  long long int sum = sum1+sum2+sum3+sum4;

  cout << sum << endl;
}
