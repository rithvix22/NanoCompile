#include<bits/stdc++.h>
#include<iostream>

using namespace std;

void vec_print(vector<int64_t> v){
  
  for(auto x : v){
    cout << x << " ";
  }
  cout << endl;
}

optional<vector<int64_t>> broadcastShape(vector<int> &a,vector <int> &b){
  
  vector<int64_t> return_vector;
  
  
  //calculating the ranks.
  int rank_a=a.size();
  int rank_b=b.size();
  int rank;
  
  //extrapolating to same sizes.
  if(rank_a<rank_b){
    
    int diff = rank_b-rank_a;
    a.insert(a.begin(),diff,1);
    rank = rank_b;
    rank_a = rank;
  }
  else if(rank_a<rank_b){
    
    int diff = rank_a - rank_b;
    b.insert(b.begin(),diff,1);
    rank = rank_a;
    rank_b = rank;
  }
  else {
    rank = rank_a;
  }

  //checking each axis;
  for(int i = rank-1 ;i>=0;i--){
     
    if(a[i]==b[i]){
      
      return_vector.push_back(a[i]);
    }

    else if(a[i]==1){
      
      return_vector.push_back(b[i]);
    }
    
    else if(b[i]==1){
      return_vector.push_back(a[i]);
    }

    else{
      return nullopt;
    }
  }
  
  reverse(return_vector.begin(),return_vector.end());
  return return_vector;
}

int main(int argc , char **argv){
  
  int n = atoi(argv[1]); //sizeof(a);
  int m = atoi(argv[2]); //sizeof(b);

  vector <int> a;
  vector <int> b;

  int scan;
  for(int i =0 ;i<n;i++){
    cin >> scan;
    a.push_back(scan);
  }

  for(int i = 0 ;i<m;i++){
    cin >> scan;
    b.push_back(scan);
  }
  cout <<"a : ";
  for(auto x : a){
    cout << x << " ";
  }
  cout << endl;
  cout << "b : ";
  for(auto x : b){
    cout << x << " ";
  }
  cout << endl;
  optional <vector<int64_t>> result = broadcastShape(a,b);

  if(result.has_value()){
    cout <<"broadcastable\n" ;
    cout << "answer : ";
    vec_print(*result);
  }

  else{
    cout << "not broadcastable\n";
  }
}
