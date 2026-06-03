#include<bits/stdc++.h>
#include<iostream>

using namespace std;

using Datatype = variant<int,vector<int>,string,float>;
using Attributes_DS = unordered_map<string,Datatype>;

class Operator;

class Tensor{
  
public:
  string name;
  vector <int> shape;
  string dtype;
  Operator *producer;
  vector <Operator*> consumers;
};

class Operator{

public:
  string name;
  vector <Tensor*> inputs;
  Tensor* output;
  Attributes_DS attributes;
};

class Graph{
  
public:
  vector <Tensor*> input_tensors;
  vector <Tensor*> output_tensors;
  vector <Tensor*> tensors;

  vector <Operator*> operators;

  unordered_map<string,Tensor*> tensor_map;
  unordered_map<string,Operator*> operator_map;
};

int main(){
  
}
